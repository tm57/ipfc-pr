#Tinashe Matate
#Image Processing (ImgProc) 
#Course Fall 2014
#Homework 4 "FEATURE COMPUTATION FOR PATTERN RECOGNITION"

---------------------------------------
In this folder are the solutions to hw3
---------------------------------------

============
/src
============

--------------------
Import.cpp/Import.h
--------------------
reading of the mosaic image,looping through all tiles(implemented in Tile.cpp/.h)
writing to file,"features.txt",and temporary write auxillary files *.data for the plots(technically contains the same data as in features.txt,just easier to gnuplot from).

--------
plots.sh
--------
gnuplot script to auto-plot the 6 subplots

---------------
Tile.cpp/Tile.h
---------------
basic image transformations,segmentation,feature computation,
definition of tile to be used for whole mosaic image

---------
Makefile
---------
To reproduce "features.txt" simply type $make
To reproduce the plot "features.pdf",type $make plot
clean up with $make clean,to get rid of the temporary .data files and the executable

=============
/output
=============
features.txt
features.pdf
answers.txt