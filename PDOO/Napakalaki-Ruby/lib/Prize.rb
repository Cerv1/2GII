#encoding: utf-8

module NapakalakiGame
class Prize
    
    attr_accessor :treasures, :levels
    
    def initialize(treasures, levels)
        @treasures=treasures;
        @levels=levels
    end
    
    def to_s
        "Tesoros: #{@treasures} \nNiveles: #{@levels}" 
    end
    
end
end
