
///test github version
#include <iostream>     // std::cout

#include <algorithm>    // std::random_shuffle, find
#include <vector>       // std::vector
#include <map>
#include <tuple>
#include <ctime>        // std::time
#include <windows.h>
#include <fstream>
#include <cmath>
#include <string>
//#include <list>
#include <cstdlib>
#include <assert.h>     /* assert */
#include "StructureData.h"
#include "Parameters.h"
using namespace std;


void TryChargeStationInsertion(vector<char>currentSolution,
	vector<char>subResults,
	float currentEnergy);


//add function

void ReadData(vector<point> &InPut);
int FindAppropriateChargeStation(int currentStation,
	int nextStation,
	vector<int> ChargeStationInfo,
	double Distance[VETX_NUM][VETX_NUM],
	double currentEnergy)   //just solve one pair of customers , not move
{
	multimap<vector<double>, int> SelectChargeStations;
	for (size_t i = 0; i < ChargeStationInfo.size(); ++i)    //actually ChargeStationInfo.size=recharging_num
	{

		if (currentStation == i + CUS_NUM + 2)
		{
			continue;
		}

		//if (ChargeStationInfo[i] == CHARGE_UPPER_BOUND)
		//{
		//continue;
		//}
		if (Distance[currentStation - 1][CUS_NUM + 2 + i - 1] > currentEnergy)
		{
			continue;
		}


		vector<double> first(2, 0.0);
		first[0] = Distance[currentStation - 1][CUS_NUM + 2 + i - 1] + Distance[CUS_NUM + 2 + i - 1][nextStation - 1];
		first[1] = ChargeStationInfo[i];    //the times of the recharging stations are used

		SelectChargeStations.insert(pair<vector<double>, int>(first, i));
	}

	if (SelectChargeStations.empty())
	{
		return -1;
	}

	return SelectChargeStations.begin()->second;
}



void TryChargeStationInsertion(vector<int>currentSolution,
	vector<int> ChargeStationInfo,
	double Distance[VETX_NUM][VETX_NUM])

