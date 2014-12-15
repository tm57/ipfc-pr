#ifndef __H_TILE__H__
#define __H_TILE__H__
#include <vector>
#include <set>
#include <utility>
class Tile{
private:
	int **tile;
	double area;
	double aspect_ratio;
	double gray_value;
	double border_length;
public:
	Tile();
	void normalized_area();
	void normalized_aspect_ratio();
	void normalized_average_gray_value();
	void normalized_inner_border_length();
	void make_tile();
	void add_row(int row,std::vector<int> input);
	inline double getArea(){return area;}
	inline double getAsp(){return aspect_ratio;}
	inline double getIbl(){return border_length;}
	inline double getGray(){return gray_value;}
	inline int **getTile(){return tile;}
	std::set<std::pair<int,int> > central_blob();
	std::vector<std::pair<int,int> > neighbours(std::pair<int,int> pix);
	//~Tile();
};
#endif