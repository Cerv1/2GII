#encoding: utf-8

require_relative 'BadConsequence.rb'
require_relative 'Prize.rb'

module NapakalakiGame
class Monster
    
    attr_reader :name, :combatLevel, :bc, :price, :levelChangeAgainstCultistPlayer
    
    def initialize(name,level,bads,goods,lC)
      @name = name
      @level = level
      @badconsequence = bads
      @prize = goods
      @levelChangeAgainstCultistPlayer = lC
    end
    
    def self.Monster(name,level,bads,goods)
      new(name,level,bads,goods,0)
    end
    
    def self.MonsterC(name,level,bads,goods,lC)
      new(name,level,bads,goods,lC)
    end
    
    def getCombatLevelAgainstCultistPlayer()
      return getCombatLevel + @levelChangeAgainstCultistPlayer
    end
    
    def getName()
      return @name
    end
    def getCombatLevel()
      return @level
    end
    def getBadConsequence()
      return @badconsequence
    end
    
    def getLevelsGained()
        return @prize.levels
    end
    
    def getTreasuresGained()
        return @prize.treasures
    end

    def to_s
        return "Nombre:"+@name.to_s()+" Nivel:"+@level.to_s()+"\n\tMal rollo: "+@badconsequence.to_s()+"\n\tBuen rollo: "+@prize.to_s()
    end
end
end