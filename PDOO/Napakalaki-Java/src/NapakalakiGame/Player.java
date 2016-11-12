/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;
import GUI.Dice;
import java.util.*;

/**
 *
 * @author Cervi
 */
public class Player {
    
    public static final int MAXLEVEL=10;
    private String name;
    private int level;
    private boolean dead=true;
    private boolean canISteal=true;
    
    ArrayList<Treasure> hiddenTreasures=null;
    ArrayList<Treasure> visibleTreasures=null;
    private Player enemy=null;
    private BadConsequence pendingBadConsequence=null;
    
    
    public Player(String name){
        this.name=name;
        level=1;
        dead=true;
        canISteal=true;
        hiddenTreasures=new ArrayList();
        visibleTreasures=new ArrayList();
    }
    
    public Player(Player p){
        this.name=p.name;
        this.level = p.level;
        this.visibleTreasures = p.visibleTreasures;
        this.hiddenTreasures = p.hiddenTreasures;
        this.pendingBadConsequence = p.pendingBadConsequence;
        this.dead = p.dead;
        this.canISteal = p.canISteal;
        this.enemy = p.enemy;
    }
    
    public String getName(){
        return name;
    }
    
    public BadConsequence getPendingBadConsequence(){
        return pendingBadConsequence;
    }
    
    private void bringToLife(){
        dead=false;
    }
    
    public int getCombatLevel(){
        int nivel_total=level;
           
        for(Treasure visibleTreasure : visibleTreasures) {
            nivel_total += visibleTreasure.getBonus();
        }
               
        return nivel_total;         
    }
    
    protected int getOponentLevel(Monster m){
        return m.getCombatLevel();
    }
    
    public Player getEnemy(){
        return this.enemy;
    }
    
    protected boolean shouldConvert(){
        Dice dice=Dice.getInstance();
        if(dice.nextNumber()==1)
            return true;
        else
            return false;
    }
    
    private void incrementLevels(int lvl){
        level=level+lvl;
    }
    
    private void decrementLevels(int lvl){
       if(lvl>=level)
            level = 1;
        else
            level -= lvl;
    }
    
    private void setPendingBadConsequence(BadConsequence b){
        pendingBadConsequence=b;
    }
    
    private void applyPrize(Monster m){
        int nLevels = m.getLevelsGained();
        this.incrementLevels(nLevels);
        int nTreasures = m.getTreasuresGained();
        if(nTreasures>0){
            CardDealer dealer = CardDealer.getInstance();
            for(int i=0; i<nTreasures; i++){
                Treasure treasure = dealer.nextTreasure();
                hiddenTreasures.add(treasure);
            }
        }
    }
    
    private void applyBadConsequence(Monster m){
        BadConsequence badConsequence = m.getBc();
        int nLevels = badConsequence.getLevels();
        this.decrementLevels(nLevels);
        BadConsequence pendingBad = badConsequence.adjustToFitTreasureLists(visibleTreasures, hiddenTreasures);
        this.setPendingBadConsequence(pendingBad);
    }
    
    private boolean canMakeTreasureVisible(Treasure t){
        
       TreasureKind tipo = t.getType();
        // ARMOR
        if(tipo == TreasureKind.ARMOR){
            for(Treasure treasure : visibleTreasures){
                if(treasure.getType() == TreasureKind.ARMOR)
                    return false;
            }
            return true;
        }
        // ONEHAND
        else if(tipo == TreasureKind.ONEHAND){
            int numUnaMano = 0;
            for(Treasure treasure : visibleTreasures){
                if(treasure.getType()==TreasureKind.BOTHHANDS)
                    return false;
                if(treasure.getType() == TreasureKind.ONEHAND)
                    numUnaMano++;
            }
            return numUnaMano <= 1;
        }
        // BOTHHANDS 
        else if(tipo == TreasureKind.BOTHHANDS){
            int numUnaMano = 0;
            for(Treasure treasure : visibleTreasures){
                if(treasure.getType() == TreasureKind.ONEHAND || treasure.getType() == TreasureKind.BOTHHANDS)
                    return false;
            }
            return true;
        }
        // HELMET
        else if(tipo == TreasureKind.HELMET){
            for(Treasure treasure : visibleTreasures){
                if(treasure.getType() == TreasureKind.HELMET)
                    return false;
            }
            return true;
        }
        // SHOES
        else{
            for(Treasure treasure : visibleTreasures){
                if(treasure.getType() == TreasureKind.SHOE)
                    return false;
            }
            return true;
        }
    }
    
    private int howManyVisibleTreasures(TreasureKind tKind){
        int type=0;
        for(int i=0; i<visibleTreasures.size(); i++){
            if(visibleTreasures.get(i).getType()==tKind)
                type++;
        }
        return type;
    }
    
    public void dieIfNoTreasures(){
        if(hiddenTreasures.isEmpty() && visibleTreasures.isEmpty())
            dead=true;
    }
    
    public boolean isDead(){
        return dead;
    }
    
    public ArrayList<Treasure> getHiddenTreasures(){
        return hiddenTreasures;
    }
    
    public ArrayList<Treasure> getVisibleTreasures(){
        return visibleTreasures;
    }
    
