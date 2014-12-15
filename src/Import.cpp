#include <iostream>
#include "Import.h"
#include "Tile.h"
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iomanip>

using namespace std;

void Import::read_file(){
	char buffer[BUF_SIZE];
	std::vector<std::vector <int> > rows_64;
	FILE* handle = fopen(filename.c_str(),"r");
	if(!handle){
		cerr<<"fopen"<<endl;
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < NUM_ROWS; i++){
		fgets(buffer,BUF_SIZE,handle);
		std::vector<int> temp = tokenize(buffer);
		rows_64.push_back(temp);
	}
	fclose(handle);
	Tile t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13;
	int idx = 0,index = 0;
	int s = 0;
	int f = 32;
	int row = 1;
	int where = 1;
	for (std::vector<std::vector<int> >::iterator i = rows_64.begin(); i != rows_64.end(); ++i){
		//Best way to extract a subvector from a vector?
		//Read (http://stackoverflow.com/questions/421573/best-way-to-extract-a-subvector-from-a-vector)
		vector<int>::iterator first = (*i).begin() + s;
		vector<int>::iterator last = (*i).begin() + f;
		vector<int> sub(first, last);
		(where < 33)?(row = 1):(row = 2);
		switch(row){
			case 1:{
				t0.add_row(idx,sub);
				s = f;
				f+=32;
				first = (*i).begin() + s;
				last = (*i).begin() + f;
				vector<int> sub1(first, last);
				t1.add_row(	idx,sub1);
				s = f;
				f+=32;
				first = (*i).begin() + s;
				last = (*i).begin() + f;
				vector<int> sub2(first, last);
				t2.add_row(idx,sub2);
				s = f;
				f+=32;
				first = (*i).begin() + s;
				last = (*i).begin() + f;
				vector<int> sub3(first, last);
				t3.add_row(idx,sub3);
				s = f;
				f+=32;
				first = (*i).begin() + s;
				last = (*i).begin() + f;
				vector<int> sub4(first, last);
				t4.add_row(idx,sub4);
				s = f;
				f+=32;
				first = (*i).begin() + s;
				last = (*i).begin() + f;
				vector<int> sub5(first, last);
				t5.add_row(idx,sub5);
				s = f;
				f+=32;
				first = (*i).begin() + s;
				last = (*i).begin() + f;
				vector<int> sub6(first, last);
				t6.add_row(idx,sub6);
				idx++;
				s  = 0;
				f  = 32;
				break;
			}
		case 2:{
			vector<int>::iterator first = (*i).begin() + s;
			vector<int>::iterator last = (*i).begin() + f;
			vector<int> sub(first, last);
			t7.add_row(index,sub);
			s = f;
			f+=32;
			first = (*i).begin() + s;
			last = (*i).begin() + f;
			vector<int> sub11(first, last);
			t8.add_row(	index,sub11);
			s = f;
			f+=32;
			first = (*i).begin() + s;
			last = (*i).begin() + f;
			vector<int> sub21(first, last);
			t9.add_row(index,sub21);
			s = f;
			f+=32;
			first = (*i).begin() + s;
			last = (*i).begin() + f;
			vector<int> sub31(first, last);
			t10.add_row(index,sub31);
			s = f;
			f+=32;
			first = (*i).begin() + s;
			last = (*i).begin() + f;
			vector<int> sub41(first, last);
			t11.add_row(index,sub41);
			s = f;
			f+=32;
			first = (*i).begin() + s;
			last = (*i).begin() + f;
			vector<int> sub51(first, last);
			t12.add_row(index,sub51);
			s = f;
			f+=32;
			first = (*i).begin() + s;
			last = (*i).begin() + f;
			vector<int> sub61(first, last);
			t13.add_row(index,sub61);
			index++;
			s = 0;
			f = 32;
			break;
		}
		default:
				break;
			}
			where++;
		}
		//loading the tiles to "image" for further processing
		image.push_back(t0);image.push_back(t1);
		image.push_back(t2);image.push_back(t3);
		image.push_back(t4);image.push_back(t5);
		image.push_back(t6);image.push_back(t7);
		image.push_back(t8);image.push_back(t9);
		image.push_back(t10);image.push_back(t11);
		image.push_back(t12);image.push_back(t13);
	}

Import::Import(std::string filename){
	this->filename = filename;
	read_file();
}

std::vector<int> Import::tokenize(char* line){
  char * pch;
  std::vector<int> v;
  pch = strtok (line,"	,");
  while (pch != NULL){
    v.push_back(atoi(pch));
    pch = strtok (NULL, "	,");
  }
  return v;
}

void Import::write_to_file(){
	string name = "features.txt";
	ofstream output(name.c_str(),ios::out);
	int idx = 0;
	int c_label;
	for(auto i : image){
		i.normalized_area();
		i.normalized_aspect_ratio();
		i.normalized_average_gray_value();
		i.normalized_inner_border_length();
		idx++;
		(idx <= 7)?(c_label = 1):(c_label = 2);
		output<<setprecision(7)<<i.getArea()<<", "<<i.getAsp()<<", "<<i.getGray()<<", "<<i.getIbl()<<", "<<c_label<<endl;
	}
	output.close();
	cout<<"\n\nwritten to <./output/features.txt> ...\n\n"<<endl;
}

void Import::write_to_filep(){
	string name0 = "class1.data";
	string name1 = "class2.data";
	ofstream output0(name0.c_str(),ios::out);
	ofstream output1(name1.c_str(),ios::out);
	int idx = 0;
	int c_label;
	for(auto i : image){
		i.normalized_area();
		i.normalized_aspect_ratio();
		i.normalized_average_gray_value();
		i.normalized_inner_border_length();
		idx++;
		(idx <= 7)?(c_label = 1):(c_label = 2);
		if(c_label == 1)
			output0<<setprecision(7)<<i.getArea()<<" "<<i.getAsp()<<" "<<i.getGray()<<" "<<i.getIbl()<<endl;
		else
			output1<<setprecision(7)<<i.getArea()<<" "<<i.getAsp()<<" "<<i.getGray()<<" "<<i.getIbl()<<endl;
	}
	output0.close();
	output1.close();
}

