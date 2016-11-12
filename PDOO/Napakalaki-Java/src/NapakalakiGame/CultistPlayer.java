/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

import java.util.*;

/**
 *
 * @author Cervi
 */
public class CultistPlayer extends Player{
    
    static private int totalCultistPlayers = 0;
    private Cultist myCultistCard;
    
    public CultistPlayer(Player p, Cultist c){
        super(p);
        this.myCultistCard=c;
        totalCultistPlayers++;
    }
    
    
    public int getCombatLevel(){
        int returnLevel=(int) (super.getCombatLevel()+(super.getCombatLevel()*0.2));
        returnLevel+=myCultistCard.getGainedLevels()*totalCultistPlayers;
        return returnLevel;
    }
    
    @Override
    protected int getOponentLevel(Monster m){
        return m.getCombatLevelAgainstCultistPlayer();
    }
    
    @Override
    protected boolean shouldConvert(){
        return false;
    }
    
    private Treasure giveMeATreasure(){
        Random rand = new Random(); 
        return visibleTreasures.get(rand.nextInt(visibleTreasures.size()-1));
    }
    
    private boolean canYouGiveMeATreasure(){
        return (!visibleTreasures.isEmpty() || visibleTreasures != null);
    }
    
    public int getTotalCultistPlayers(){
        return totalCultistPlayers;
    }
}
