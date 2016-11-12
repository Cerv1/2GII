#encoding: utf-8

require_relative 'BadConsequence.rb'
require_relative 'Prize.rb'
require_relative 'Monster.rb'
require_relative 'TreasureKind.rb'

monsters = Array.new

bc = BadConsequence.newLevelSpecificTreasures("Pierdes tu armadura visible y otra oculta", 0,
      [TreasureKind::ARMOR], [TreasureKind::ARMOR])
    prize = Prize.new(2,1)
    monsters << Monster.new('3 Byakhees de bonanza', 8, bc, prize)

    bc = BadConsequence.newLevelSpecificTreasures("Embobados con el lindo primigenio te descartas de tu casco visible",
      0, [TreasureKind::HELMET], nil)
    prize = Prize.new(1,1)
    monsters << Monster.new('Chibithulhu', 2, bc, prize)

    bc = BadConsequence.newLevelSpecificTreasures("El primordial bostezo contagioso. Pierdes el calzado visible",
      0, [TreasureKind::SHOE], nil)
    prize = Prize.new(1,1)
    monsters << Monster.new('El sopor de Dunwich', 2, bc, prize)

    bc = BadConsequence.newLevelSpecificTreasures("Te atrapan para llevarte de fiesta y te dejan caer en mitad
      del vuelo. Descarta 1 mano visible y 1 mano oculta", 0, [TreasureKind::ONEHAND], [TreasureKind::ONEHAND])
    prize = Prize.new(4,1)
    monsters << Monster.new('Angeles de la noche ibicenca', 14, bc, prize)

    bc = BadConsequence.newLevelNumberOfTreasures("Pierdes todos tus tesoros visibles", 0, 5, 0)
    prize = Prize.new(3,1)
    monsters << Monster.new('El gorron en el umbral', 10, bc, prize)

    bc = BadConsequence.newLevelSpecificTreasures("Pierdes la armadura visible", 0, [TreasureKind::ARMOR], nil)
    prize = Prize.new(2,1)
    monsters << Monster.new('H.P. Munchcraft', 6, bc, prize)

    bc = BadConsequence.newLevelSpecificTreasures("Sientes bichos bajo la ropa. Descarta la armadura visible",
      0, [TreasureKind::ARMOR], nil)
    prize = Prize.new(1,1)
    monsters << Monster.new('Bichgooth', 2, bc, prize)

    bc = BadConsequence.newLevelNumberOfTreasures("Pierdes 5 niveles y 3 tesoros visibles", 5, 3, 0)
    prize = Prize.new(4,2)
    monsters << Monster.new('El rey de rosa', 13, bc, prize)

    bc = BadConsequence.newLevelNumberOfTreasures("Toses los pulmones y pierdes 2 niveles", 2, 0, 0)
    prize = Prize.new(1,1)
    monsters << Monster.new('La que redacta en las tinieblas', 2, bc, prize)

    bc = BadConsequence.newDeath("Estos monstruos resultan bastante superficiales y te aburren mortalmente. Estas muerto")
    prize = Prize.new(2,1)
    monsters << Monster.new('Los hondos', 8, bc, prize)

    bc = BadConsequence.newLevelNumberOfTreasures("Pierdes 2 niveles y 2 tesoros ocultos", 2, 0, 2)
    prize = Prize.new(2,1)
    monsters << Monster.new('Semillas Cthulhu', 4, bc, prize)

    bc = BadConsequence.newLevelSpecificTreasures("Te intentas escaquear. Pierdes una mano visible", 0,
      [TreasureKind::ONEHAND], nil)
    prize = Prize.new(2,1)
    monsters << Monster.new('Dameargo', 1, bc, prize)

    bc = BadConsequence.newLevelNumberOfTreasures("Da mucho asquito. Pierdes 3 niveles", 3, 0, 0)
    prize = Prize.new(1,1)
    monsters << Monster.new('Pollipolipo volante', 3, bc, prize)

    bc = BadConsequence.newDeath("No le hace gracia que pronuncien mal su nombre. Estas muerto")
    prize = Prize.new(3,1)
    monsters << Monster.new('Yskhtihyssg-Goth', 12, bc, prize)

    bc = BadConsequence.newDeath("La familia te atrapa. Estas muerto")
    prize = Prize.new(4,1)
    monsters << Monster.new('Familia feliz', 1, bc, prize)

    bc = BadConsequence.newLevelSpecificTreasures("La quinta directiva primaria te obliga a perder 2 niveles
      y un tesoro 2 manos visible", 2, [TreasureKind::BOTHHANDS], nil)
    prize = Prize.new(2,1)
    monsters << Monster.new('Roboggoth', 8, bc, prize)

    bc = BadConsequence.newLevelSpecificTreasures("Te asusta en la noche. Pierdes un casco visible", 0,
      [TreasureKind::HELMET], nil)
    prize = Prize.new(1,1)
    monsters << Monster.new('El espia', 5, bc, prize)

    bc = BadConsequence.newLevelNumberOfTreasures("Menudo susto te llevas. Pierdes 2 niveles y 5 tesoros visibles",
      2, 5, 0)
    prize = Prize.new(1,1)
    monsters << Monster.new('El Lenguas', 20, bc, prize)

    bc = BadConsequence.newLevelSpecificTreasures("Te faltan manos para tanta cabeza. Pierdes 3 niveles y tus
      tesoros visibles de las manos", 3, [TreasureKind::ONEHAND], nil)
    prize = Prize.new(1,1)
    monsters << Monster.new('Bicefalo', 20, bc, prize)

