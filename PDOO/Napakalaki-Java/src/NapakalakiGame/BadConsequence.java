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
public abstract class BadConsequence {
    
    protected String text;
    protected int levels;
    
    public static final int MAXTREASURES = 10;
    
    public BadConsequence(String text, int levels){
        this.text=text;
        this.levels=levels;
    }
    
    public boolean isEmpty(){
        return true;
    }
    
    public String getText(){
        return text;
    }
    
    public int getLevels(){
        return levels;
    }
    
    public void substractVisibleTreasure(Treasure t){

    }
    
    public void substractHiddenTreasure(Treasure t){

    }
    
    public int getNVisibleTreasures(){
        return 0;
    }
    
    public int getNHiddenTreasures(){
        return 0;
    }
    
    public ArrayList<TreasureKind> getSpecificVisibleTreasures(){
        return null;
    }
    
    public ArrayList<TreasureKind> getSpecificHiddenTreasures(){
        return null;
    }
    
    public BadConsequence adjustToFitTreasureLists(ArrayList<Treasure> v, ArrayList<Treasure> h){
        return null;
    }
    
    public String toString(){
        return "Text = " + text + "\nLevels = " + Integer.toString(levels);
    }
   

    
}
