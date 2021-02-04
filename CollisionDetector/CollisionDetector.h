#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <vector>


using namespace std;

/*
TODO: ������ �����ϰ� unit test �ϱ� 
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


	//TODO: index �� ���� ����
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


	//TODO: table initialize 
	CollisionDetector() :p1(73856093), p2(19349663), p3(83492791), n(1000), gridSize(1), timeStamp(0) {
		/*
			large prime number
		*/
		hashTable.reserve(n);

	};
	~CollisionDetector();


	void addObject(MockingMesh* mesh);
	void setHashParam(int p1, int p2, int p3, int tableSize, float gridSize);
	
	vector<CollisionInfo> detectCollision();
	





private:

	vector<MockingMesh*> m_obj_list;
	//TODO: linked list vs vector 
	vector<vector<MappedVertice>> hashTable; 




	void mapVertices(); //timestamp update
	
	int calculateKey(float x, float y, float z); //if n<0 n+=bucketsize
	bool IsIntersect(MockingMesh* mesh, int tet_index, glm::vec3& point);
	void calculateAABB(MockingMesh* mesh, int tet_index, glm::vec3& minout, glm::vec3& maxout);
	void cleanHashTable();

};

