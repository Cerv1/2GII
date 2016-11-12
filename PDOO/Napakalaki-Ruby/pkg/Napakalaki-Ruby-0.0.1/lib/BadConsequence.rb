#encoding: utf-8
require_relative 'player.rb'

module NapakalakiGame
    
  class BadConsequence

    @@MAXTREASURES = 10
    
     def self.MAXTREASURES
      return @@MAXTREASURES
    end
    
    def initialize(aText,someLevels)
      @text = aText
      @levels = someLevels
    end
    
    def self.maxtreasures
      return @@MAXTREASURES
    end
    
    def isEmpty()
       raise NotImplementedError.new 
    end
    
    def getLevelsBc()
      return @levels
    end
    
    def substractVisibleTreasures(t)
      raise NotImplementedError.new 
    end
    
    def substractHiddenTreasures(t)
      raise NotImplementedError.new 
    end 

    def adjustToFitTreasuresLists(v,h)
      raise NotImplementedError.new
    end
    
  end
end