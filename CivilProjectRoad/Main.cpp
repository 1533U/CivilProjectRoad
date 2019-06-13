#include<iostream>

#include<fstream>
#include<cstdlib>
#include<cmath>
#include<vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <Windows.h>
#include <iomanip>

using namespace std;
using vec = vector<double>;
using matrix = vector<vec>;



string GetFileName(const string & prompt);
matrix Read3DCSV(string filelocation);


int main(int argc, char *argv[])
{
	

	string filelocation = GetFileName("Driver Polyline Data:  ");
	ifstream ifs(filelocation.c_str());
	if (!ifs.is_open()) {
		cerr << "cannot open " << filelocation << " for input" << endl;
	
	}
	


	matrix CSVMatrixData1 = ReadCSV(filelocation);



	//for loop for distance of c

		//calcute a to b for difrance of 350m
			//strait line between points on C defined as L
		//intersetion of line L with geometry T
			// T defined by trigailare data
			//Report IP deifned as the Intersction point with the road surface.
			//AB distance
	//AB and corisponing IP




}



string GetFileName(const string & prompt) {

	const int BUFSIZE = 1024;
	char buffer[BUFSIZE] = { 0 };
	OPENFILENAME ofns = { 0 };
	ofns.lStructSize = sizeof(ofns);
	ofns.lpstrFile = buffer;
	ofns.nMaxFile = BUFSIZE;
	ofns.lpstrTitle = prompt.c_str();
	GetOpenFileName(&ofns);
	return buffer;
}
	
matrix Read3DCSV(string filelocation) {


	ifstream Datafile(filelocation.c_str());
	matrix CSVMatrixData;






	return CSVMatrixData;
}