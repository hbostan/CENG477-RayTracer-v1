#ifndef __HW1__PARSER__
#define __HW1__PARSER__

#include <iostream>
#include <string>
#include <vector>
#include "Vector.h"
#include "Ray.h"
#include "ppm.h"
using namespace std;
namespace parser
{
	//Notice that all the structures are as simple as possible
	//so that you are not enforced to adopt any style or design.
	/*struct Vec3f
	{
		float x, y, z;
	};

	struct Vec3i
	{
		int x, y, z;
	};

	struct Vec4f
	{
		float x, y, z, w;
	};*/

	struct Camera
	{
		Point position;
		Vec3f gaze;
		Vec3f up;
		Vec4f near_plane;
		float near_distance;
		int image_width, image_height;
		std::string image_name;
	};

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

	struct Sphere
	{
		int material_id;
		int center_vertex_id;
		float radius;
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

		float SphereIntersect(const Ray &ray, const Sphere &sphere)
		{
			float root1, root2;

			Vec3f direction = ray.direction;
			Vec3f distance_vector = ray.origin - vertex_data[sphere.center_vertex_id];
			
			float A = direction.dot(direction);
			float B = direction.dot(distance_vector) * 2;
			float C = distance_vector.dot(distance_vector) - sphere.radius * sphere.radius;

			float discriminant = B * B - 4 * A * C;
			if(discriminant < 0) return false;
			else
			{
				root1 = (-B + discriminant)/(2*A);
				root2 = (-B - discriminant)/(2*A); 
			}

			float small = root1 < root2 ? root1 : root2;
			float big = root1 > root2 ? root1 : root2;

			if(small < 0)
			{
				if(big < 0) return -1;
				return big;
			}
			else
			{
				return small;
			}

		}

		void Render(Camera camera)
		{
			Vec3f right_vector = camera.up.cross(-camera.gaze);
			
			cout << "hebele" << endl;

			float left = camera.near_plane.x;
			float right = camera.near_plane.y;
			float bottom = camera.near_plane.z;
			float top = camera.near_plane.w;

			Point m = camera.position + camera.gaze * camera.near_distance;
			Point q = m + (right_vector * left + camera.up * top);

			float horizontal_step = (right - left)/camera.image_width;
			float vertical_step = (top - bottom)/camera.image_height;

			unsigned char* image = new unsigned char[camera.image_width * camera.image_height * 3];

			int i = 0;
			for(int y = 0; y < camera.image_height; ++y)
			{
				for(int x = 0; x < camera.image_width; ++x)
				{
					float u = left + horizontal_step * (x+0.5);
					float v = top - vertical_step * (y+0.5);

					Point s = q + camera.up * u + right_vector * v;

					Vec3f d = s - camera.position;
					d.normalize();

					Ray ray(camera.position, d);

					for(auto it = spheres.begin(); it != spheres.end(); it++)
					{
						i = (y * camera.image_width + x)*3;
						if(SphereIntersect(ray, *(it)) > 0)
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
