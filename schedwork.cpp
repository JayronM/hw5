#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helper(const AvailabilityMatrix& avail,const size_t dailyNeed, const size_t maxShifts,DailySchedule& sched, vector<size_t>& shiftsCount, size_t day, size_t slot);



// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    size_t n = avail.size();
		size_t k= avail[0].size();

		sched.assign(n,vector<Worker_T>(dailyNeed, INVALID_ID)); // schedule for n days with daill need slots
		//track how many shifts per worker
		vector<size_t> shiftsCount(k,0);
		return helper(avail, dailyNeed, maxShifts, sched, shiftsCount, 0,0);//backtracking at day 0
}


bool helper(const AvailabilityMatrix& avail,const size_t dailyNeed, const size_t maxShifts,DailySchedule& sched, vector<size_t>& shiftsCount, size_t day, size_t slot){
	size_t n = avail.size();
	size_t k= avail[0].size();
	if(day == n) return true; //all days scheduled
	if(slot == dailyNeed){
		return helper(avail, dailyNeed, maxShifts, sched, shiftsCount, day+1, 0);// move onto next day if today is filled
	}
	for(Worker_T w =0; w<k;++w){
		//availibilty 
		if(!avail[day][w]|| shiftsCount[w] >= maxShifts){
			continue;
		}
		bool alreadyScheduled = false; // making sure that worker is not already in the schedule for the day
		for(size_t i = 0; i< slot;++i){
			if(sched[day][i]==w){
				alreadyScheduled = true;
				break;
			}
		}
		if(alreadyScheduled) continue;
		//assign and recusrve
		sched[day][slot] =w;
		shiftsCount[w]++;
		if(helper(avail, dailyNeed, maxShifts, sched, shiftsCount, day, slot+1)){
			return true;
		}
		shiftsCount[w]--; //backtrack
	}
	return false;//no slot found basically
}
