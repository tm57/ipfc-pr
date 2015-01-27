#include "Tile.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <utility>
#include <cassert>
#define NUM_COLS 32

using namespace std;

Tile::Tile(){
	make_tile();
}

void Tile::make_tile(){
	this->tile = new int *[NUM_COLS];
	if(!tile){
		cerr<<"new"<<endl;
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < NUM_COLS; i++){
		tile[i] = new int[NUM_COLS];
		if(!tile[i]){
			cerr<<"new"<<endl;
			exit(EXIT_FAILURE);
		}
	}
	for(int i = 0; i < NUM_COLS; i++){
		for(int j = 0; j < NUM_COLS; j++){
			this->tile[i][j] = 0;
		}
	}
}

void Tile::add_row(int row,std::vector<int> input){
	int idx = 0;
	for (std::vector<int>::iterator i = input.begin(); i != input.end(); ++i){
		if(row < NUM_COLS){
				tile[row][idx] = *i;
				idx++;
		}else{
			continue;
		}	
	}
}
/*
This function returns the pixels,corresponding to the central 'blob'
values returned are the coordinates to access the intensity values 
from the current tile(image)
*/
 std::set<std::pair<int,int> > Tile::central_blob(){
	std::set<std::pair<int,int> > blob;
	blob.insert(make_pair(15,15));
	for(int i = 15; i < NUM_COLS; i++){
		for(int j = 15; j < NUM_COLS; j++){
			std::vector<pair<int,int> > neighbors;
			neighbors = neighbours(make_pair(i,j));
			for (std::vector<pair<int,int> >::iterator it = neighbors.begin(); it != neighbors.end(); ++it){
				if(tile[(*it).first][(*it).second] >= 130)
					(blob.insert((*it)));
				else
					continue;
			}
		}
	}
	return blob;
}


vector<pair<int,int> > Tile::neighbours(pair<int,int> pix){
	//4 neigborhood
	std::vector<pair<int,int> > result;
	int resx = NUM_COLS,resy = NUM_COLS;
	int x = pix.first;
	int y = pix.second;
	if(x+1 >= 0 && y >= 0 && x+1 < resx - 1){
		result.push_back(make_pair(x+1,y));
	}
	if(x-1 >= 0 && y >= 0){
		result.push_back(make_pair(x-1,y));
	}
	if(y+1 >= 0 && x >= 0 && y+1 < resy - 1){
		result.push_back(make_pair(x,y+1));
	}
	if(y-1 >= 0 && x >= 0){
		result.push_back(make_pair(x,y-1));
	}
	return result;
}

void Tile::normalized_area(){
	int mysize;
	mysize = central_blob().size();
	double result = (double)mysize / 1024.0;
	area = result;
}

void Tile::normalized_aspect_ratio(){
	 std::set<std::pair<int,int> > blob = central_blob();
	 std::set<std::pair<int,int> >::const_iterator it = blob.begin();
	 int xmax = (*it).first,ymax = (*it).second;
	 int xmin = xmax,ymin = ymax;
	 for(auto f : blob){
	 	if(f.first > xmax){
	 		xmax = f.first;
	 	}

	 	if(f.second > ymax){
	 		ymax = f.second;
	 	}

	 	if(f.second < ymin){
		 		ymin = f.second;
		 }

		if(f.first < xmin){
		 	xmin = f.first;
		 }
	 }
	 double w = xmax - xmin + 1;
	 double h = ymax - ymin + 1;
	 aspect_ratio = (h > w)?( w / h):( h / w);
}

void Tile::normalized_average_gray_value(){
	std::set<std::pair<int,int> > blob = central_blob();
	int sum = 0;
	for(auto f : blob){
		sum+=tile[f.first][f.second];
	}
	double tmp = sum / blob.size();
	
	gray_value = (tmp - 130.0) / 94.0;
}

void Tile::normalized_inner_border_length(){
	Tile tobeEroded;
	int ig_pixels;
	int blob_pixles;
	std::set<std::pair<int,int> > blob = central_blob();
	blob_pixles = blob.size();
	for(auto f : blob){
		tobeEroded.getTile()[f.first][f.second] = tile[f.first][f.second];
	}
	for(int i  = 0; i < NUM_COLS; i++){
		for(int j = 0; j < NUM_COLS; j++){
			if(tobeEroded.getTile()[i][j] != 0){
				std::vector<pair<int,int> > neighbors;
				neighbors = neighbours(make_pair(i,j));
				for(auto f : neighbors){
					if(tobeEroded.getTile()[f.first][f.second] != 0){
						continue;
					}else{
						blob.erase(make_pair(i,j));
						break;
					}
				}
			}
		}
	}
	ig_pixels = blob.size();
	assert(blob_pixles != 0);
	border_length = (double)ig_pixels / (double)blob_pixles;
}
