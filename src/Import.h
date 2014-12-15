#ifndef __H_IMPORT__H__
#define __H_IMPORT__H__
#include "Tile.h"
#include <vector>
#include <algorithm>
#define BUF_SIZE 4096
#define NUM_ROWS 64

class Import{
private:
	std::string filename;
	std::vector<Tile> image;
public:
	void read_file();
	void write_to_file();
	void write_to_filep();
	std::vector<int> tokenize(char* line);
	inline std::vector<Tile> getMosaic(){return this->image;}
	inline std::string getStream(){return this->filename;}
	Import(std::string);
	//~Import();
};
#endif
