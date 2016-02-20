#include <list>
#include <vector>
#include <iostream>
#include <map>
#include "StructureData.h"
#include "Parameters.h"


using namespace std;


int FindAppropriateChargeStation (char currentStation,
	                             char nextStation,
	                             vector<int> ChargeStationInfo,
	                             float currentEnergy,
						double Distance[VETX_NUM][VETX_NUM])   //just solve one pair of customers , not move
{
	multimap<vector<double>, int> SelectChargeStations;
	for (size_t i = 0; i < ChargeStationInfo.size(); ++i)    //actually ChargeStationInfo.size=recharging_num
	{

		if (currentStation == i + CUS_NUM+2)
		{
			continue;
		}
		
		if (ChargeStationInfo[i] == CHARGE_UPPER_BOUND)
		{
			continue;
		}
		if (Distance[currentStation-1][ CUS_NUM +2 + i-1] > currentEnergy)
		{
			continue;
		}


		vector<double> first(2, 0.0);
		first[0] = Distance[currentStation-1][CUS_NUM + 2 + i-1] + Distance[CUS_NUM+ 2 + i-1][nextStation-1];
		first[1] = ChargeStationInfo[i];    //the times of the recharging stations are used

		SelectChargeStations.insert(pair<vector<double>, int>(first, i));
	}

	if (SelectChargeStations.empty())
	{
		return -1;
	}

	return SelectChargeStations.begin()->second;
}


void TryChargeStationInsertion(vector<char>currentSolution,
	    vector<char>subResults,
	    float currentEnergy, double Distance[VETX_NUM][VETX_NUM])
{
		
		typedef vector<char>::iterator iter_type;

		currentEnergy = FULL_ENERGY;
	
		vector<char>::iterator itr1 = currentSolution.begin();
		vector<char>::iterator itr2 = currentSolution.begin();
	    ++itr2;

	float TotalDis = 0.0;

	while(itr2!=currentSolution.end())
	{
		float dis = Distance[*itr1-1][*itr2-1];  //define a new function called GetDistance
		if (*itr1 == 1) 
		{
			currentEnergy = FULL_ENERGY; //from depot, always full energy
			TotalDis = 0.0;
		} 
        else
		{
			currentEnergy -= dis;
			TotalDis += dis;
		}
		
		vector<int> ChargeStationInfo;

		if (currentEnergy < 0)
		{
			int ChargeStationIndex = FindAppropriateChargeStation(*itr1, *itr2, ChargeStationInfo, currentEnergy, Distance);
			while (ChargeStationIndex = -1)    //-1 is no appropriate station is selected
			{
				--itr1; --itr2;
				int ChargeStationIndex = FindAppropriateChargeStation(*itr1, *itr2, ChargeStationInfo, currentEnergy, Distance);
				/*for (int i = 0; i < NUM_CHARGE; ++i)
				{
					if (*itr1 = i + 21)
						break;
				}*/    //how to step out of the while cycle if *itr1 is one of the recharging station; big M to make the solution valid
			}

			currentSolution.insert(itr2, CUS_NUM+2 + ChargeStationIndex);    //ORIGINAL itr2 is the position the charge station will be inserted
			++itr1;
			currentEnergy = FULL_ENERGY;
			TotalDis = 0.0;
		}
		else
		{
			++itr1; ++itr2;
		}
		}
		
	}

	





         


	



		

	

			