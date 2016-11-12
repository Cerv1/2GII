#encoding: utf-8

require_relative 'TreasureKind.rb'

module NapakalakiGame
class Treasure
    
    attr_reader :name, :bonus, :type
    
    def initialize(name,bonus,type)
        @name=name
        @bonus=bonus
        @type=type
    end
    
    def getType
        return @type
    end
    
    def to_s
        "#{@name} (#{@bonus}-#{@type})"
    end
    
end
end