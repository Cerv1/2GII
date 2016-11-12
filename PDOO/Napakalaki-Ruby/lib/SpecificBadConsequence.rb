#encoding: utf-8
require_relative 'BadConsequence.rb'

module NapakalakiGame
  class SpecificBadConsequence < BadConsequence
      
    def initialize(text, levels, specVisible, specHidden)
      super(text,levels)
      @specificHiddenTreasures = specHidden
      @specificVisibleTreasures = specVisible
    end
    
    def isEmpty()
       if(@specificHiddenTreasures.length == 0 && @specificVisibleTreasures.length == 0)
         return true
       end
    return false
    end
    
    def getSpecificHiddenTreasures()
      return @specificHiddenTreasures
    end
    
    def getSpecificVisibleTreasures()
      return @specificVisibleTreasures
    end
    
    def substractVisibleTreasures(t)
      n = @specificVisibleTreasures.find_index(t.getType())
      if(n != nil)
        @specificVisibleTreasures.delete_at(n)
      end
    end
    
    def substractHiddenTreasures(t)
      n = @specificHiddenTreasures.find_index(t.getType())
      if(n != nil)
        @specificHiddenTreasures.delete_at(n)
      end
    end
    
    def adjustToFitTreasuresLists(v,h)
      if(@specificHiddenTreasures != nil)
            adHidList = Array.new
        else
            adHidList = nil
        end
        
         if(@specificVisibleTreasures != nil)
            adVisList = Array.new
        else
            adVisList = nil
        end
        
        types = [TreasureKind::HELMET, TreasureKind::ARMOR, TreasureKind::ONEHAND, TreasureKind::BOTHHANDS]
        
        for i in 0..@specificHiddenTreasures.size-1
        types.each do |tesoro|
            if(tesoro == v[i])
                adHidList<<tesoro
            end
        end
        end
        
        for i in 0..@specificVisibleTreasures.size-1
        types.each do |tesoro|
            if(tesoro == h[i])
                adVisList<<tesoro
            end
        end
        end
        
        adjustedbc = SpecificBadConsequence.new(@text, 0, adVisList, adHidList)
        return adjustedbc
    end
    
    def to_s()
      return @text.to_s() +"\n\t\tNiveles:"+@levels.to_s()+"\n\t\tspecHidden:"+@specificHiddenTreasures.to_s()+"\n\t\tspecVisible:"+@specificVisibleTreasures.to_s()
    end
    
  end
end
