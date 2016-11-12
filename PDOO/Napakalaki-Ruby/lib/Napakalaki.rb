#encoding: utf-8

require 'singleton'

require_relative 'Player.rb'
require_relative 'CardDealer.rb'
require_relative 'CombatResult.rb'
require_relative 'Monster.rb'
require_relative 'CultistPlayer.rb'

module NapakalakiGame
    
class Napakalaki
    
    include Singleton
    
    attr_accessor :currentPlayer, :players, :currentMonster, :dealer, :currentPlayerIndex
    
    def initialize
        @currentPlayer=nil
        @currentPlayerIndex=-1
        @players=Array.new
        @dealer=CardDealer.instance
        @currentMonster=nil
    end
    
    private
    
    def initPlayers(names)
        names.each do |name|
            @players << Player.new(name)
        end
    end
    
    def nextPlayer
        if(@currentPlayerIndex==-1)
            rnd=rand(@players.size())
            @currentPlayer=@players[rnd]
            @currentPlayerIndex=rnd
        else
            @currentPlayerIndex=@currentPlayerIndex+1
            if(@currentPlayerIndex==@players.size())
                @currentPlayerIndex=0
            end
        end
        
        @currentPlayer=@players[@currentPlayerIndex]
        return @currentPlayer
    end
    
    def nextTurnIsAllowed
        if(@currentPlayer==nil)
            return true
        else
            return @currentPlayer.validState
        end
    end
    
    def setEnemies
        for i in(0..@players.size() -1)
            n = rand(@players.size())
            while (i == n)
                n = rand(@players.size())
            end
            @players[i].setEnemy(@players[n])
        end
    end
    
    #------------------------ PARTE PÚBLICA  ------------------------
    
    
    public
    
    def developCombat()
      combatresult = @currentPlayer.combat(@currentMonster)
      @dealer.giveMonsterBack(@currentMonster)
      if(combatresult == CombatResult::LOSEANDCONVERT)
        aux = CultistPlayer.new(@currentPlayer,@dealer.nextCultist)
        @players.delete(@currentPlayer)
        @currentPlayer = aux
        @players << aux
      end
      return combatresult
    end
    
    def discardVisibleTreasures(treasures)
        for i in 0..(treasures.size - 1)
          treasure = treasures[i]
          @currentPlayer.discardVisibleTreasure(treasure)
          @dealer.giveTreasureBack(treasure)
        end
    end
    
    def discardHiddenTreasures(treasures)
        for i in 0..(treasures.size - 1)
          treasure = treasures[i]
          @currentPlayer.discardHiddenTreasure(treasure)
          @dealer.giveTreasureBack(treasure)
        end
    end
    
    def makeTreasuresVisible(treasure)
        treasure.each do | t |
          @currentPlayer.makeTreasureVisible(t)
        end
    end
    
    def initGame(names)
        initPlayers(names)
        setEnemies();
        dealer.initCards()
        nextTurn()
    end
    
    def getCurrentPlayer
        return @currentPlayer
    end
    
    def getCurrentMonster
        return @currentMonster
    end
    
    def nextTurn
        stateOK = nextTurnIsAllowed
        if(stateOK)
          @currentMonster =@dealer.nextMonster
          @currentPlayer = nextPlayer
          dead = @currentPlayer.isDead
          if(dead)
            @currentPlayer.initTreasures
          end
        end
        return stateOK
    end
    
    
    def endOfGame(result)
        if(result == CombatResult::WINGAME)
            return true
        else
            return false
        end
    end
    
end
end
