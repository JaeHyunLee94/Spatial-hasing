#include "pch.h"
#include "CppUnitTest.h"
#include "../include/glm/glm.hpp"
#include "../CollisionDetector/CollisionDetector.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
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
			mesh2.vertices.push_back(glm::vec3(0.1, 0.1, 0.1));
			mesh2.vertices.push_back(glm::vec3(-0.4, 0, 0));
			mesh2.vertices.push_back(glm::vec3(0, -0.4, 0));
			mesh2.vertices.push_back(glm::vec3(0, 0, -0.4));

			mesh2.tet.push_back(MockingTet{
					0,1,2,3
				}
			);

			detector.addObject(&mesh1);
			detector.addObject(&mesh2);


			Assert::AreEqual(true, detector.IsIntersect(&mesh1, 0, glm::vec3(0.2, 0.2, 0.2)));

			
		}
	};
}
