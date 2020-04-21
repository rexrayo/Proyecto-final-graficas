#include "Loaders.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Objff.h"
#include "Models.h"
#include <vector>


namespace CG
{ 
	void Load(const std::string path, Objff* objeto)
	{
		//Objff* objeto = Objff::Instance();
		//char cadena[128];
		std::string cadena;
		std::ifstream fe(path);
		std::ifstream fe2(path);
		int v=0, f=0, t=0;
		std::string num;
		vector<int> faces;

		//getline(fe, cadena);

		//if (cadena[0] == 'O' || cadena[1] == 'F' || cadena[2] == 'F')
		//{
		//	while (getline(fe, cadena))
		//	{
		//		if (cadena[0] == ' ' || cadena[0] == '#')
		//		{
		//			cadena.clear();
		//		}
		//		if (isdigit(cadena[0]))
		//		{
		//			std::istringstream be(cadena.substr(0));
		//			be >> v; 
		//			be >> f; 
		//			be >> t;
		//			//std::cout << v << " " << f;
		//			
		//			glm::vec3 vert;
		//			double x, y, z;
		//			for (int i = 0; i < v; i++)
		//			{
		//				getline(fe, cadena);
		//				std::istringstream se(cadena.substr(0));
		//				se >> x; 
		//				se >> y; 
		//				se >> z;
		//				
		//				/*if (objeto->maxX == 0 && objeto->maxY == 0 && objeto->maxZ == 0 &&
		//					objeto->minX == 0 && objeto->minY == 0 && objeto->minZ == 0)
		//				{
		//					objeto->maxX = x;
		//					objeto->minX = x;
		//					objeto->maxY = y;
		//					objeto->minY = y;
		//					objeto->maxZ = z;
		//					objeto->minZ = z;
		//					objeto->MaxX = glm::vec3(x, y, z);
		//					objeto->MaxY = glm::vec3(x, y, z);
		//					objeto->MaxZ = glm::vec3(x, y, z);
		//					objeto->MinX = glm::vec3(x, y, z);
		//					objeto->MinY = glm::vec3(x, y, z);
		//					objeto->MinZ = glm::vec3(x, y, z);
		//				}

		//				if (objeto->maxX < x)
		//				{
		//					objeto->maxX = x;
		//					objeto->MaxX = glm::vec3(x, y, z);
		//				}
		//				if (objeto->maxY< y)
		//				{
		//					objeto->maxY = y;
		//					objeto->MaxY = glm::vec3(x, y, z);
		//				}
		//				if (objeto->maxZ < z)
		//				{
		//					objeto->maxZ = z;
		//					objeto->MaxZ = glm::vec3(x, y, z);
		//				}
		//				if (objeto->minX > x)
		//				{
		//					objeto->minX = x;
		//					objeto->MinX = glm::vec3(x, y, z);
		//				}
		//				if (objeto->minY > y)
		//				{
		//					objeto->minY = y;
		//					objeto->MinY = glm::vec3(x, y, z);
		//				}
		//				if (objeto->minZ > z)
		//				{
		//					objeto->minZ = z;
		//					objeto->MinZ = glm::vec3(x, y, z);
		//				}*/

		//				vert = glm::vec3(x, y, z);
		//				objeto->v.push_back(vert);
		//			}
		//			//glm::vec3 maxVec = glm::vec3(objeto->maxX, objeto->maxY, objeto->maxZ);
		//			//glm::vec3 minVec = glm::vec3(objeto->minX, objeto->minY, objeto->minZ);

		//			//glm::vec3 center = (maxVec - minVec) / 2.0f;

		//			/*for (int pii = 0; pii < objeto->v.size(); pii++)
		//			{
		//				objeto->v[pii] = (objeto->v[pii] - center);
		//			}*/

		//			for (int ji = 0; ji < f; ji++)
		//			{
		//				getline(fe, cadena);
		//				std::istringstream se(cadena.substr(0));
		//				int l = 0, cont = 0, temp = 0;
		//				vector<int>xyz;
		//				se >> l;
		//				while (cont != l) {
		//					se >> temp;
		//					xyz.push_back(temp);
		//					cont++;
		//				}
		//				for (int ij = 0; ij < l-2; ij++)
		//				{
		//					objeto->f.push_back(glm::vec3(xyz[0], xyz[ij+1], xyz[ij+2]));
		//					
		//				}

		//			}
		//			for (int j = 0; j < objeto->f.size(); j++)
		//			{
		//				glm::vec3 x, y, z, edge1, edge2;
		//				x = objeto->v[objeto->f[j].x];
		//				y = objeto->v[objeto->f[j].y];
		//				z = objeto->v[objeto->f[j].z];
		//				edge1 = y - x;
		//				edge2 = z - x;
		//				objeto->fn.push_back(normalize(cross(edge1, edge2)));
		//			}

		//			for (int i = 0; i < objeto->v.size(); i++)
		//			{
		//				vector<glm::vec3> sum;
		//		
		//				for (int j = 0; j < objeto->f.size(); j++)
		//				{
		//					if (float(i) == objeto->f[j].x || float(i) == objeto->f[j].y || float(i) == objeto->f[j].z) {
		//						sum.push_back(objeto->fn[j]);
		//					}
		//				}

		//				for (int l = 1; l < sum.size(); l++)
		//				{
		//					sum[0] += sum[l];
		//				}

		//				objeto->vn.push_back(glm::normalize(sum[0]));
		//			}




		//		}
		//	}

		//	
		//	for (auto face : objeto->f)
		//	{
		//		objeto->drawArrays.push_back(objeto->v[int(face[0])]);
		//		objeto->drawArrays.push_back(objeto->v[int(face[1])]);
		//		objeto->drawArrays.push_back(objeto->v[int(face[2])]);
		//		glm::vec3 tem = glm::vec3 ( (objeto->v[face[0]].x + objeto->v[face[1]].x + objeto->v[face[2]].x) / 3,
		//									(objeto->v[face[0]].y + objeto->v[face[1]].y + objeto->v[face[2]].y) / 3,
		//									(objeto->v[face[0]].z + objeto->v[face[1]].z + objeto->v[face[2]].z) / 3);
		//		objeto->fc.push_back(tem);
		//	}
		//	
		//}
		//else
		//{

			std::string a, x, y, z;

			while (getline(fe2, cadena))
			{
				std::istringstream be(cadena.substr(0));
				be >> a;
				
				if (a == "v")
				{
					glm::vec3 vertex;
					be >> vertex.x;
					be >> vertex.y;
					be >> vertex.z;

					objeto->v.push_back(vertex);

				}
				else if (a == "vt")
				{
					//getline(fe, cadena);
				}
				else if (a == "vn")
				{
					//getline(fe, cadena);
				}
				else if (a == "f")
				{
					/*glm::vec3 vertex;
		
					be >> vertex.x;
					be >> vertex.y;
					be >> vertex.z;


					std::cout << "hola";*/

					bool tri = true;
					glm::vec3 vertex;
					int fac, ant = 10000000000;
					std::vector <float> final;
					
					while (tri)
					{
						be >> x;
						std::istringstream ce(x.substr(0));
						ce >> fac;
						if (ant != fac) {
							final.push_back(fac);
							ant = fac;
						}
						else
						{
							tri = false;
							//std::cout << "hola";
						}
					}
					if (final.size() >0)
					{
						for (int k = 0; k < final.size()-2; k++)
						{
							objeto->f.push_back(glm::vec3(final[0]-1, final[k+1]-1, final[k+2]-1));
							objeto->fArray.push_back(glm::vec3(final[0] - 1, final[k + 1] - 1, final[k + 2] - 1));
							objeto->fArray.push_back(glm::vec3(final[0] - 1, final[k + 1] - 1, final[k + 2] - 1));
							objeto->fArray.push_back(glm::vec3(final[0] - 1, final[k + 1] - 1, final[k + 2] - 1));
						}
					}

				}
			}

			for (int j = 0; j < objeto->f.size(); j++)
			{
				glm::vec3 x, y, z, edge1, edge2;
				x = objeto->v[objeto->f[j].x];
				y = objeto->v[objeto->f[j].y];
				z = objeto->v[objeto->f[j].z];
				edge1 = (y - x);
				edge2 = (z - x);
				
				objeto->fn.push_back(glm::normalize(glm::cross(edge1, edge2)));

				//objeto->drawArrays.push_back(objeto->v[int(objeto->f[j].x)]);
				//objeto->drawArrays.push_back(objeto->v[int(objeto->f[j].y)]);
				//objeto->drawArrays.push_back(objeto->v[int(objeto->f[j].z)]);

				glm::vec3 tem = glm::vec3((objeto->v[objeto->f[j].x].x + objeto->v[objeto->f[j].y].x + objeto->v[objeto->f[j].z].x) / 3,
					(objeto->v[objeto->f[j].x].y + objeto->v[objeto->f[j].y].y + objeto->v[objeto->f[j].z].y) / 3,
					(objeto->v[objeto->f[j].x].z + objeto->v[objeto->f[j].y].z + objeto->v[objeto->f[j].z].z) / 3);
				objeto->fc.push_back(tem);


			}

			for (int i = 0; i < objeto->v.size(); i++)
			{
				vector<glm::vec3> sum;
				glm::vec3 res = glm::vec3(0);

				for (int j = 0; j < objeto->f.size(); j++)
				{
					if (i == objeto->f[j].x || i == objeto->f[j].y || i == objeto->f[j].z) {
						sum.push_back(objeto->fn[j]);
					}
				}

				for (int l = 0; l < sum.size(); l++)
				{
					res += sum[l];
				}

				objeto->vn.push_back(glm::vec3(res.x/sum.size(), res.y / sum.size(), res.z / sum.size()));
				res = glm::vec3(0);
			}

			for (auto face : objeto->f)
			{
				objeto->drawArrays.push_back(objeto->v[int(face[0])]);
				objeto->drawArrays.push_back(objeto->v[int(face[1])]);
				objeto->drawArrays.push_back(objeto->v[int(face[2])]);

				objeto->vnArrays.push_back(objeto->vn[int(face[0])]);
				objeto->vnArrays.push_back(objeto->vn[int(face[1])]);
				objeto->vnArrays.push_back(objeto->vn[int(face[2])]);
			}
		//}
		fe.close();
		fe2.close();

		
	}

	void LoadObj(const std::string path) {
		glm::vec3 test;
	}

	void LoadOff(const std::string path) {
		glm::vec3 test;
	}
}
