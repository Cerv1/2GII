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
public class SpecificBadConsequence extends BadConsequence{
    
    private ArrayList<TreasureKind> specificVisibleTreasures = new ArrayList();
    private ArrayList<TreasureKind> specificHiddenTreasures = new ArrayList();
    
    public SpecificBadConsequence(String text, int levels, ArrayList<TreasureKind> v, ArrayList<TreasureKind> h){
        super(text,levels);
        this.specificVisibleTreasures=v;
        this.specificHiddenTreasures=h;
    }
    
    public ArrayList<TreasureKind> getSpecificVisibleTreasures(){
        return this.specificVisibleTreasures;
    }
    
    public ArrayList<TreasureKind> getSpecificHiddenTreasures(){
        return this.specificHiddenTreasures;
    }
    
    @Override
    public boolean isEmpty(){
       if((specificHiddenTreasures==null && specificVisibleTreasures==null)||(specificHiddenTreasures.isEmpty() && specificVisibleTreasures.isEmpty()))
            return true;
       else
            return false;
    }
    
    @Override
    public void substractVisibleTreasure(Treasure t){
        if(specificVisibleTreasures!=null)
            specificVisibleTreasures.remove(t.getType());
    }
    
     @Override
    public void substractHiddenTreasure(Treasure t){
        if(specificHiddenTreasures!=null)
            specificHiddenTreasures.remove(t.getType());
    }

    
    @Override
    public BadConsequence adjustToFitTreasureLists(ArrayList<Treasure> v, ArrayList<Treasure> h){
        BadConsequence bcAjustado;
        if(v.isEmpty() && h.isEmpty()){
            bcAjustado=new SpecificBadConsequence(this.text,0,new ArrayList(),new ArrayList());
            return bcAjustado;
        }else{
            ArrayList<TreasureKind> adjustspecificV=new ArrayList();
            ArrayList<TreasureKind> adjustspecificH=new ArrayList();
                
            for(int i=0; i<v.size(); i++){
                for(int j=0; j<this.specificVisibleTreasures.size(); j++){
                    if(v.get(i).getType()==this.specificVisibleTreasures.get(j))
                        adjustspecificV.add(this.specificVisibleTreasures.get(j));
                }
            }
                
            for(int i=0; i<h.size(); i++){
                for(int j=0; j<this.specificHiddenTreasures.size(); j++){
                    if(h.get(i).getType()==this.specificHiddenTreasures.get(j))
                        adjustspecificH.add(this.specificHiddenTreasures.get(j));
                }
            }
        
            bcAjustado = new SpecificBadConsequence(text, 0, adjustspecificV, adjustspecificH);
            return bcAjustado;
        }

    }
    
    @Override
    public String toString(){
        String description = "--- Mal Rollo --- \n" + "Texto: " + text + "\n";
        if(levels != 0)
            description += "Pérdida de niveles: " + levels + "\n";
        if(specificVisibleTreasures != null)
            description += "Lista tesoros visibles: " + specificVisibleTreasures.toString() + "\n";
        if(specificHiddenTreasures != null)
            description += "Lista tesoros ocultos: " + specificHiddenTreasures.toString() + "\n";
                
        return description;
    }
}
