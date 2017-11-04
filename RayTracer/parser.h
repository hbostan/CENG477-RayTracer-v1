#ifndef __HW1__PARSER__
#define __HW1__PARSER__

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
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

		inline int clamp(float n) 
		{
			return (int)(round(max(0.0f, min(n, 255.0f))));
		}

		//TODO iterate over cameras
		void Render(Camera &camera);

		Intersection getIntersection(Ray &ray);
		Vec3f castRay(Ray& ray, int level);
		//TODO add reflections here
		//TODO add reflection counter into Ray.
		Vec3f lightItUp(Intersection& intersection, int level);
		Vec3f getDiffuseSpecular(Intersection& intersection);
		

		//Functions
		void loadFromXml(const std::string& filepath);
	};
}
#endif