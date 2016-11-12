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
public class CardDealer {
    
    private static CardDealer instance = null;
    
    private ArrayList<Treasure> unusedTreasures=null;
    private ArrayList<Treasure> usedTreasures=null;
    private ArrayList<Monster> unusedMonsters=null;
    private ArrayList<Monster> usedMonsters=null;
    private ArrayList<Cultist> unusedCultists=null;
    private ArrayList<Cultist> usedCultists=null;
    
    
    public static CardDealer getInstance(){
        if(instance==null)
            instance=new CardDealer();
        return instance;
    }
    
    private CardDealer(){
        unusedTreasures=new ArrayList();
        usedTreasures=new ArrayList();
        unusedMonsters=new ArrayList();
        usedMonsters=new ArrayList();
        unusedCultists=new ArrayList();
        usedCultists=new ArrayList();
    }
    
    private void initCultistCardDeck(){
        unusedCultists.add(new Cultist("Cultist",1));
        unusedCultists.add(new Cultist("Cultist",1));
        unusedCultists.add(new Cultist("Cultist",1));
        unusedCultists.add(new Cultist("Cultist",1));
        unusedCultists.add(new Cultist("Cultist",2));
        unusedCultists.add(new Cultist("Cultist",2));
        
        shuffleCultists();
    }
    
