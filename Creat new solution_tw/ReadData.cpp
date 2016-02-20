
///test github version
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle, find
#include <vector>       // std::vector
#include <map>
#include <tuple>
#include <ctime>        // std::time
#include <fstream>
#include <cmath>
#include <string>
#include <cstdlib>
#include "StructureData.h"
#include <fstream>
#include "Parameters.h"
using namespace std;
void SplitInPutStrings(const std::vector<string> &InputString,
	point &TempPoint)
{
	size_t pos = InputString.size();
	TempPoint.x = stof(InputString.at(3));
	TempPoint.y = stof(InputString.at(4));


}

void ReadData(vector<point> &InPut) {

	ifstream InputTxt;
	
	string line;
	InputTxt.open("TravelTime.txt");
	std::vector<std::string> SubStrs, ResidualStr;
	std::string::size_type Sub1Begin, Sub1End;
	string tmp;
	point TempPoint;
	int InputCount=0;
	while (!InputTxt.eof())
	{
		Sub1Begin = 0;
		SubStrs.clear();
		getline(InputTxt, tmp);
		Sub1End = tmp.find("\t");
		do
		{
			SubStrs.push_back(tmp.substr(Sub1Begin, Sub1End - Sub1Begin));
			Sub1Begin = Sub1End + 1;
			Sub1End = tmp.find("\t", Sub1End + 1);
		} while (Sub1End != std::string::npos);
		SubStrs.push_back(tmp.substr(Sub1Begin, Sub1End - Sub1Begin));
		SplitInPutStrings(SubStrs, TempPoint);
		InPut[InputCount].x = TempPoint.x;
		InPut[InputCount].y = TempPoint.y;
		InputCount++;
		if (InputCount>=InPut.size())
		{
			break;
		}
	}




	InputTxt.close();



}
