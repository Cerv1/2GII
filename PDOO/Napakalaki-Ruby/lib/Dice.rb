# encoding: utf-8

require 'singleton'

module NapakalakiGame
class Dice
    
    include Singleton
    
    def initialize
    
    end
    
    def nextNumber
        return 1+rand(6)
    end
    
    
end
end