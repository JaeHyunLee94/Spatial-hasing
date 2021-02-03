#pragma once


#include <unordered_map>
#include <vector>


using namespace std;


struct Mesh{
	//tet info
};

struct MappedVertice {
	int index;
	int obj_index;
};

class CollisionInfo {




};



class CollisionDetector
{

	/*
	* collision detection class using spatial hashing
	*/

public:

	int timeStep;
	

	//hash parameter
	int p1, p2, p3;

	int n;//table size
	float gridSize;


	//TODO: table initialize 
	CollisionDetector(); 
	~CollisionDetector();


	void addObject(Mesh* mesh);
	void setHashParam(int p1, int p2, int p3, int tableSize, float gridSize);
	
	CollisionInfo detectCollision();
	void mapVertices();




private:

	vector<Mesh*> m_obj_list;
	//TODO: hash table 을 list로도 구현가능?
	vector<vector<MappedVertice>> Table; 




	void mapVertices(); //timestamp update
	
	int calculateKey(); //if n<0 n+=bucketsize
	int checkIntersect();
	int calculateAABB();
	void cleanHashTable();

};

