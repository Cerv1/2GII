#encoding: utf-8
module NapakalakiGame

    class Cultist
  
        def initialize(name,gainedLevels)
          @name = name
          @gainedLevels = gainedLevels
        end

        attr_reader :gainedLevels
    end
end

