#ifndef MyStruct
#define MyStruct
#include <string>
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
#endif