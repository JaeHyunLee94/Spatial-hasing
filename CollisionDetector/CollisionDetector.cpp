#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{
	timeStep = 0;
}

CollisionInfo CollisionDetector::detectCollision()
{

	
	/*
	TODO: detect algorithm

	1. mesh 배열로부터 vertice들을  mapping
	2. for each tet
		{
			calculate aabb;
			calculate overlapping cell
			후보 vertice 계산

			후보 vertice 중 충돌한다면
			contactinfo list에 object 정보와 함께 넣음
 		}

		timestamp++;
	*/
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
}

int CollisionDetector::calculateAABB()
{

	/*
	* TODO: tet 넣으면 aabb 계산해주는 함수
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
