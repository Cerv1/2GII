#!/bin/csh -vx
rm -f salida10millones-basico.dat
echo "" >> salida10millones-basico.dat
@ i = 1000
while( $i < 1000000 )
./genera-basico $i >> salida10millones-basico.dat
@ i += 50000
end
