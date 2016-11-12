#encoding: utf-8
require_relative 'BadConsequence.rb'
require_relative 'NumericBadConsequence.rb'
require_relative 'Player.rb'

module NapakalakiGame
  
    class DeathBadConsequence < NumericBadConsequence
      
    def initialize(text)
      super(text,Player.MAXLEVEL,BadConsequence.MAXTREASURES,BadConsequence.MAXTREASURES)
    end
    
  end
end
