#!/bin/csh -vx
echo "" >> salida.dat
@ i = 1000
while( $i < 15000000 )
./genera $i >> salida.dat
@ i += 50000
end
