#!/bin/sh
ARQUIVODADOS=/home/pi/le_pot_spi_medidas.txt
ARQUIVOSAIDA=/home/pi/le_pot_spi_medidas.png

gnuplot << EOF
set title "Medidas coletadas do potenciometro no Arduino"
set ylabel "Valor [V]"
set xlabel "Tempo [s]"
set terminal png
set output "$ARQUIVOSAIDA"
plot "$ARQUIVODADOS" \
     linecolor rgb '#0060ad' \
     linetype 1 \
     linewidth 1 \
     pointtype 2 \
     pointsize 1.0 \
     title "le_pot_spi" \
     with linespoints
EOF

