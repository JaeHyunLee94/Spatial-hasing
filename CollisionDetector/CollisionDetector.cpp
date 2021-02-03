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

	1. mesh �迭�κ��� vertice����  mapping
	2. for each obj
		for each tet
		{
			calculate aabb;
			calculate overlapping cell
			�ĺ� vertice ��� --> timestamp lazy update

			�ĺ� vertice �� �浹�Ѵٸ�
			contactinfo list�� object ������ �Բ� ����
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

				1.hash ��� �� mapping
				2. mapping �ϸ� timestamp �����͵� ����
			
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
	* TODO: tet ������ aabb ������ִ� �Լ�
		min x,y,z, max x,y,z
	*
	*/
	return 0;
}

void CollisionDetector::cleanHashTable()
{
	/*
	* TODO: �ֱ������� hash table clean
	*/


}
