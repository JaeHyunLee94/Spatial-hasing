#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{
	timeStep = 0;
}

CollisionInfo CollisionDetector::detectCollision()
{

	
	/*
	TODO: detect algorithm

	1. mesh �迭�κ��� vertice����  mapping
	2. for each tet
		{
			calculate aabb;
			calculate overlapping cell
			�ĺ� vertice ���

			�ĺ� vertice �� �浹�Ѵٸ�
			contactinfo list�� object ������ �Բ� ����
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

				1.hash ��� �� mapping
				2. mapping �ϸ� timestamp �����͵� ����
			
			}

		}
		
	*/
}

int CollisionDetector::calculateAABB()
{

	/*
	* TODO: tet ������ aabb ������ִ� �Լ�
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
