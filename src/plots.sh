#!/bin/bash  
gnuplot <<EOF
set terminal pdf

set key top right
set grid
set output "features.pdf"

set title  "area vs aspect ratio"
set ylabel "area/aspect ratio"
plot 'class1.data' using 1 with line title "class 1",'class2.data' using 2 with line title "class 2"

set title  "area vs gray value"
set ylabel "area/gray value"
plot 'class1.data' using 1 with line title "class 1",'class2.data' using 3 with line title "class 2"

set title  "area vs inner border length"
set ylabel "area/inner border length"
plot 'class1.data' using 1 with line title "class 1",'class2.data' using 4 with line title "class 2"

set title  "gray value vs aspect ratio"
set ylabel "gray value/aspect ratio"
plot 'class1.data' using 2 with line title "class 1",'class2.data' using 3 with line title "class 2"

set title  "aspect ratio vs inner border length"
set ylabel "aspect ratio/inner border length"
plot 'class1.data' using 2 with line title "class 1",'class2.data' using 4 with line title "class 2"

set title "gray value vs inner border length"
set ylabel "gray value/inner border length"
plot 'class1.data' using 3 with line title "class 1",'class2.data' using 4 with line title "class 2"
EOF


