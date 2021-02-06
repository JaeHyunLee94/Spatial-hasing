#include <iostream>
#include <cassert>
#include <glm/glm.hpp>
#include "CollisionDetector.h"

int main(int argc, char** argv) {

	CollisionDetector detector;

	MockingMesh mesh1;
	mesh1.vertices.push_back(glm::vec3(1.1, 1.1, 1.1));
	mesh1.vertices.push_back(glm::vec3(3.2, 5.4, 5.4));
	mesh1.vertices.push_back(glm::vec3(5.4, 3.2, 5.4));
	mesh1.vertices.push_back(glm::vec3(5.4, 5.4, 3.2));
	

	mesh1.tet.push_back(MockingTet{
			0,1,2,3
		}
	);
	


	MockingMesh mesh2;
	
	mesh2.vertices.push_back(glm::vec3(2.1, 2.1, 2.1));
	mesh2.vertices.push_back(glm::vec3(2.5, 2.9, 2.9));
	mesh2.vertices.push_back(glm::vec3(2.9, 2.5, 2.9));
	mesh2.vertices.push_back(glm::vec3(2.9, 2.9, 2.5));

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


	std::cout << "output collision vector size : " << outPut.size() << "\n";
	for (int i = 0; i < outPut.size(); i++) {

		std::cout << "penetrated mesh: " << outPut[i].penetratedMesh << '\n';
		std::cout << "penetrating mesh: " << outPut[i].penetratingMesh << '\n';
		std::cout << "vertex list: \n";
		for (int j = 0; j < outPut[i].verticeList.size(); j++) {
			std::cout << outPut[i].verticeList[j] << " ";

		}
		std::cout << "\n";




	}

	

	

	return 0;
}