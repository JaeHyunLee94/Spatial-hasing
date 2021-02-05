#include "CollisionDetector.h"


void CollisionDetector::addObject(MockingMesh* mesh)
{
	assert(mesh != nullptr && mesh != NULL);
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

vector<CollisionInfo> CollisionDetector::detectCollision()
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

			 같은 tetrahedron 이면 넣지 않기
		}

		timestamp++;
	*/

	vector<CollisionInfo> ret;
	

	mapVertices();

	//iter all mesh
	for (int mesh_inx = 0; mesh_inx < m_obj_list.size(); mesh_inx++) {
		

		MockingMesh* tmp_mesh = m_obj_list[mesh_inx];
		CollisionInfo tmp_info;
		tmp_info.penetratedMesh = tmp_mesh;
		ret.push_back(tmp_info);
		// iter each tetrahedron
		for (int tet_inx = 0; tet_inx < tmp_mesh->tet.size(); tet_inx++) {
			

			glm::vec3 aabb_min;
			glm::vec3 aabb_max;
			calculateAABB(tmp_mesh, tet_inx, aabb_min, aabb_max);
			
			//iter overlapping cell
			for (int x = (int)aabb_min.x; x <= (int)aabb_max.x; x++) {
				for (int y = (int)aabb_min.y; y <= (int)aabb_max.y;  y++) {
					for (int z = (int)aabb_min.z; z <= (int)aabb_max.z; z++) {


						int key = calculateKey(x, y, z);

						for (list<MappedVertice>::iterator iter = hashTable[key].begin() ; iter->timeStamp <= timeStamp ; iter++) {

							// penetrating candidate vertex 
							int obj_index = iter->obj_index;
							int vertex_index = iter->vectice_index;
							glm::vec3 point = m_obj_list[obj_index]->vertices[vertex_index];
							
							if (IsIntersect(tmp_mesh,tet_inx, point )) {

								bool find = false;
								for (int col_inx = 0; col_inx < ret.size(); col_inx++) {

									if (ret[col_inx].penetratingMesh == m_obj_list[obj_index] && ret[col_inx].penetratedMesh == tmp_mesh) {
										find = true;
										ret[col_inx].verticeList.push_back(vertex_index);
										break;
									}

								}
								if (!find) {
									assert(tmp_mesh != nullptr);
									assert(m_obj_list[obj_index] != nullptr);
									ret.push_back(
										CollisionInfo{
											tmp_mesh,
											m_obj_list[obj_index],
											vector<int>(1,vertex_index)
										}
									);
								}
								


							}


						}




					}
				}
			}



		}





	}

	if (timeStamp % 10000 == 9999) {
		cleanHashTable();
		timeStamp = 0;
	}

	timeStamp++;
	return ret;
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

			hashTable[key].push_front(
				MappedVertice{
					i,
					v,
					timeStamp
				}
			);



		}



	}
}

int CollisionDetector::calculateKey(float x, float y, float z)
{
	int ret= ( ((int)(x / gridSize) * p1) ^ ((int)(y / gridSize) * p2) ^ ((int)(z / gridSize)*p3) ) % n;

	return ret;
}

bool CollisionDetector::IsIntersect(MockingMesh* mesh, int tet_index, glm::vec3& point)
{
	/*
	* check intersect bewtween tetrahedron and vertex
	*/

	glm::vec3 x1 = mesh->vertices[mesh->tet[tet_index].id1];
	glm::vec3 x2 = mesh->vertices[mesh->tet[tet_index].id2];
	glm::vec3 x3 = mesh->vertices[mesh->tet[tet_index].id3];
	glm::vec3 x4 = mesh->vertices[mesh->tet[tet_index].id4];

	if (checkSamePoint(x1, point) || checkSamePoint(x2, point) || checkSamePoint(x3, point) || checkSamePoint(x4, point)) return false;

	glm::vec3 barycentricV1 = x2 - x1;
	glm::vec3 barycentricV2 = x3 - x1;
	glm::vec3 barycentricV3 = x4 - x1;
	glm::vec3 p_x0= point -x1; //p-x0 vector
	glm::mat3x3 A(barycentricV1, barycentricV2, barycentricV3);

	//what if non invertible?
	glm::mat3x3 Ainverse= glm::inverse(A);
	glm::vec3 solution = Ainverse * p_x0;

	if (solution.x > 0 && solution.y > 0 && solution.z > 0 && solution.x + solution.y + solution.z < 1) return true;
	return false;
}

void CollisionDetector::calculateAABB(MockingMesh* mesh, int tet_index,glm::vec3& minout,glm::vec3& maxout)
{

	/*
	* TODO: tet 넣으면 aabb 계산해주는 함수
		min x,y,z, max x,y,z
	*
	*/
	float minx, miny, minz, maxx, maxy, maxz;

	
	glm::vec3 p1 = mesh->vertices[mesh->tet[tet_index].id1];
	glm::vec3 p2 = mesh->vertices[mesh->tet[tet_index].id2];
	glm::vec3 p3 = mesh->vertices[mesh->tet[tet_index].id3];
	glm::vec3 p4 = mesh->vertices[mesh->tet[tet_index].id4];

	minx = min({p1.x,p2.x,p3.x,p4.x});
	miny = min({ p1.y,p2.y,p3.y,p4.y });
	minz = min({ p1.z,p2.z,p3.z,p4.z });

	maxx = max({ p1.x,p2.x,p3.x,p4.x });
	maxy = max({ p1.y,p2.y,p3.y,p4.y });
	maxz = max({ p1.z,p2.z,p3.z,p4.z });

	minout.x = minx;
	minout.y = miny;
	minout.z = minz;

	maxout.x = maxx;
	maxout.y = maxy;
	maxout.z = maxz;


	return ;
}

void CollisionDetector::cleanHashTable()
{
	/*
	* TODO: 주기적으로 hash table clean
	*/


	/*for (int i = 0; i < n; i++) {
		for (vector<MappedVertice>::iterator iter = hashTable[i].begin() ; iter == hashTable[i].end();) {

			if (iter->timeStamp != timeStamp) {
				iter = hashTable[i].erase(iter);
			}
			else {
				iter++;
			}

		}
	}*/
	for (int i = 0; i < n; i++) {
		hashTable[i].clear();
	}
	

}

bool CollisionDetector::checkSamePoint(glm::vec3& point1, glm::vec3& point2)
{
	
	if (abs(point1.x - point2.x) < epsilone && abs(point1.y - point2.y) < epsilone && abs(point1.z - point2.z) < epsilone) return true;
	return false;
}
