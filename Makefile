#Compiler
CC = g++ -g -std=c++11 


#Directories
IDIR = ./input
SRCDIR = ./src
OUTDIR = ./output

#Sources
SOURCES = $(wildcard $(SRCDIR)/*.cpp )
ARGV = $(wildcard $(IDIR)/*.txt )
PDF = $(wildcard $(OUTDIR)/*.pdf )
BSH = $(wildcard $(SRCDIR)/*.sh )
run:
	$(CC) $(SOURCES) -o main && ./main $(ARGV) && mv *.txt $(OUTDIR)
plot:
	chmod a+x $(BSH) && ./$(BSH) && evince *.pdf && mv *.pdf $(OUTDIR) 
clean:
	rm -rf *.data main