    private void initTreasureCardDeck(){
        Treasure T1 = new Treasure("¡Sí mi amo!", 4, TreasureKind.HELMET);
        unusedTreasures.add(T1);
        Treasure T2 = new Treasure("Botas de investigación", 3, TreasureKind.SHOE);
        unusedTreasures.add(T2);
        Treasure T3 = new Treasure("Capucha de Cthulhu", 3, TreasureKind.HELMET);
        unusedTreasures.add(T3);
        Treasure T4 = new Treasure("A prueba de babas", 2, TreasureKind.ARMOR);
        unusedTreasures.add(T4);
        Treasure T5 = new Treasure("Botas de lluvia ácida", 1, TreasureKind.SHOE);
        unusedTreasures.add(T5);
        Treasure T6 = new Treasure("Casco minero", 2, TreasureKind.HELMET);
        unusedTreasures.add(T6);
        Treasure T7 = new Treasure("Ametralladora Thompson", 4, TreasureKind.BOTHHANDS);
        unusedTreasures.add(T7);
        Treasure T8 = new Treasure("Camiseta de la UGR", 1, TreasureKind.ARMOR);
        unusedTreasures.add(T8);
        Treasure T9 = new Treasure("Clavo de rail ferroviario", 3, TreasureKind.ONEHAND);
        unusedTreasures.add(T9);
        Treasure T10 = new Treasure("Cuchillo de sushi arcano", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(T10);
        Treasure T11 = new Treasure("Fez alópodo", 3, TreasureKind.HELMET);
        unusedTreasures.add(T11);
        Treasure T12 = new Treasure("Hacha prehistórica", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(T12);
        Treasure T13 = new Treasure("El aparato del Pr. Tesla", 4, TreasureKind.ARMOR);
        unusedTreasures.add(T13);
        Treasure T14 = new Treasure("Gaita", 4, TreasureKind.BOTHHANDS);
        unusedTreasures.add(T14);
        Treasure T15 = new Treasure("Insecticida", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(T15);
        Treasure T16 = new Treasure("Escopeta de 3 cañones", 4, TreasureKind.BOTHHANDS);
        unusedTreasures.add(T16);
        Treasure T17 = new Treasure("Garabato místico", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(T17);
        Treasure T18 = new Treasure("La rebeca metálica", 2, TreasureKind.ARMOR);
        unusedTreasures.add(T18);
        Treasure T19 = new Treasure("Lanzallamas", 4, TreasureKind.BOTHHANDS);
        unusedTreasures.add(T19);
        Treasure T20 = new Treasure("Necrocomicón", 1, TreasureKind.ONEHAND);
        unusedTreasures.add(T20);
        Treasure T21 = new Treasure("Necronomicón", 5, TreasureKind.BOTHHANDS);
        unusedTreasures.add(T21);
        Treasure T22 = new Treasure("Linterna a 2 manos", 3, TreasureKind.BOTHHANDS);
        unusedTreasures.add(T22);
        Treasure T23 = new Treasure("Necrognomicón", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(T23);
        Treasure T24 = new Treasure("Necrotelecom", 2, TreasureKind.HELMET);
        unusedTreasures.add(T24);
        Treasure T25 = new Treasure("Mazo de los antiguos", 3, TreasureKind.ONEHAND);
        unusedTreasures.add(T25);
        Treasure T26 = new Treasure("Necroplayboycón", 3, TreasureKind.ONEHAND);
        unusedTreasures.add(T26);
        Treasure T27 = new Treasure("Porra preternatural", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(T27);
        Treasure T28 = new Treasure("Shogulador", 1, TreasureKind.BOTHHANDS);
        unusedTreasures.add(T28);
        Treasure T29 = new Treasure("Varita de atizamiento", 3, TreasureKind.ONEHAND);
        unusedTreasures.add(T29);
        Treasure T30 = new Treasure("Tentáculo de pega", 2, TreasureKind.HELMET);
        unusedTreasures.add(T30);
        Treasure T31 = new Treasure("Zapato deja-amigos", 1, TreasureKind.SHOE);
        unusedTreasures.add(T31);  
        
        shuffleTreasures();
    }
    
    private void initMonsterCardDeck(){
        
        BadConsequence BC1 = new SpecificBadConsequence("Pierdes tu armadura visible y otra oculta", 0,
                             new ArrayList(Arrays.asList(TreasureKind.ARMOR)),
                             new ArrayList(Arrays.asList(TreasureKind.ARMOR)));
        Prize P1 = new Prize(2,1);
        unusedMonsters.add(new Monster("3 Byakhees de bonanza", 8, BC1, P1,0));
        
        BadConsequence BC2 = new SpecificBadConsequence("Embobados con el lindo primigenio te descartas "
                                 + "de tu casco visible", 0, 
                             new ArrayList(Arrays.asList(TreasureKind.HELMET)),
                             new ArrayList()); 
        Prize P2 = new Prize(1,1);
        unusedMonsters.add(new Monster("Chibithulhu", 2, BC2, P2,0));        
      
        BadConsequence BC3 = new SpecificBadConsequence("El primordial bostezo contagioso. Pierdes el"
                                 + " calzado visible", 0, 
                             new ArrayList(Arrays.asList(TreasureKind.SHOE)),
                             new ArrayList());
        Prize P3 = new Prize(1,1);
        unusedMonsters.add(new Monster("El sopor de Dunwich", 2, BC3, P3,0));
        
        BadConsequence BC4 = new SpecificBadConsequence("Te atrapan para llevarte de fiesta y te"
                             + " dejan caer\n en mitad del vuelo. Descarta 1 mano visible y"
                             + " 1 mano oculta", 0, 
                             new ArrayList(Arrays.asList(TreasureKind.ONEHAND)),
                             new ArrayList(Arrays.asList(TreasureKind.ONEHAND)));
        Prize P4 = new Prize(4,1);
        unusedMonsters.add(new Monster("Angeles de la noche ibicenca", 14, BC4, P4,0));
        
        BadConsequence BC5 = new SpecificBadConsequence("Pierdes todos tus tesoros visibles", 0,
                             new ArrayList(Arrays.asList(TreasureKind.ARMOR, TreasureKind.BOTHHANDS,
                             TreasureKind.HELMET, TreasureKind.ONEHAND,
                             TreasureKind.SHOE)), new ArrayList());
        Prize P5 = new Prize(3,1);
        unusedMonsters.add(new Monster("El gorron en el umbral", 10, BC5, P5,0));
                        
        BadConsequence BC6 = new SpecificBadConsequence("Pierdes la armadura visible", 0, 
                             new ArrayList(Arrays.asList(TreasureKind.ARMOR)),
                             new ArrayList());
        Prize P6 = new Prize(1,1);
        unusedMonsters.add(new Monster("H.P. Munchcraft", 6, BC6, P6,0));

        BadConsequence BC7 = new SpecificBadConsequence("Sientes bichos bajo la ropa. Descarta la"
                             + "armadura visible", 0, 
                             new ArrayList(Arrays.asList(TreasureKind.ARMOR)),
                             new ArrayList());
        Prize P7 = new Prize(1,1);
        unusedMonsters.add(new Monster("Bichgooth", 2, BC7, P7,0));
        
        BadConsequence BC8 = new NumericBadConsequence("Pierdes 5 niveles y 3 tesoros visibles", 5, 3, 0);
        Prize P8 = new Prize(4,2);
        unusedMonsters.add(new Monster("El rey de rosa", 13, BC8, P8,0));
        
        BadConsequence BC9 = new NumericBadConsequence("Toses los pulmones y pierdes 2 niveles", 2, 0, 0);
        Prize P9 = new Prize(1,1);
        unusedMonsters.add(new Monster("La que redacta en las tinieblas", 2, BC9, P9,0));
        
        BadConsequence BC10 = new DeathBadConsequence("Estos monstruos resultan bastante superfic"
                             + "iales\n y te aburren mortalmente. Estas muerto");
        Prize P10 = new Prize(2,1);
        unusedMonsters.add(new Monster("Los hondos", 8, BC10, P10,0));
        
        BadConsequence BC11 = new NumericBadConsequence("Pierdes 2 niveles y 2 tesoros ocultos", 2, 0, 2);
        Prize P11 = new Prize(2,1);
        unusedMonsters.add(new Monster("Semillas Cthulhu", 4, BC11, P11,0));
        
        BadConsequence BC12 = new SpecificBadConsequence("Te intentas escaquear. Pierdes una mano visible.", 0, 
                             new ArrayList(Arrays.asList(TreasureKind.ONEHAND)), new ArrayList());
        Prize P12 = new Prize(2,1);
        unusedMonsters.add(new Monster("Dameargo", 1, BC12, P12,0));  
        
        BadConsequence BC13 = new NumericBadConsequence("Da mucho asquito. Pierdes 3 niveles.", 3, 0, 0);
        Prize P13 = new Prize(1,1);
        unusedMonsters.add(new Monster("Pollipolipo volante", 3, BC13, P13,0));
        
        BadConsequence BC14 = new DeathBadConsequence("No le hace gracia que pronuncien mal su nombre"
                               + ". Estás muerto.");
        Prize P14 = new Prize(3,1);
        unusedMonsters.add(new Monster("YskhtihyssgGoth", 12, BC14, P14,0));
         
        BadConsequence BC15 = new DeathBadConsequence("La familia te atrapa. Estás muerto.");
        Prize P15 = new Prize(4,1);
        unusedMonsters.add(new Monster("Familia feliz", 1, BC15, P15,0));
        
        BadConsequence BC16 = new SpecificBadConsequence("La quinta directiva primaria te obliga a \nperder 2 "
                              + "niveles y un tesoro 2 manos visible.", 2, 
                              new ArrayList(Arrays.asList(TreasureKind.BOTHHANDS)),
                              new ArrayList());
        Prize P16 = new Prize(2,1);
        unusedMonsters.add(new Monster("Roboggoth", 8, BC16, P16,0));
        
        BadConsequence BC17 = new SpecificBadConsequence("Te asusta en la noche. Pierdes un casco visible. ",0,
                              new ArrayList(Arrays.asList(TreasureKind.HELMET)),
                              new ArrayList());
        Prize P17 = new Prize(1,1);
        unusedMonsters.add(new Monster("El espia", 5, BC17, P17,0));
        
        BadConsequence BC18 = new NumericBadConsequence("Menudo susto te llevas. Pierdes 2 niveles y 5 "
                              +" tesoros visibles. ", 2, 5, 0);
        Prize P18 = new Prize(1,1);
        unusedMonsters.add(new Monster("El lenguas", 20, BC18, P18,0));
        
        BadConsequence BC19 = new SpecificBadConsequence("Te faltan manos para tanta cabeza. \nPierdes 3 "
                              +"niveles y tus tesoros visibles de las manos. ", 3,
                              new ArrayList(Arrays.asList(TreasureKind.BOTHHANDS)),
                              new ArrayList());
        Prize P19 = new Prize(1,1);
        unusedMonsters.add(new Monster("Bicefalo", 20, BC19, P19,0));
        
        //CULTIST
        BadConsequence bc;
        Prize prize;
        
        ArrayList<TreasureKind> tVisible = new ArrayList();
        ArrayList<TreasureKind> tHidden = new ArrayList();
       
       tVisible.add(TreasureKind.ONEHAND);
       bc = new SpecificBadConsequence("Pierdes 1 mano visible",0,tVisible,null);
       prize = new Prize(3,1);
       unusedMonsters.add(new Monster("El mal indecible impronunciable",10,bc,prize,-2));
       
       tVisible = new ArrayList();
       
       bc = new NumericBadConsequence("Pierdes tus tesoros visibles. Jajaja.",0,BadConsequence.MAXTREASURES,0);
       prize = new Prize(2,1);
       unusedMonsters.add(new Monster("Testigos Oculares",6,bc,prize,+2));
       
       bc = new DeathBadConsequence("Hoy no es tu día de suerte. Mueres.");
       prize = new Prize(2,5);
       unusedMonsters.add(new Monster("El gran chulhu",20,bc,prize,+4));
       
       bc = new NumericBadConsequence("Tu gobierno te recorta 2 niveles.",2,0,0);
       prize = new Prize(2,1);
       unusedMonsters.add(new Monster("Serpiente Político",8,bc,prize,-2));
       
       tVisible.add(TreasureKind.ARMOR);
       tVisible.add(TreasureKind.HELMET);
       tHidden.add(TreasureKind.BOTHHANDS);
       bc = new SpecificBadConsequence("Pierdes tu casco y tu armadura visible. Pierdes tus manos ocultas.",0,tVisible,tHidden);
       prize = new Prize(1,1);
       unusedMonsters.add(new Monster("Felpuggoth",2,bc,prize,+5));
       
       bc = new NumericBadConsequence("Pierdes 2 niveles.",2,0,0);
       prize = new Prize(4,2);
       unusedMonsters.add(new Monster("Shoggoth",16,bc,prize,-4));
       
       bc = new NumericBadConsequence("Pintalabios negro. Pierdes 2 niveles.",2,0,0);
       prize = new Prize(1,1);
       unusedMonsters.add(new Monster("Lolitagooth",2,bc,prize,+3));
       
       shuffleMonsters();
    }
    
    private void shuffleTreasures(){
       Collections.shuffle(unusedTreasures);
    }
    
    private void shuffleMonsters(){
        Collections.shuffle(unusedMonsters);
    }
    
    private void shuffleCultists(){
        Collections.shuffle(unusedCultists);
    }
    
    public Treasure nextTreasure(){
        if(unusedTreasures.isEmpty()){
            unusedTreasures=usedTreasures;
            usedTreasures=new ArrayList();
            shuffleTreasures();
        }
        Treasure nextTreasure = unusedTreasures.get(0);
        unusedTreasures.remove(nextTreasure);
        usedTreasures.add(nextTreasure);
        return nextTreasure;        
    }
    
    public Monster nextMonster(){
        if(unusedMonsters.isEmpty()){
            unusedMonsters=usedMonsters;
            usedMonsters=new ArrayList();
            shuffleMonsters();
        }
        Monster nextMonster = unusedMonsters.get(0);
        unusedMonsters.remove(nextMonster);
        usedMonsters.add(nextMonster);
        return nextMonster;   
    }
    
    public Cultist nextCultist(){
        if(unusedCultists.isEmpty()){
            unusedCultists=usedCultists;
            usedCultists=new ArrayList();
            shuffleCultists();
        }
        Cultist nextCultist = unusedCultists.get(0);
        unusedCultists.remove(nextCultist);
        usedCultists.add(nextCultist);
        return nextCultist;      
    }
    
    public void giveTreasureBack(Treasure t){
        usedTreasures.add(t); 
        unusedTreasures.remove(t);
    }
    
    public void giveMonsterBack(Monster m){
        usedMonsters.add(m);
        unusedMonsters.remove(m);
    }
    
    public void initCards(){
        this.initTreasureCardDeck();
        this.initMonsterCardDeck();
        this.initCultistCardDeck();
    }
}
