#ifndef LOS_H
#define LOS_H

#include "../Structures/LinkedList.h"

class LOS {
public:
	static LinkedList<int> Path(
		int** graph,
		int currNodes,
		int startNode,
		int destination,
		int columns
	);
};


#endif