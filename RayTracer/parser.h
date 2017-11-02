#ifndef __HW1__PARSER__
#define __HW1__PARSER__

#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include "Vector.h"
#include "Camera.h"
#include "Shape.h"
#include "Ray.h"
#include "ppm.h"
using namespace std;
namespace parser
{
	struct PointLight
	{
		Vec3f position;
		Vec3f intensity;
	};

	struct Material
	{
		Vec3f ambient;
		Vec3f diffuse;
		Vec3f specular;
		Vec3f mirror;
		float phong_exponent;
	};

	struct Face
	{
		int v0_id;
		int v1_id;
		int v2_id;
	};

	struct Mesh
	{
		int material_id;
		std::vector<Face> faces;
	};

	struct Triangle
	{
		int material_id;
		Face indices;
	};
	
	struct Scene
	{
		//Data
		Vec3i background_color;
		float shadow_ray_epsilon;
		int max_recursion_depth;
		std::vector<Camera> cameras;
		Vec3f ambient_light;
		std::vector<PointLight> point_lights;
		std::vector<Material> materials;
		std::vector<Vec3f> vertex_data;
		std::vector<Mesh> meshes;
		std::vector<Triangle> triangles;
		std::vector<Sphere> spheres;

		void Render(Camera &camera)
		{
			camera.initCamera();
			unsigned char* image = new unsigned char[camera.image_width * camera.image_height * 3];

			int i = 0;
			for(int y = 0; y < camera.image_height; ++y)
			{
				for(int x = 0; x < camera.image_width; ++x)
				{
					Ray ray = camera.makeRay(x, y);

					for(auto it = spheres.begin(); it != spheres.end(); it++)
					{
						i = (y * camera.image_width + x) * 3;
						Intersection intersection(ray);
						it->intersect(intersection, vertex_data);
						if(intersection.pSphere)
						{
							image[i++] = 255;
							image[i++] = 0;
							image[i++] = 255;
						}
						else
						{
							image[i++] = 0;
							image[i++] = 0;
							image[i++] = 0;
						}
					}
				}
			}

			write_ppm("test.ppm", image, camera.image_width, camera.image_height);
		}

		//Functions
		void loadFromXml(const std::string& filepath);
	};
}

#endif
