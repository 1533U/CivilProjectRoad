#include<iostream>
#include "Data.h"
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
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
double DistanceAtoB(matrix polyline, int currentA, int currentB);



int main(int argc, char *argv[])
{
	

	string filelocation = GetFileName("Driver Polyline Data:  ");
	ifstream ifs(filelocation.c_str());
	if (!ifs.is_open()) {
		cerr << "cannot open " << filelocation << " for input" << endl;
	
	}
	


	 matrix CSVMatrixData1 = Read3DCSV(filelocation);
	 double AB = 0;
	 double A2B = 0;
	 int j = 0;
	 double distnacestep = 0;
	for (size_t i = 0; i < CSVMatrixData1.size(); i++)
	{

		A2B = AB;
		j = i;
		do
		{
			if (j=i)
			{
				distnacestep = DistanceAtoB(CSVMatrixData1, j, j + 1);
				AB = AB + distnacestep;
			}

			A2B = A2B + DistanceAtoB(CSVMatrixData1, j, j+1);

			j++;


		} while ((A2B <=(350+350*i))&&(j< CSVMatrixData1.size()));
	}
	//for loop for distance of c

		//calcute a to b for difrance of 350m
			//strait line between points on C defined as L
		//intersetion of line L with geometry T
			// T defined by trigailare data
			//Report IP deifned as the Intersction point with the road surface.
			//AB distance
	//AB and corisponing IP



	return 0;
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

	for (std::string line; std::getline(Datafile, line); )
	{
		std::replace(line.begin(), line.end(), ',', ' ');
		std::istringstream in(line);
		CSVMatrixData.push_back(
			vec(std::istream_iterator<double>(in),
				std::istream_iterator<double>()));
	}

	for (matrix::const_iterator
		it(CSVMatrixData.begin()), end(CSVMatrixData.end()); it != end; ++it) {
		std::copy(it->begin(), it->end(),
		std::ostream_iterator<double>(std::cout, ", "));
		std::cout << "\n";
	}

	return CSVMatrixData;
}

double DistanceAtoB(matrix polyline,int currentA, int currentB)
{
	double distance = 0;
	if (currentB< polyline.size())
	{
		distance = sqrt(pow((polyline[currentA][0] - polyline[currentB][0]),2) + pow((polyline[currentA][1] - polyline[currentB][1]),2)+ pow((polyline[currentA][2] - polyline[currentB][2]),2));
	}

	return distance;
} 