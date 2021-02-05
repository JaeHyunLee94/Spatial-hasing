#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>


using namespace std;

/*
TODO: 변수명 정리하고 unit test 하기 
*/


struct MockingTet {
	int id1;
	int id2;
	int id3;
	int id4;
};


struct MockingMesh{
	//tet info
	vector<MockingTet> tet;
	vector<glm::vec3> vertices;
};

struct MappedVertice {
	
	int obj_index;
	int vectice_index;
	int timeStamp;
};

struct CollisionInfo {

	MockingMesh* penetratedMesh=nullptr;
	MockingMesh* penetratingMesh=nullptr;


	//TODO: index 로 줄지 결정
	vector<int> verticeList;
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
	float epsilone;


	//TODO: table initialize 
	CollisionDetector() :p1(73856093), p2(19349663), p3(83492791), n(10), gridSize(1), timeStamp(0),epsilone(0.0000001) {
		/*
			large prime number
		*/
		for (int i = 0; i < n; i++) hashTable.push_back(list<MappedVertice>());
		

	};
	~CollisionDetector() {
	};


	void addObject(MockingMesh* mesh);
	void setHashParam(int p1, int p2, int p3, int tableSize, float gridSize);
	
	vector<CollisionInfo> detectCollision();
	

	vector<MockingMesh*> m_obj_list;
	//TODO: linked list vs vector 
	vector<list<MappedVertice>> hashTable;



	void mapVertices(); //timestamp update

	int calculateKey(float x, float y, float z); //if n<0 n+=bucketsize
	bool IsIntersect(MockingMesh* mesh, int tet_index, glm::vec3& point);
	void calculateAABB(MockingMesh* mesh, int tet_index, glm::vec3& minout, glm::vec3& maxout);
	void cleanHashTable();
	bool checkSamePoint(glm::vec3& point1, glm::vec3& point2);
	void makeVectorUnique(vector<int>& v);



private:

	

};

