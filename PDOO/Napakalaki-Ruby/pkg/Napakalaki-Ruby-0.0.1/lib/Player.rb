#encoding: utf-8

require_relative 'Treasure.rb'
require_relative 'TreasureKind.rb'
require_relative 'BadConsequence.rb'
require_relative 'Napakalaki.rb'
require 'CardDealer.rb'
require_relative 'Dice.rb'
require_relative 'Monster.rb'
require_relative 'Prize.rb'

module NapakalakiGame
class Player
    
    @@MAXLEVEL=10
    
    attr_accessor :pendingBadConsequence, :enemy
    attr_reader :name, :level, :visibleTreasures, :hiddenTreasures, :dead, :canISteal
    
    def self.MAXLEVEL
      return @@MAXLEVEL
    end
    
    def initialize(name)
        @name=name
        @level=1
        @dead=true
        @canISteal=true
        @hiddenTreasures=Array.new
        @visibleTreasures=Array.new
        @pendingBadConsequence=nil
        @enemy=nil
    end
    
    def PlayerCopy(p)
      @name=p.getName
      @level = p.getLevels
      @dead = p.dead
      @hiddenTreasures = p.getHiddenTreasures
      @visibleTreasures = p.getVisibleTreasures
      @pendingBadConsequence = p.pendingBadConsequence
      @enemy=p.enemy
      @canISteal=p.canISteal
    end
    
    private
    
    def bringToLife
        @dead=false
    end
    
    def getOponentLevel(m)
      return m.getCombatLevel
    end
    
    def getCombatLevel
        total=@level
        
        for treasure in @visibleTreasures
            total+=treasure.bonus
        end
        
        return total
    end
    
    def incrementLevels(lvl)
        @level=@level+lvl
    end
    
    def decrementLevels(lvl)
        if((@level-lvl)>1)
            @level=@level-lvl
        else
            @level=1
        end
    end
    
    def setPendingBadConsequence(b)
        @pendingBadConsequence=b
    end
    
    def applyPrize(m)
      nLevels = m.getLevelsGained
      incrementLevels(nLevels)
      nTreasures = m.getTreasuresGained()
      if(nTreasures>0)
        dealer = CardDealer.instance
        for i in (0..nTreasures)
          treasure=dealer.nextTreasure
          @hiddenTreasures << treasure
        end
      end
    end
    
    
    def applyBadConsequence(m)
      badConsequence = m.getBadConsequence
      nLevels = badConsequence.getLevelsBc()
      decrementLevels(nLevels)
      pendingBad = badConsequence.adjustToFitTreasuresLists(@visibleTreasures, @hiddenTreasures)
      setPendingBadConsequence(pendingBad)
    end
    
    def canMakeTreasureVisible(t)
      aux = @visibleTreasures.select { |treas| treas.getType() == t.getType() }
      if(t.getType() == TreasureKind::ONEHAND)
        if((!(@visibleTreasures.select { |treas| treas.getType() == TreasureKind::BOTHHANDS }).empty?))
          return false
        else
          if(aux.length <= 1)
            return true
          else
            return false
          end
        end
      end
      if(t.getType() == TreasureKind::BOTHHANDS)
        if(!(@visibleTreasures.select{ |treas| treas.getType() == TreasureKind::ONEHAND }.empty?))
          return false
        end
      end
      if(aux.length == 1)
        return false
      else 
        return true
      end
    end
    
    def howManyVisibleTreasures(tKind)
        total_visibles=0
        @visibleTreasures.each do |vT|
             if(vT.type == tKind)
                total_visibles=total_visibles+1
             end
        end 
        return total_visibles
    end
    
    def dieIfNoTreasures
        if(@visibleTreasures.empty? && @hiddenTreasures.empty?)
            @dead=true
        end
    end
    
    
    #------------------------ PARTE PÚBLICA  ------------------------
    
    
    public 
   
    def shouldConvert()
      dado=Dice.instance
      if(dado.nextNumber == 1)
          return true
      else
          return false
      end
  end
    
    def getName
        return @name
    end
    
    def isDead
        return @dead
    end
    
    def getHiddenTreasures
        @hiddenTreasures
    end
    
    def getVisibleTreasures
        @visibleTreasures
    end
    
    def combat(m)
      res = 0
      if(getCombatLevel > getOponentLevel(m))
        @pendingBadConsequence = nil
        applyPrize(m)
        if(getLevels >= @@MAXLEVEL)
          res = CombatResult::WINGAME
        else
          res = CombatResult::WIN
        end
      else
        applyBadConsequence(m)
        if(shouldConvert())
          res = CombatResult::LOSEANDCONVERT
        else
          res = CombatResult::LOSE
        end
      end
    return res
    end
    
    def makeTreasureVisible(t)
        canI = canMakeTreasureVisible(t)
        if(canI)
          @visibleTreasures << t
          @hiddenTreasures.delete(t)
        end
    end
    
    def discardVisibleTreasure(t)
      @visibleTreasures.delete(t)
      if(@pendingBadConsequence!=nil && !@pendingBadConsequence.isEmpty)
        @pendingBadConsequence.substractVisibleTreasures(t)
      else
        dieIfNoTreasures
      end
    end
    
    def discardHiddenTreasure(t)
        @hiddenTreasures.delete(t)
      if(@pendingBadConsequence!=nil && !@pendingBadConsequence.isEmpty)
        @pendingBadConsequence.substractHiddenTreasures(t)
      else
        dieIfNoTreasures
      end
    end
    
    def validState
        if(@pendingBadConsequence==nil)
            return true
        end
        
        if(@pendingBadConsequence.isEmpty && (@hiddenTreasures.size()<=4))
            return true
        end
        
        return false
    end
    
    def initTreasures
        dealer = CardDealer.instance
        dice = Dice.instance
        bringToLife
        treasure = dealer.nextTreasure
        @hiddenTreasures << treasure
        number = dice.nextNumber
        if(number>1)
          treasure = dealer.nextTreasure
          @hiddenTreasures << treasure
        end
        if(number==6)
          treasures = dealer.nextTreasure
          @hiddenTreasures << treasure
        end
    end
    
    def getLevels
        return @level
    end
    
    def stealTreasure
        canI = canISteal
        if(canI)
          canYou = @enemy.canYouGiveMeATreasure
          if(canYou)
            treasure = @enemy.giveMeATreasure
            @hiddenTreasures << treasure
            haveStolen
            return treasure
          end
        end
        return nil  
    end
    
    def setEnemy(enemy)
        @enemy=enemy
    end
    
    def giveMeATreasure
        rnd=rand(@hiddenTreasures.size)
        ret=@hiddenTreasures[rnd]
        @hiddenTreasures.delete_at(rnd)
        return ret
    end
    
    def canISteal
        return @canISteal
    end
    
    def canYouGiveMeATreasure
        if(@visibleTreasures.empty?)
            return false
        else
            return true
        end
    end
    
    def haveStolen
        @canISteal=false
    end
    
    def discardAllTreasures
       @visibleTreasures.each do |tV|
          discardVisibleTreasure(tV)
        end
        
      @hiddenTreasures.each do |tH|
        discardHiddenTreasure(tH)
      end
      
        dieIfNoTreasures
    end
    
    def to_s()
      if(@pendingBadConsequence == nil)
        mensaje = "[]"
      else
        mensaje = @pendingBadConsequence.to_s()
      end

      return @name.to_s+"  Nivel:"+@level.to_s() + "\n\nPendingBadConsequnce: "+mensaje
    end
    
    
end
end