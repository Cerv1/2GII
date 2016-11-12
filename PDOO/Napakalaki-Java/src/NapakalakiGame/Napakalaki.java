/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

import java.util.*;

/**
 *
 * @author Usuario
 */
public class Napakalaki {
    
    private static Napakalaki instance = null;
    
    private Player currentPlayer;
    private int currentPlayerIndex;
    private ArrayList<Player> players;
    private CardDealer dealer;
    private Monster currentMonster;
    
    public static Napakalaki getInstance(){
        if(instance==null)
            instance=new Napakalaki();
        return instance;
    }
    
    private Napakalaki(){
        currentPlayer=null;
        currentPlayerIndex=-1;
        players=new ArrayList();
        dealer=CardDealer.getInstance();
        currentMonster=null;
    }
    
    public int getCurrenPlayerIndex(){
        return currentPlayerIndex;
    }
    
    public ArrayList<Player> getPlayers(){
        return players;
    }
    
    private void initPlayers(ArrayList<String> names){
        for(int i=0; i<names.size(); i++){
            String name = names.get(i);
            Player player = new Player(name);
            players.add(player);
        }
    }
    
    private Player nextPlayer(){
        if(currentPlayerIndex==-1){     //Primera jugada
            Random rnd = new Random();
            currentPlayerIndex=(int)(rnd.nextDouble() * players.size());
        }
        else{
            currentPlayerIndex++;
            if(currentPlayerIndex==players.size())
                currentPlayerIndex=0;
        }
        
        currentPlayer=players.get(currentPlayerIndex);
        return currentPlayer;
     }
    
    private boolean nextTurnIsAllowed(){
        if(currentPlayer==null)
            return true;
        
        return currentPlayer.validState();
    }
    
    private void setEnemies(){
        Random rnd = new Random();
        
        for (int i=0; i <players.size(); i++){
            int randomPos = rnd.nextInt(players.size());
            
            while (i == randomPos)
                randomPos = rnd.nextInt(players.size());
            
            players.get(i).setEnemy(players.get(randomPos));
        }
    }
    
   public CombatResult developCombat(){
        Monster m = currentMonster;
        CombatResult combatResult = currentPlayer.combat(m);
        if(combatResult == CombatResult.LOSEANDCONVERT){
            Cultist c = dealer.nextCultist();
            Player p = new CultistPlayer(currentPlayer, c);
            players.add(p);
            players.remove(currentPlayer);
            currentPlayer = p;
        }            
        dealer.giveMonsterBack(m);
        return combatResult;
    }
    
    public void discardVisibleTreasures(ArrayList<Treasure> treasures){
        for(int i=0; i<treasures.size(); i++){
            Treasure treasure = treasures.get(i);
            currentPlayer.discardVisibleTreasure(treasure);
            dealer.giveTreasureBack(treasure);
        }
    }
    
    public void discardHiddenTreasures(ArrayList<Treasure> treasures){
        for(int i=0; i<treasures.size(); i++){
            Treasure treasure = treasures.get(i);
            currentPlayer.discardHiddenTreasure(treasure);
            dealer.giveTreasureBack(treasure);
        }
    }
    
    public void makeTreasuresVisible(ArrayList<Treasure> treasures){
        for(int i=0; i<treasures.size(); i++){
            Treasure t = treasures.get(i);
            currentPlayer.makeTreasureVisible(t);
        }
    }
    
    public void initGame(ArrayList<String> names){
        this.initPlayers(names);
        this.setEnemies();
        dealer.initCards();
        this.nextTurn();
    }
    
    public Player getCurrentPlayer(){
        return currentPlayer;
    }
    
    public Monster getCurrentMonster(){
        return currentMonster;
    }
    
    public boolean nextTurn(){
        boolean stateOK=this.nextTurnIsAllowed();
        if(stateOK){
            currentMonster = dealer.nextMonster();
            currentPlayer = this.nextPlayer();
            boolean dead = currentPlayer.isDead();
            if(dead){
                currentPlayer.initTreasures();
            }
        }
        return stateOK;
    }
    
    public boolean endOfGame(CombatResult result){
        if(result == CombatResult.WINGAME)
            return true;
        return false;
    }
}
