/*
 *  ExperimentManager.cpp
 *  hog
 *
 *  Created by Daniel Harabor on 18/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "ExperimentManager.h"
#include "TestConstants.h"

using namespace ExpMgrUtil;

ExpMgrUtil::ExperimentCollection* ExperimentManager::tests = NULL;
int ExperimentManager::refcount=0;

ExpMgrUtil::TestExperiment::TestExperiment(ExperimentKey key, int sx, int sy, int gx, int gy, int terrain, int size, double dist, string mapname, bool pathable)
{
	this->key = key;
	this->startx = sx;
	this->starty = sy; 
	this->goalx = gx;
	this->goaly = gy; 
	this->terrain = terrain;
	this->size = size;
	this->distance = dist;
	this->mapname = mapname;
	this->pathable = pathable;
}


ExperimentManager::ExperimentManager()
{
	if(tests == NULL) 
	{
		tests = new ExperimentCollection();
		generateExperiments();
	}

	refcount++;
}

ExperimentManager::~ExperimentManager()
{
	refcount--;
	if(refcount == 0) 
	{
		for (__gnu_cxx::hash_map<int, TestExperiment*>::iterator i = tests->begin(); i != tests->end(); ++i)
			delete i->second;	
		
		tests->clear();
		delete tests;
		tests = NULL; // reset the initialization
	}
}

TestExperiment* ExperimentManager::getExperiment(ExperimentKey expkey)
{
	last = expkey;
	return (*tests)[expkey]; // TODO: check behaviour when expkey is nonexistent in the hashtable
}

void ExperimentManager::generateExperiments()
{	
	if(tests->size() == 0)
	{
		tests->insert(pair<int, TestExperiment*>((int)kPathableToyProblemLST,  new TestExperiment(kPathableToyProblemLST, 4,2,1,7,4,2,6.0+ROOT_TWO, maplocation, true)));
		tests->insert(pair<int, TestExperiment*>((int)kNotPathableGoalIsSoftObstacleLST, new TestExperiment(kNotPathableGoalIsSoftObstacleLST, 1,2,22,1,4,2,0, maplocation, false)));
		tests->insert(pair<int, TestExperiment*>((int)kNotPathableStartIsHardObstacleLST, new TestExperiment(kNotPathableStartIsHardObstacleLST, 0,0,22,6,4,2,0, maplocation, false)));

		tests->insert(pair<int, TestExperiment*>((int)kPathableMoveNorthLST, new TestExperiment(kPathableMoveNorthLST, 4,8,4,7,4,2,1, maplocation, true)));
		tests->insert(pair<int, TestExperiment*>((int)kPathableMoveSouthLST, new TestExperiment(kPathableMoveSouthLST, 4,8,4,9,4,2,1, maplocation, true)));
		tests->insert(pair<int, TestExperiment*>((int)kPathableMoveEastLST, new TestExperiment(kPathableMoveEastLST, 4,8,5,8,4,2,1, maplocation, true)));
		tests->insert(pair<int, TestExperiment*>((int)kPathableMoveWestLST, new TestExperiment(kPathableMoveWestLST, 4,8,3,8,4,2,1, maplocation, true)));
		tests->insert(pair<int, TestExperiment*>((int)kPathableMoveNorthWestLST, new TestExperiment(kPathableMoveNorthWestLST, 4,8,3,7,4,2,1, maplocation, true)));
		tests->insert(pair<int, TestExperiment*>((int)kPathableMoveNorthEastLST, new TestExperiment(kPathableMoveNorthEastLST, 4,8,5,7,4,2,1, maplocation, true)));
		tests->insert(pair<int, TestExperiment*>((int)kPathableMoveSouthEastLST, new TestExperiment(kPathableMoveSouthEastLST, 4,8,5,9,4,2,1, maplocation, true)));
		tests->insert(pair<int, TestExperiment*>((int)kPathableMoveSouthWestLST, new TestExperiment(kPathableMoveSouthWestLST, 4,8,3,9,4,2,1, maplocation, true)));
	}
}

/*TestExperiment getExperiment(ExperimentKey expkey)
{
/*	switch(expkey)
	{	
	
		
/*		case kNotPathableHardObstacleLST:
		{
			TestExperiment exp = {1,2,22,1,4,2,0, maplocation.c_str(), false};
			return exp;			
		}
		case kGoalNotTraversableLST:
		{
			TestExperiment exp = {0,0,10,5,4,2,0, maplocation.c_str(), false};
			return exp;
		} */
		
		/*
	}	
}*/
/*
TestExperiment getExperimentPathable(ExperimentKey expkey)
{
//	extern float ptrLastExperimentFunction;
//	ptrLastExperimentFunction = &getExperimentPathable;

	switch(expkey)
	{
		case kPathableToyProblemLST:
		{
			TestExperiment exp = {1,2,5,1,4,2,3.0+ROOT_TWO, maplocation.c_str(), true};
			return exp;
		}
		default: 
		{
			TestExperiment exp = {-1,-1,-1,-1,-1,-1,-1,"",false};
	//		ptrLastExperimentFunction = 0;
			return exp;
		}

	}
}


TestExperiment getExperimentOutOfBounds(ExperimentKey expkey)
{
//	extern float ptrLastExperimentFunction = &getExperimentOutOfBounds;

	switch(expkey)
	{
		case kNotPathableStartPositionOutOfBoundsLST:
		{
			TestExperiment exp = {0,0,22,6,4,2,0, maplocation.c_str(), false};	
			return exp;
		}
		case kNotPathableGoalPositionOutOfBoundsLST:
		{
			TestExperiment exp = {0,0,10,5,4,2,0, maplocation.c_str(), false};
			return exp;
		}
		default: 
		{
			TestExperiment exp = {-1,-1,-1,-1,-1,-1,-1,"",false};
			//prtLastExperimentFunction = 0;
			return exp;
		}
	}
}*/