#include "CollisionDetector.h"


void CollisionDetector::addObject(MockingMesh* mesh)
{
	this->m_obj_list.push_back(mesh);
}

void CollisionDetector::setHashParam(int p1, int p2, int p3, int tableSize, float gridSize)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->n = tableSize;
	this->gridSize = gridSize;
}

CollisionInfo CollisionDetector::detectCollision()
{

	
	/*
	TODO: detect algorithm

	1. mesh 배열로부터 vertice들을  mapping
	2. for each obj
		for each tet
		{
			calculate aabb;
			calculate overlapping cell
			후보 vertice 계산 --> timestamp lazy update

			후보 vertice 중 충돌한다면
			contactinfo list에 object 정보와 함께 넣음
 		}

		timestamp++;
	*/

	mapVertices();

	
	timeStamp++;
	return CollisionInfo();
}

void CollisionDetector::mapVertices()
{

	/*
	TODO: vertice mapping algorithm

		1. for each object{
			
			for each vertex{

				1.hash 계산 후 mapping
				2. mapping 하며 timestamp 지난것들 삭제
			
			}

		}
		
	*/

	for (int i = 0; i < m_obj_list.size(); i++) {

		for (int v = 0; v < m_obj_list[i]->vertices.size(); v++) {

			glm::vec3 pos = m_obj_list[i]->vertices[v];
			int key = calculateKey(pos.x, pos.y, pos.z);

			hashTable[key].push_back(
				MappedVertice{
					i,
					v,
					timeStamp
				}
			)



		}



	}




}

int CollisionDetector::calculateKey(float x,float y, float z)
{
	int ret= ( (int)(x / gridSize) * p1 + (int)(y / gridSize) * p2 + (int)(z / gridSize)*p3) % n;

	return ret;
}

int CollisionDetector::calculateAABB()
{

	/*
	* TODO: tet 넣으면 aabb 계산해주는 함수
		min x,y,z, max x,y,z
	*
	*/
	return 0;
}

void CollisionDetector::cleanHashTable()
{
	/*
	* TODO: 주기적으로 hash table clean
	*/


}
