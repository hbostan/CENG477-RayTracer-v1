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

			int j = 0;
			for(int i = 0; i < camera.image_width * camera.image_height; i++)
			{
				image[j++] = background_color.x;
				image[j++] = background_color.y;
				image[j++] = background_color.z;
			}

			int i = 0;
			for(int y = 0; y < camera.image_height; ++y)
			{
				for(int x = 0; x < camera.image_width; ++x)
				{
					Ray ray = camera.makeRay(x, y);
					i = (y * camera.image_width + x) * 3;

					for(auto it = triangles.begin(); it != triangles.end(); it++)
					{
						Intersection intersection(ray);
						if(it->intersect(intersection, vertex_data))
						{
							image[i++] = 0;
							image[i++] = 255;
							image[i++] = 255;
						}
					}

					i = (y * camera.image_width + x) * 3;

					for(auto it = spheres.begin(); it != spheres.end(); it++)
					{
						Intersection intersection(ray);
						it->intersect(intersection, vertex_data);
						if(intersection.pSphere)
						{
							image[i++] = 255;
							image[i++] = 0;
							image[i++] = 255;
						}
					}

					i = (y * camera.image_width + x) * 3;

					for(auto it = meshes.begin(); it != meshes.end(); it++)
					{
						Mesh mesh = (*it);

						for(auto it2 = mesh.faces.begin(); it2 != mesh.faces.end(); it2++)
						{
							Triangle triangle;
							triangle.material_id = mesh.material_id;
							triangle.indices = (*it2);

							Intersection intersection(ray);
							if(triangle.intersect(intersection, vertex_data))
							{
								image[i++] = 255;
								image[i++] = 255;
								image[i++] = 0;
							}
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
