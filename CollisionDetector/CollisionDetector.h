#pragma once


#include <unordered_map>
#include <vector>


using namespace std;


struct MockingMesh{
	//tet info

	vector<glm::vec3> vertices;
};

struct MappedVertice {
	
	int obj_index;
	int vectice_index;
	int timeStamp;
};

class CollisionInfo {

	MockingMesh* penetratedMesh;
	MockingMesh* penetratingMesh;


	//TODO: index 로 줄지 결정
	vector<glm::vec3> verticeList;


};


 
class CollisionDetector
{

	/*
	* collision detection class using spatial hashing
	*/

public:

	int timeStamp;
	

	//hash parameter
	int p1, p2, p3;

	int n;//table size
	float gridSize;


	//TODO: table initialize 
	CollisionDetector() :p1(5), p2(6), p3(7), n(1000), gridSize(1), timeStamp(0) {

	};
	~CollisionDetector();


	void addObject(MockingMesh* mesh);
	void setHashParam(int p1, int p2, int p3, int tableSize, float gridSize);
	
	CollisionInfo detectCollision();
	void mapVertices();




private:

	vector<MockingMesh*> m_obj_list;
	//TODO: hash table 을 list로도 구현가능?
	vector<vector<MappedVertice>> hashTable; 




	void mapVertices(); //timestamp update
	
	int calculateKey(float x, float y, float z); //if n<0 n+=bucketsize
	int checkIntersect();
	int calculateAABB();
	void cleanHashTable();

};

