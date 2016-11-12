#encoding: utf-8

require 'BadConsequence.rb'
require 'Treasure.rb'

module NapakalakiGame
    
  class NumericBadConsequence < BadConsequence
      
    def initialize(text,levels,nVisible,nHidden)
      super(text,levels)
      @nHiddenTreasures = nHidden
      @nVisibleTreasures = nVisible
    end
    
    def isEmpty()
       if(@nVisibleTreasures == 0 && @nHiddenTreasures == 0)
         return true
       end
    return false
    end
    
    def getNVisibleTreasures()
      return @nVisibleTreasures
    end
    
    def getNHiddenTreasures()
      return @nHiddenTreasures
    end
    
    def substractVisibleTreasures(t)
      @nVisibleTreasures -= 1
    end
    
    def substractHiddenTreasures(t)
      @nHiddenTreasures -= 1
    end
    
    def adjustToFitTreasuresLists(visible,hidden)
      if(@nVisibleTreasures <= visible.length)
        vRet = @nVisibleTreasures
      else
        vRet = visible.length
      end
      if(@nHiddenTreasures <= hidden.length)
        hRet = @nHiddenTreasures
      else
        hRet = hidden.length
      end
      ret = NumericBadConsequence.new(@text,0, vRet, hRet)
      return ret
    end
    
    def to_s()
      return @text.to_s() +"\n\t\tNiveles:"+@levels.to_s()+"\n\t\tnHidden:"+@nHiddenTreasures.to_s()+"\n\t\tnVisible:"+@nVisibleTreasures.to_s()
    end
    
  end
end