{
	//list<int> currentSolution,
		//typedef list<int>::iterator iter_type;

	double currentEnergy = FULL_ENERGY;

	vector<int>::iterator itr1 = currentSolution.begin();
	vector<int>::iterator itr2 = currentSolution.begin();
	++itr2;

	double TotalDis = 0.0;
	//int itercount = 0;
	while (itr2 != currentSolution.end())
	{
		//cout << itercount << endl;
		//if (itercount == 4)
		//{
		//	cout << endl;
		//}
		//itercount++;
		double dis = Distance[*itr1 - 1][*itr2 - 1];  //define a new function called GetDistance
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

		//int count2 = 0;
		if (currentEnergy < 0)
		{
			int ChargeStationIndex = FindAppropriateChargeStation(*itr1, *itr2, ChargeStationInfo, Distance, currentEnergy);
			while (ChargeStationIndex == -1)    //-1 is no appropriate station is selected
			{
				
				//cout << count2 << endl;
				//count2++;
				cout << *itr1 << endl;
				--itr1; --itr2;
				int ChargeStationIndex = FindAppropriateChargeStation(*itr1, *itr2, ChargeStationInfo, Distance, currentEnergy);
				/*for (int i = 0; i < NUM_CHARGE; ++i)
				{
				if (*itr1 = i + 21)
				break;
				}*/    //how to step out of the while cycle if *itr1 is one of the recharging station; big M to make the solution valid
			}

			currentSolution.insert(itr2, CUS_NUM + 2 + ChargeStationIndex);    //ORIGINAL itr2 is the position the charge station will be inserted
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

int main()
{
	double readytime[] = { 0.0,355.0,176.0,744.0,737.0,263.0,0.0,0.0,0.0, };
	double duedate[] = { 1236.0,407.0,228.0,798.0,809.0,325.0,1236.0,1236.0,1236.0 };
	double servicetime[] = { 0.0,90.0,90.0,90.0,90.0,90.0,0.0,0.0,0.0 };
	int demand[] = { 0, 10, 20, 20, 30, 10, 0, 0, 0 };
	double traveltime[VETX_NUM][VETX_NUM];
	double Distance[VETX_NUM][VETX_NUM];
	 
	// import the txt network file
	/*ifstream info("c101C5.txt");    // info.open("c101C5", ios::in)
	struct timewindow tw[VETX_NUM];
	if (info.is_open())

	{
		int lines;

		for (int i = 0; i < lines; ++i)
		{
			info >> tw[i].ID;
			info >> tw[i].type;
			info >> tw[i].P.x >> tw[i].P.y;
			info >> tw[i].pindex;
			info >> tw[i].demand;
			info >> tw[i].readytime >> tw[i].duedate >> tw[i].servicetime;
		}

	}
	else
		cout << "Error opening" << "c101C5" << "for input" << endl;*/
	struct timewindow tw[VETX_NUM];

	vector<point> Points;
	point tp;
	for (size_t i = 0; i < VETX_NUM; i++)
	{
		Points.push_back(tp);
	}

	ReadData(Points);

	for (int i = 0; i < VETX_NUM; i++)
	{
		tw[i].readytime = readytime[i];
		tw[i].duedate = duedate[i];
		tw[i].servicetime = servicetime[i];
		tw[i].demand = demand[i];
		tw[i].P.x = Points[i].x;
		tw[i].P.y = Points[i].y;
	}

	for (int i = 0; i < VETX_NUM; ++i)
	{
		for (int j = 0; j < VETX_NUM; ++j)
		{
			Distance[i][j] = sqrt(pow((tw[i].P.x - tw[j].P.x), 2) + pow((tw[i].P.y - tw[j].P.y), 2));
			traveltime[i][j] = Distance[i][j];
		}
	}
	
	//create initial raw solution
	//srand(unsigned(time(0)));
	vector<int> tmp_solution;
	SOL tpSol;
	

	for (int i = 2; i < CUS_NUM + 1; i++)
	{
		tmp_solution.push_back(i);
		tpSol.Depots.push_back(i);
	}
		
	for (int i = 1; i < VEHICLE_NUM; i++)
	{
		tmp_solution.push_back(1);
		tpSol.Depots.push_back(1);
	}
	
	
	random_shuffle(tmp_solution.begin(), tmp_solution.end());
	random_shuffle(tpSol.Depots.begin(), tpSol.Depots.end());
	
	tmp_solution.insert(tmp_solution.begin(), 1);
	tmp_solution.push_back(1);

	tpSol.Depots.insert(tpSol.Depots.begin(), 1);
	tpSol.Depots.push_back(1);


	tpSol.NumRoutes = tpSol.GetNumRoutes();

	for (int i = 0; i < tpSol.NumRoutes; i++)
	{
		// change type of vehicle 
		tpSol.Type[i] = 1;
	}

	vector<int>::iterator att = tmp_solution.begin();
	for (att = tmp_solution.begin(); att !=tmp_solution.end(); ++att)
		cout << *att<< ' ';
	cout << '\n';
	
	map<int, int>demand_pair;
	int point[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};

	for (int i = 0; i < VETX_NUM; ++i)
		//demand_pair.insert(pair<int, int>(point[i], tw[i].demand));
		demand_pair.insert(pair<int, int>(point[i], demand[i]));
	
	map<int, int>::iterator it = demand_pair.begin();
	for (it = demand_pair.begin(); it != demand_pair.end(); ++it)
		cout << it->first << " => " << it->second << '\n';

	//calculate the cumulative demands
	vector<int>cal_demand;
	vector<int>::iterator cal_itr = cal_demand.begin();
	vector<int>::iterator at = tmp_solution.begin();
	for (at = tmp_solution.begin(); at != tmp_solution.end(); ++at)

		cal_demand.push_back(demand_pair.find(*(at))->second);    //just withdraw the demand of the customer order in the current solution


	for (cal_itr = cal_demand.begin(); cal_itr != cal_demand.end(); ++cal_itr)
	{
		if (*cal_itr == 0)

			continue;

		else
			*(cal_itr) = *(cal_itr - 1) + *(cal_itr);     //calculate the demand customer by customer
	}


	for (vector<int>::iterator output = cal_demand.begin(); output < cal_demand.end(); output++)
	cout << *output << ' ';
	cout << '\n';

	//check whether exceed the capacity
	sort(cal_demand.begin(), cal_demand.end());
	vector<int>::iterator up;
	up = upper_bound(cal_demand.begin(), cal_demand.end(), CAPACITY);  //locate the first place with the calculated demands bigger than capacity

	cout << (up - cal_demand.begin()) << '\n';

	while ((up - cal_demand.begin()) != (CUS_NUM + VEHICLE_NUM))
	{
		tmp_solution.clear();
		for (int i = 2; i < CUS_NUM + 1; i++)
			tmp_solution.push_back(i);
		for (int i = 1; i < VEHICLE_NUM; i++)
			tmp_solution.push_back(1);
		random_shuffle(tmp_solution.begin(), tmp_solution.end());
		tmp_solution.insert(tmp_solution.begin(), 1);  //begin at depot
		tmp_solution.push_back(1);                     //end at depot

		cal_demand.clear();
		for (at = tmp_solution.begin(); at != tmp_solution.end(); ++at)

			cal_demand.push_back(demand_pair.find(*(at))->second);


		for (cal_itr = cal_demand.begin(); cal_itr != cal_demand.end(); ++cal_itr)
		{
			if (*cal_itr == 0)

				continue;

			else
				*(cal_itr) = *(cal_itr - 1) + *(cal_itr);
		}
		sort(cal_demand.begin(), cal_demand.end());
		up = upper_bound(cal_demand.begin(), cal_demand.end(), CAPACITY);
	}


	cout << (up - cal_demand.begin()) << '\n';

	for (vector<int>::iterator result = cal_demand.begin(); result < cal_demand.end(); ++result)
		cout << *result << ' ';
	cout << '\n';

	for (vector<int>::iterator lat = tmp_solution.begin(); lat != tmp_solution.end(); ++lat)
		cout << *lat << ' ';

	//insert recharging stations
	vector<int>ChargeStationInfo(CHARGE_NUM, 0);
	TryChargeStationInsertion(tmp_solution,ChargeStationInfo,Distance);
	


	//check the time window of the customers

	//calculate the recharging time
	vector<double>chargetime(VETX_NUM, 0.0);
	vector<int>::iterator pl;
	int chargestation[] = { 7, 8, 9 };
	vector<int> chargest(chargestation, chargestation + CHARGE_NUM);   //this is the vector of recharging station vertices

	vector<int>::iterator itr1 = tmp_solution.begin();
	vector<int>::iterator itr2 = tmp_solution.begin();
	vector<double>::iterator mov_itr = chargetime.begin();

	for (; itr1 != tmp_solution.end(); ++itr1, ++itr2, ++mov_itr)
	{

		pl = find(chargest.begin(), chargest.end(), *itr1);    //check whether itr1 is a recharging station
		if (pl != chargest.end())   //this point is a recharging station
		{
			++itr2;
			pl = find(chargest.begin(), chargest.end(), *itr2);
			while ((pl == chargest.end())||(*itr2 != 1))   //*itr2 is not a depot or not a recharging station
			{
				*mov_itr = *mov_itr + Distance[*(--itr2) - 1][(*itr2) - 1];  //!!!!Distance is the distance matrix between all the points
				++itr2;
			}
			*mov_itr = *mov_itr + Distance[*(--itr2) - 1][(*itr2) - 1];   //should * the reverse rate

			/*itr1 = itr2;
			mov_itr = itr2;*/

			while (itr1 != itr2)
			{
				++itr1; ++mov_itr;
			}
		}
	}

	vector<double>begintime(VETX_NUM,0.0); //all initial is 0
	double lastBeginTime = 0.0;
	vector<int>::iterator mov = ++tmp_solution.begin() ;   //from the SECOND element


	for (; mov != tmp_solution.end(); ++mov)
	{
		begintime[*mov] = tw[*mov].readytime;
		cout << tw[*mov].readytime << endl;
		//float lastBeginTime = tw[*mov_itr-1].readytime;
			
		lastBeginTime = max(tw[*mov].readytime,                   //calculate the actual service time of mov_itr
			lastBeginTime
			+ tw[*(--mov)].servicetime        //last customer's service time
			+ traveltime[*(--mov)-1][*mov-1]        //travel time between last customer and the present customer
			+ tw[*(--mov)].chargetime);

		begintime[*mov] = lastBeginTime;
	}
}




		