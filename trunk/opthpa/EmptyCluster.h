/*
 * EmptyCluster.h
 *
 *  Creates a maximal size cluster which is obstacle free. 
 *  Nodes and edges which appear along the perimeter of such clusters are
 *  added to the abstract graph. 
 *
 * 	NB: Clusters are extended in size using a floodfill approach.
 * 	NB2: Every possible transition point is created when an entrance
 * 	between two adjacent clusters is identified.
 *
 * @author: dharabor
 * @created: 10/02/2010
 */

#ifndef EMPTYCLUSTER_H
#define EMPTYCLUSTER_H

#ifdef OS_MAC
	#include "GLUT/glut.h"
	#include <OpenGL/gl.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
#endif

#include "HPACluster.h"

class HPAClusterAbstraction;

class EmptyCluster : public HPACluster
{
	#ifdef UNITTEST
		friend class EmptyClusterTest;
	#endif

	public:
		EmptyCluster(const int x, const int y) throw(std::invalid_argument);
		virtual ~EmptyCluster();

		virtual void 
			addNodesToCluster(HPAClusterAbstraction*) throw(std::invalid_argument);
		virtual void openGLDraw();


	protected:
		virtual void connectParent(node*, HPAClusterAbstraction*);
		virtual void buildHorizontalEntrances(HPAClusterAbstraction* hpamap);
		virtual void buildVerticalEntrances(HPAClusterAbstraction* hpamap);

	private:
		void initOpenGLCoordinates(HPAClusterAbstraction*);
		void extend(HPAClusterAbstraction*);
		void frameCluster(HPAClusterAbstraction*);
		void addMacroEdges(HPAClusterAbstraction *aMap);
		
		GLdouble glx, gly, glz;  // OpenGL origin coordinates
		GLdouble glHeight, glWidth;
};

#endif
