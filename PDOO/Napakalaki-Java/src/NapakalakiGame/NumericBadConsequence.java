/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

import java.util.ArrayList;

/**
 *
 * @author Cervi
 */
public class NumericBadConsequence extends BadConsequence{
    
    private int nVisibleTreasures;
    private int nHiddenTreasures;
    
    public NumericBadConsequence(String text, int levels, int nVisible, int nHidden){
        super(text,levels);
        this.nVisibleTreasures=nVisible;
        this.nHiddenTreasures=nHidden;
    }
    
    public int getNHiddenTreasures(){
        return this.nHiddenTreasures;
    }
    
    public int getNVisibleTreasures(){
        return this.nVisibleTreasures;
    }
    
    @Override
    public void substractVisibleTreasure(Treasure t){
        if(nVisibleTreasures>0)
            nVisibleTreasures--;
    }
    
    @Override
    public void substractHiddenTreasure(Treasure t){
        if(nHiddenTreasures>0)
            nHiddenTreasures--;
    }
    
    @Override
    public BadConsequence adjustToFitTreasureLists(ArrayList<Treasure> v, ArrayList<Treasure> h){
        int nVret, nHret;
        
        int nVis = v.size();
        int nHid = h.size();
        
        if(nVis<nVisibleTreasures)
            nVret=nVis;
        else
            nVret=nVisibleTreasures;
        
        if(nHid<nHiddenTreasures)
            nHret=nHid;
        else
            nHret=nHiddenTreasures;
        
        BadConsequence adjustedBC=new NumericBadConsequence(text,0, nVret, nHret);
        System.out.println("MAL ROLLO AJUSTADO: "+adjustedBC.toString());
        return adjustedBC;
    }
    
    @Override
    public boolean isEmpty(){
        if(nVisibleTreasures == 0 && nHiddenTreasures==0)
            return true;
        else
            return false;
    }
    
    @Override
    public String toString(){
        String description = "--- Mal Rollo  --- \n" + "Texto: " + text + "\n";
            description += "Pérdida de niveles: " + levels + "\n";
            description += "Pérdida de tesoros visibles: " + nVisibleTreasures + "\n";
            description += "Pérdida de tesoros ocultos: " + nHiddenTreasures + "\n";
    
        return description;
    }
}
