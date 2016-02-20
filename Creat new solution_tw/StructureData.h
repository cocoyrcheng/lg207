#ifndef MyStruct
#define MyStruct
#include <string>
#include <vector>
#include "Parameters.h"
using namespace std;

struct point                 //define a struct variable called point
{
	double x, y;
};

struct timewindow           //define a struct variable called timewindow
{
	double readytime, duedate, servicetime, chargetime, demand, pindex;
	std::string ID, type;
	point P;

};

class SOL
{
public:
	int NumRoutes;
	int Type[MaxNumRoutes];
	vector<int> Depots;
	int GetNumRoutes() {
		int nr = 0;
		for (int i = 0; i < (int)Depots.size();i++)
		{
			if (Depots[i] == 1) nr++;
		}
		return nr - 1;
	}
};
#endif