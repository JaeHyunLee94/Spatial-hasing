#include <iostream>
#include <cassert>
#include <glm/glm.hpp>
#include "CollisionDetector.h"

int main(int argc, char** argv) {

	CollisionDetector detector;

	MockingMesh mesh1;
	mesh1.vertices.push_back(glm::vec3(0, 0, 0));
	mesh1.vertices.push_back(glm::vec3(1.2, 0, 0));
	mesh1.vertices.push_back(glm::vec3(0, 1.2, 0));
	mesh1.vertices.push_back(glm::vec3(0, 0, 1.2));
	mesh1.vertices.push_back(glm::vec3(1.2, 1.2, 1.2));

	mesh1.tet.push_back(MockingTet{
			0,1,2,3
		}
	);
	mesh1.tet.push_back(MockingTet{
			1,2,3,4
		}
	);


	MockingMesh mesh2;
	
	mesh2.vertices.push_back(glm::vec3(-0.4, 0, 0));
	mesh2.vertices.push_back(glm::vec3(0, -0.4, 0));
	mesh2.vertices.push_back(glm::vec3(0, 0, -0.4));
	mesh2.vertices.push_back(glm::vec3(0.1, 0.1, 0.1));

	mesh2.tet.push_back(MockingTet{
			0,1,2,3
		}
	);

	detector.addObject(&mesh1);
	detector.addObject(&mesh2);


	vector<CollisionInfo> outPut = detector.detectCollision();

	glm::vec3 t1(0.1, 0.1, 0.1);
	glm::vec3 t2(0.0, 0.5, 0.1);
	glm::vec3 t3(-0.1, -0.1, -0.1);
	glm::vec3 t4(0,0,0);


	
	std::cout << outPut.size() << "\n";
	std::cout << outPut[0].penetratedMesh << "\n";
	std::cout << outPut[0].penetratingMesh << "\n";
	std::cout << outPut[0].verticeList.size() << "\n\n";

	for (int i = 0; i < outPut[0].verticeList.size(); i++)std::cout << outPut[0].verticeList[i] << "\n\n";

	std::cout << outPut[1].penetratedMesh << "\n";
	std::cout << outPut[1].penetratingMesh << "\n";
	std::cout << outPut[1].verticeList.size() << "\n\n";
	for(int i=0;i<outPut[1].verticeList.size();i++)std::cout << outPut[1].verticeList[i] << "\n";

	

	return 0;
}