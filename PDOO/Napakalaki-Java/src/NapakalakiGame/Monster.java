/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

/**
 *
 * @author Usuario
 */
public class Monster {
    
    private String name;
    private int combatLevel;
    private BadConsequence bc;
    private Prize price;
    private int levelChangeAgainstCultistPlayer = 0;
    
    public Monster(String name, int combatLevel, BadConsequence bc, Prize price){
        this.name=name;
        this.combatLevel=combatLevel;
        this.bc=bc;
        this.price=price;
        this.levelChangeAgainstCultistPlayer=0;
    }
    
    public Monster(String n, int cL, BadConsequence bc, Prize p, int IC){
        this.name=n;
        this.combatLevel=cL;
        this.bc=bc;
        this.price=p;
        this.levelChangeAgainstCultistPlayer=IC;
    }

    public String getName() {
        return name;
    }

    public int getCombatLevel() {
        return combatLevel;
    }
    
    public int getCombatLevelAgainstCultistPlayer(){
        return (this.combatLevel+this.levelChangeAgainstCultistPlayer);
    }

    public BadConsequence getBc() {
        return bc;
    }

    public Prize getPrice() {
        return price;
    }
    
    @Override
    public String toString(){
        return "Nombre = " + this.getName() + "\nNivel de combate = " + Integer.toString(combatLevel) + 
                "\n " + bc.toString() + "\n" + price.toString();
    }
    
    public int getLevelsGained(){
        return price.getLevel();
    }
    
    public int getTreasuresGained(){
        return price.getTreasures();
    }
}