    public CombatResult combat(Monster m){
        int myLevel = this.getCombatLevel();
        int monsterLevel = this.getOponentLevel(m);
        if(myLevel>monsterLevel){
            this.applyPrize(m);
            if(this.level>=MAXLEVEL)
                return CombatResult.WINGAME;
            else
                return CombatResult.WIN;
        }
        else{
            this.applyBadConsequence(m);
            
            if(this.shouldConvert())
                return CombatResult.LOSEANDCONVERT;
            else
                return CombatResult.LOSE;
        }
    }
    
    public void makeTreasureVisible(Treasure t){
        boolean canI = this.canMakeTreasureVisible(t);
        if(canI){
            visibleTreasures.add(t);
            hiddenTreasures.remove(t);
        }
    }
    
    public void discardVisibleTreasure(Treasure t){
        visibleTreasures.remove(t);
         if(pendingBadConsequence!=null && !pendingBadConsequence.isEmpty()){
             pendingBadConsequence.substractVisibleTreasure(t);
         }
         else
             this.dieIfNoTreasures();
    }
    
    public void discardHiddenTreasure(Treasure t){
         hiddenTreasures.remove(t);
         if(pendingBadConsequence!=null && !pendingBadConsequence.isEmpty()){
             pendingBadConsequence.substractHiddenTreasure(t);
         }
         else
             this.dieIfNoTreasures();
    }
    
    public boolean validState(){
         if(pendingBadConsequence == null || pendingBadConsequence.isEmpty())
             return (hiddenTreasures.size() <= 4);
         else
             return false;
    }
    
    public void initTreasures(){
        CardDealer dealer = CardDealer.getInstance();
        Dice dice = Dice.getInstance();
        this.bringToLife();
        Treasure treasure = dealer.nextTreasure();
        hiddenTreasures.add(treasure);
        int number = dice.nextNumber();
        if(number>1){
            treasure = dealer.nextTreasure();
            hiddenTreasures.add(treasure);
        }
        if(number==6){
            treasure = dealer.nextTreasure();
            hiddenTreasures.add(treasure);
        }
        
    }
    
    public int getLevels(){
        return level;
    }
    
    public Treasure stealTreasure(){
        boolean canI = this.canISteal();
        if(canI){
            boolean canYou = enemy.canYouGiveMeATreasure();
            if(canYou){
                Treasure treasure = enemy.giveMeATreasure();
                hiddenTreasures.add(treasure);
                this.haveStolen();
                return treasure;
            }
        }
        return null;
    }
    
    //EXAMEN
    public void stealToPreviousPlayer(){
        Napakalaki napa=Napakalaki.getInstance();
        int anterior = napa.getCurrenPlayerIndex();
        anterior--;
        ArrayList<Player> jugadores = napa.getPlayers();
        if(anterior==-1){
            anterior=jugadores.size()-1;
        }
        Player previo = jugadores.get(anterior);
        boolean gotBetter=false;
        int mejorBonus = 0;
        int posBonus=-1;
        for(int i=0; i<previo.getHiddenTreasures().size(); i++){
            if(previo instanceof CultistPlayer){
                if(previo.getHiddenTreasures().get(i).getBonus()>mejorBonus && previo.getHiddenTreasures().get(i).getType()!=TreasureKind.ONEHAND){
                    mejorBonus=previo.getHiddenTreasures().get(i).getBonus();
                    posBonus=i;
                    gotBetter=true;
                }
            }
            else{
                if(previo.getHiddenTreasures().get(i).getBonus()>mejorBonus){
                    mejorBonus=previo.getHiddenTreasures().get(i).getBonus();
                    posBonus=i;
                    gotBetter=true;
                }
            }    
        }
        Treasure mejorTesoro=null;
        
        if(posBonus!=-1)
             mejorTesoro=previo.getHiddenTreasures().get(posBonus);
        
        if(this.canISteal() && gotBetter && mejorTesoro!=null){
            if(this.canMakeTreasureVisible(mejorTesoro)){
                this.visibleTreasures.add(mejorTesoro);
                this.haveStolen();
            }
            else{
                this.hiddenTreasures.add(mejorTesoro);
                this.discardHiddenTreasure(mejorTesoro);
                this.haveStolen();
            }
        }
    }
    //FIN EXAMEN
    
    public void setEnemy(Player enemy){
        this.enemy=enemy;
    }
    
    private Treasure giveMeATreasure(){
        Random rnd=new Random();
        int randomPos=(rnd.nextInt(hiddenTreasures.size()));
        Treasure ret=hiddenTreasures.get(randomPos);
        hiddenTreasures.remove(randomPos);
        return ret;
    }
    
    public boolean canISteal(){
        return canISteal;
    }
    
    private boolean canYouGiveMeATreasure(){
        if(!hiddenTreasures.isEmpty())
            return true;
        else
            return false;
    }
    
    private void haveStolen(){
        canISteal=false;
    }
    
    public void discardAllTreasures(){
        ArrayList<Treasure> visTreasures = new ArrayList(visibleTreasures);
        ArrayList<Treasure> hidTreasures = new ArrayList(hiddenTreasures);
        
        for (Treasure treasureV : visTreasures) {
            this.discardVisibleTreasure(treasureV);
        }
        for (Treasure treasureH : hidTreasures) {
            this.discardHiddenTreasure(treasureH);
        }
        
        this.dieIfNoTreasures();
    }
    
    @Override
    public String toString(){
        return name+"("+this.level+")"+" -> CombatLevel "+Integer.toString(getCombatLevel())+" \n";
    }
    
}
