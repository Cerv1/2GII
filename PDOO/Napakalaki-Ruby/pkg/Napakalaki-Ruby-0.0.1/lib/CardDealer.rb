#encoding: utf-8

require 'singleton'

require 'Treasure.rb'
require 'TreasureKind.rb'
require 'BadConsequence.rb'
require 'NumericBadConsequence.rb'
require 'SpecificBadConsequence.rb'
require 'DeathBadConsequence.rb'
require 'Napakalaki.rb'
require 'Player.rb'
require 'Dice.rb'
require 'Monster.rb'
require 'Prize.rb'
require 'Cultist.rb'


module NapakalakiGame

class CardDealer
    
    include Singleton 
    
    attr_reader :unusedMonsters, :usedMonsters, :unusedTreasures, :usedTreasures, :unusedCultists, :usedCultists
    
    def initialize
        @unusedMonsters=Array.new
        @unusedTreasures=Array.new
        @usedMonsters=Array.new
        @usedTreasures=Array.new
        @unusedCultists=Array.new
        @usedCultists=Array.new
    end
    
    private
    
    def initCultistCardDeck()
        @unusedCultists << Cultist.new("Cultist",1)
        @unusedCultists << Cultist.new("Cultist",1)
        @unusedCultists << Cultist.new("Cultist",1)
        @unusedCultists << Cultist.new("Cultist",1)
        @unusedCultists << Cultist.new("Cultist",2)
        @unusedCultists << Cultist.new("Cultist",2)
    end
    
    def initTreasureCardDeck
        tesoro = Treasure.new("¡Sí mi amo!", 4, TreasureKind::HELMET)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Botas de investigación", 3, TreasureKind::SHOE)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Capucha de Cthulhu", 3, TreasureKind::HELMET)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("A prueba de babas", 2, TreasureKind::ARMOR)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Botas de lluvia ácida", 1, TreasureKind::BOTHHANDS)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Casco minero", 2, TreasureKind::HELMET)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Ametralladora Thompson", 4, TreasureKind::BOTHHANDS)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Camiseta de la UGR", 1, TreasureKind::ARMOR)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Clavo de rail ferroviario", 3, TreasureKind::ONEHAND)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Cuchillo de sushi arcano", 2, TreasureKind::ONEHAND)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Fez alópodo", 3, TreasureKind::HELMET)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Hacha prehistórica", 2, TreasureKind::ONEHAND)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("El aparato del Pr. Tesla", 4, TreasureKind::ARMOR)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Gaita", 4, TreasureKind::BOTHHANDS)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Insecticida", 2, TreasureKind::ONEHAND)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Escopeta de 3 cañones", 4, TreasureKind::BOTHHANDS)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Garabato místico", 2, TreasureKind::ONEHAND)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("La rebeca metálica", 2, TreasureKind::ARMOR)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Lanzallamas", 4, TreasureKind::BOTHHANDS)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Necrocomicón", 1, TreasureKind::ONEHAND)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Necronomicón", 5, TreasureKind::BOTHHANDS)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Linterna a 2 manos", 3, TreasureKind::BOTHHANDS)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Necrognomicón", 2, TreasureKind::ONEHAND)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Necrotelecom", 2, TreasureKind::HELMET)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Mazo de los antiguos", 3, TreasureKind::ONEHAND)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Necroplayboycón", 3, TreasureKind::ONEHAND)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Porra preternatural", 2, TreasureKind::ONEHAND)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Shogulador", 1, TreasureKind::BOTHHANDS)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Varita de atizamiento", 3, TreasureKind::ONEHAND)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Tentáculo de pega", 2, TreasureKind::HELMET)
        @unusedTreasures << tesoro

        tesoro = Treasure.new("Zapato deja-amigos", 1, TreasureKind::SHOE)
        @unusedTreasures << tesoro 
    end
    
    def initMonsterCardDeck
        pr = Prize.new(2,1)
        bc = NumericBadConsequence.new("Pierdes tu armadura visible y otra oculta", 0, 1, 1)
        @unusedMonsters << Monster.Monster("3 Byakhees de bonanza", 8, bc, pr)

        pr = Prize.new(1, 1)
        bc = SpecificBadConsequence.new("Embobados con el lindo primigenio te descartas de tu casco visible", 0, 
                TreasureKind::HELMET, Array.new)
        @unusedMonsters << Monster.Monster("Chibithulhu", 2, bc, pr)     

        pr = Prize.new(1, 1)
        bc = SpecificBadConsequence.new("El primordial bostezo contagioso. Pierdes el calzado visible. ", 0,
                    TreasureKind::SHOE, Array.new)
        @unusedMonsters<< Monster.Monster("El sopor de Dunwich", 2, bc, pr)

        pr = Prize.new(4, 1)
        bc = SpecificBadConsequence.new("Te atrapan para llevarte de fiesta y te dejan caer en mitad del vuelo. 
                  Descarta 1 mano visible y 1 mano oculta", 0,  TreasureKind::ONEHAND, TreasureKind::ONEHAND)
        @unusedMonsters << Monster.Monster("Ángeles de la noche ibicenca ", 14, bc ,pr)

        pr = Prize.new(3, 1)
        bc = NumericBadConsequence.new("Pierdes todos tus tesoros visibles. ", 0, 100, 0)
        @unusedMonsters << Monster.Monster("El gorrón en el umbral ", 10, bc ,pr)

        pr = Prize.new(2, 1)
        bc = SpecificBadConsequence.new("Pierdes la armadura visible. ",0 , TreasureKind::ARMOR,  Array.new)
        @unusedMonsters << Monster.Monster("H.P Munchcraft ", 6, bc ,pr)

        pr = Prize.new(1, 1)
        bc = SpecificBadConsequence.new("Sientes bichos bajo la ropa. Descarta la armadura visible. ", 0, 
                  TreasureKind::ARMOR,  Array.new)
        @unusedMonsters << Monster.Monster("Bichgooth " , 2, bc ,pr)

        pr = Prize.new(4, 2)
        bc = NumericBadConsequence.new("Pierdes 5 niveles y 3 tesoros visibles. ", 5, 3, 0)
        @unusedMonsters << Monster.Monster("El rey de rosa ", 13, bc ,pr)

        pr = Prize.new(1, 1)
        bc = NumericBadConsequence.new("Toses los pulmones y pierdes 2 niveles. ", 2, 0, 0)
        @unusedMonsters << Monster.Monster("La que redacta en las tinieblas ", 2, bc ,pr)

        pr = Prize.new(2, 1)
        bc = DeathBadConsequence.new("Estos monstruos resultan bastante superficiales y te aburren mortalmente. Estás muerto. ")
        @unusedMonsters << Monster.Monster("Los hondos ", 8, bc, pr)

        pr = Prize.new(2, 1)
        bc = NumericBadConsequence.new("Pierdes 2 niveles y 2 tesoros ocultos. ", 2, 0, 2)
        @unusedMonsters << Monster.Monster("Semillas Cthulhu ", 4, bc ,pr)

        pr = Prize.new(2, 1)
        bc = SpecificBadConsequence.new("Te intentas escaquear. Pierdes una mano visible. " , 0, 
                      TreasureKind::ONEHAND,  Array.new)
        @unusedMonsters << Monster.Monster("Dameargo ", 1, bc ,pr)

        pr = Prize.new(1, 1)
        bc = BadConsequence.new("Da mucho asquito. Pierdes 3 niveles. ", 3)
        @unusedMonsters << Monster.Monster("Pollipólipo volante ", 3, bc ,pr)

        pr = Prize.new(3, 1)
        bc = DeathBadConsequence.new("No le hace gracia que pronuncien mal su nombre. Estás muerto. ")
        @unusedMonsters << Monster.Monster("Yskhtihyssg-Goth ", 12, bc ,pr)

        pr = Prize.new(4, 1)
        bc = DeathBadConsequence.new("La familia te atrapa. Estás muerto. ")
        @unusedMonsters << Monster.Monster("Familia feliz ", 1, bc ,pr)

        pr = Prize.new(2, 1)
        bc = SpecificBadConsequence.new("La quinta directiva primaria te obliga a perder 2 niveles y un
                    tesoro 2 manos visible. ", 2, TreasureKind::BOTHHANDS,  Array.new)
        @unusedMonsters << Monster.Monster("Roboggoth ", 8, bc ,pr)

        pr = Prize.new(1, 1)
        bc  = SpecificBadConsequence.new("Te asusta en la noche. Pierdes un casco visible. ", 0, 
                    TreasureKind::HELMET,  Array.new)
        @unusedMonsters << Monster.Monster("El espía ", 5, bc,pr)

        pr = Prize.new(1, 1)
        bc = NumericBadConsequence.new("Menudo susto te llevas. Pierdes 2 niveles y 5 tesoros visibles. ", 2, 5, 0)
        @unusedMonsters << Monster.Monster("El lenguas ", 20, bc ,pr)

        pr = Prize.new(1, 1)
        bc = SpecificBadConsequence.new("Te faltan manos para tanta cabeza. Pierdes 3 niveles y tus tesoros visibles de las manos. ", 
                    3, TreasureKind::BOTHHANDS,  Array.new)
        @unusedMonsters << Monster.Monster("Bicéfalo ", 20, bc ,pr)

          #CULTISTS

        pr = Prize.new(2,1)
        bc = NumericBadConsequence.new("Pierdes tus tesoros visibles. Jajaja.",0,BadConsequence.MAXTREASURES, 0)
        @unusedMonsters << Monster.MonsterC("Testigos Oculares",6,bc,pr,+2)

        pr = Prize.new(2,5)
        bc = DeathBadConsequence.new("Hoy no es tu día de suerte. Mueres.")
        @unusedMonsters << Monster.MonsterC("El gran cthulhu",20,bc,pr,+4)

        pr = Prize.new(2,1)
        bc = NumericBadConsequence.new("Tu gobierno te recorta 2 niveles.", 2, 0,0)
        @unusedMonsters << Monster.MonsterC("Serpiente Político",8,bc,pr,-2)

        pr = Prize.new(1,1)
        bc = SpecificBadConsequence.new("Pierdes tu casco y tu armadura visible. Pierdes tus manos ocultas.",0,[TreasureKind::ARMOR,TreasureKind::HELMET],[TreasureKind::BOTHHANDS])
        @unusedMonsters << Monster.MonsterC("Felpuggoth",2,bc,pr,+5)

        pr = Prize.new(4,2)
        bc = NumericBadConsequence.new("Pierdes 2 niveles",2,0,0)
        @unusedMonsters << Monster.MonsterC("Shoggoth",16,bc,pr,-4)

        pr = Prize.new(1,1)
        bc = NumericBadConsequence.new("Pintalabios negro. Pierdes 2 niveles.",2,0,0)
        @unusedMonsters << Monster.MonsterC("Lolitagooth",2,bc,pr,+3)
    end
    
    def shuffleTreasures
        @unusedTreasures.shuffle!
    end
    
    def shuffleMonsters
        @unusedMonsters.shuffle!
    end
    
    def shuffleCultists
      @unusedCultists.shuffle!
    end
    
    
    #------------------------ PARTE PÚBLICA  ------------------------
    
    public 
    
    
    def nextTreasure
        if(@unusedTreasures.length() == 0)
        @usedTreasures.each do |t|
          @unusedTreasures << @usedTreasures.delete(t)
        end
        shuffleTreasures
      end
      return @unusedTreasures.delete_at(0)
    end
    
    def nextMonster
        if(@unusedMonsters.length() == 0)
        @usedMonster.each do |m|
          @unusedMonsters << @usedMonster.delete(m)
        end
        shuffleMonsters
      end
      return @unusedMonsters.delete_at(0)
    end
    
    def nextCultist
      return @unusedCultists.delete_at(0)
    end
    
    def giveTreasureBack(t)
        @usedTreasures << t
    end
    
    def giveMonsterBack(m)
        @usedMonsters << m
    end
    
    def initCards
        initTreasureCardDeck
        initMonsterCardDeck
        initCultistCardDeck
        shuffleTreasures
        shuffleMonsters
        shuffleCultists
    end
    
 end   
end
