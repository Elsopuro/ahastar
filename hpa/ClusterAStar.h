/*
 *  ClusterAStar.h
 *  hog
 *
	A simple variant on the standard A* implementation which supports limiting search to one or two clusters.
	Specifically, if useCorridor is true, the parentClusterId of the start node is used to limit which nodes are added to the open list.
	If the corridor is unspecified, a regular A* search is run on the map. 	NB: assumes the graph is composed of nodes of type ClusterNode.
		
	This class also adds additional metrics for measuring search performance:
	 - Total time to search (in milliseconds).
	 - Peak memory (records max size of open list during the search).
	
 *  Created by Daniel Harabor on 14/11/08.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CLUSTERASTAR_H
#define CLUSTERASTAR_H

#include <string>
#include <map>
#include "aStar3.h"

class statCollection;
class path;
class graphAbstraction;
class node;
class edge;
class statCollection;

class AbstractClusterAStar : public aStarOld
{
	public:	
		AbstractClusterAStar() { corridorNodes = NULL; verbose = false;}
		virtual ~AbstractClusterAStar() {}
		virtual const char* getName() = 0;
		virtual path *getPath(graphAbstraction *aMap, node *from, node *to, reservationProvider *rp = 0);
		
		long getPeakMemory() { return peakmemory; }
		double getSearchTime() { return searchtime; }
		void setCorridorNodes(std::map<int, node*>* _nodes) 
		{ 
			corridorNodes = _nodes; 
			assert(corridorNodes == _nodes); 
		}
		
		bool verbose;
	protected:
		bool isInCorridor(node* n);
		void expand(node* current, node* to, heap* openList, std::map<int, node*>& closedList, graph* g);

		virtual bool evaluate(node* current, node* target, edge* e) = 0; 
		virtual bool checkParameters(graphAbstraction* aMap, node* from, node* to) = 0;

		long peakmemory;
		double searchtime;
		std::map<int, node*> *corridorNodes;

	private:
		void printNode(std::string msg, node* n);
};

class ClusterAStar : public AbstractClusterAStar
{
	public:
		#ifdef UNITTEST
			friend class ClusterAStarTest; 
		#endif
		
		ClusterAStar() : AbstractClusterAStar() { }
		virtual ~ClusterAStar() {}
		virtual const char* getName() { return "ClusterAStar"; }
		virtual void logFinalStats(statCollection *stats);

	protected:
		virtual bool evaluate(node* current, node* target, edge* e);
		bool checkParameters(graphAbstraction* aMap, node* from, node* to);
		


};

#endif

