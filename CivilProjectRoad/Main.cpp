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
#include<math.h>

using namespace std;
using vec = vector<float>;
using matrix = vector<vec>;
#define vector(a,b,c) \
	(a)[0] = (b)[0] - (c)[0];	\
	(a)[1] = (b)[1] - (c)[1];	\
	(a)[2] = (b)[2] - (c)[2];

#define crossProduct(a,b,c) \
(a)[0] = (b)[1] * (c)[2] - (c)[1] * (b)[2]; \
(a)[1] = (b)[2] * (c)[0] - (c)[2] * (b)[0]; \
(a)[2] = (b)[0] * (c)[1] - (c)[0] * (b)[1];

#define innerProduct(v,q) \
((v)[0] * (q)[0] + \
(v)[1] * (q)[1] + \
(v)[2] * (q)[2])




string GetFileName(const string & prompt);
matrix Read3DCSV(string filelocation);
double DistanceAtoB(matrix polyline, int currentA, int currentB);
bool rayIntersectsTriangle(float *p, float *d, float *v0, float *v1, float *v2);



int main(int argc, char *argv[])
{
	

	string filelocation = GetFileName("Driver Polyline Data:  ");
	ifstream ifs(filelocation.c_str());
	if (!ifs.is_open()) {
		cerr << "cannot open " << filelocation << " for input" << endl;
	
	}
	 matrix CSVMatrixData1 = Read3DCSV(filelocation);


	 string filelocation1 = GetFileName("Mesh:  ");
	 ifstream ifs1(filelocation1.c_str());
	 if (!ifs1.is_open()) {
		 cerr << "cannot open " << filelocation1 << " for input" << endl;

	 }
	 matrix CSVMatrixData2 = Read3DCSV(filelocation1);


	 float AB = 0;
	 float A2B = 0;
	 int j = 0;
	 float distnacestep = 0;
	 bool IPcheck;
	 int k = 0 ;

	for (size_t i = 0; i < CSVMatrixData1.size()-1; i++)
	{
		cout << i<<'\n';
		A2B = AB;
		j = i;
		do
		{
			//cout << j << '\n';
			if (j==i)
			{
				distnacestep = DistanceAtoB(CSVMatrixData1, j, j + 1);
				AB = AB + distnacestep;
				j++;
			}
			else
			{
				A2B = A2B + DistanceAtoB(CSVMatrixData1, j, j+1);
				j++;
			}

			float p[3] = { CSVMatrixData1[i][0],CSVMatrixData1[i][1],CSVMatrixData1[i][2] };
			float d[3] = { CSVMatrixData1[i][0]- CSVMatrixData1[j][0],CSVMatrixData1[i][1] - CSVMatrixData1[j][1],CSVMatrixData1[i][2] - CSVMatrixData1[j][2]};

			for (size_t g = 0; g < CSVMatrixData2.size(); g++)
			{
				if (CSVMatrixData2[g][0]>= CSVMatrixData1[i][0]|| CSVMatrixData2[g][1] >= CSVMatrixData1[i][1])
				{

					k = g;
					break;
				}
			}

			do
			{

				float v0[3] = { CSVMatrixData2[k][0],CSVMatrixData2[k][1],CSVMatrixData2[k][2] };
				float v1[3] = { CSVMatrixData2[k][3],CSVMatrixData2[k][4],CSVMatrixData2[k][5] };
				float v2[3] = { CSVMatrixData2[k][6],CSVMatrixData2[k][7],CSVMatrixData2[k][8] };

				IPcheck = rayIntersectsTriangle(p, d, v0, v1, v2);

				if (IPcheck)
				{
					//cout << A2B-AB<<'\n';
				}


				k++;
				//cout << k << '\n';
			} while (k< CSVMatrixData2.size());


		} while ((A2B <=(350+AB))&&(j<CSVMatrixData1.size()-1));
	}




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

bool rayIntersectsTriangle(float *p, float *d,float *v0, float *v1, float *v2)
{

	float e1[3], e2[3], h[3], s[3], q[3];
	float a, f, u, v;
	vector(e1, v1, v0);
	vector(e2, v2, v0);

	crossProduct(h, d, e2);
	a = innerProduct(e1, h);

	if (a > -0.00001 && a < 0.00001)
		return(false);

	f = 1 / a;
	vector(s, p, v0);
	u = f * (innerProduct(s, h));

	if (u < 0.0 || u > 1.0)
		return(false);

	crossProduct(q, s, e1);
	v = f * innerProduct(d, q);

	if (v < 0.0 || u + v > 1.0)
		return(false);

	
	float t = f * innerProduct(e2, q);

	if (t > 0.00001) { /
		float finalPoint[3];
		finalPoint[0] = p[0] + d[0] * t;
		finalPoint[1] = p[1] + d[1] * t;
		finalPoint[2] = p[2] + d[2] * t;
		cout <<finalPoint[0]<<finalPoint[1]<<finalPoint[2]<<'\n';
		std::ostringstream oss;
		oss << '1' << ".xls";
		std::string var = oss.str();
		std::ofstream myfile;
		myfile.open(var, std::ofstream::out | std::ofstream::app);
		myfile << finalPoint[0] << "," << finalPoint[1] << "," << finalPoint[2] << "\n";
		myfile.close();
		return(true);
	}
	else 
	
		return (false);
}