#include "parser.h"
#include "tinyxml2.h"
#include <sstream>
#include <stdexcept>

void parser::Scene::loadFromXml(const std::string& filepath)
{
	tinyxml2::XMLDocument file;
	std::stringstream stream;

	auto res = file.LoadFile(filepath.c_str());
	if (res)
	{
		throw std::runtime_error("Error: The xml file cannot be loaded.");
	}

	auto root = file.FirstChild();
	if (!root)
	{
		throw std::runtime_error("Error: Root is not found.");
	}

	//Get BackgroundColor
	auto element = root->FirstChildElement("BackgroundColor");
	if (element)
	{
		stream << element->GetText() << std::endl;
	}
	else
	{
		stream << "0 0 0" << std::endl;
	}
	stream >> background_color.x >> background_color.y >> background_color.z;

	//Get ShadowRayEpsilon
	element = root->FirstChildElement("ShadowRayEpsilon");
	if (element)
	{
		stream << element->GetText() << std::endl;
	}
	else
	{
		stream << "0.001" << std::endl;
	}
	stream >> shadow_ray_epsilon;

	//Get MaxRecursionDepth
	element = root->FirstChildElement("MaxRecursionDepth");
	if (element)
	{
		stream << element->GetText() << std::endl;
	}
	else
	{
		stream << "0" << std::endl;
	}
	stream >> max_recursion_depth;

	//Get Cameras
	element = root->FirstChildElement("Cameras");
	element = element->FirstChildElement("Camera");
	Camera camera;
	while (element)
	{
		auto child = element->FirstChildElement("Position");
		stream << child->GetText() << std::endl;
		child = element->FirstChildElement("Gaze");
		stream << child->GetText() << std::endl;
		child = element->FirstChildElement("Up");
		stream << child->GetText() << std::endl;
		child = element->FirstChildElement("NearPlane");
		stream << child->GetText() << std::endl;
		child = element->FirstChildElement("NearDistance");
		stream << child->GetText() << std::endl;
		child = element->FirstChildElement("ImageResolution");
		stream << child->GetText() << std::endl;
		child = element->FirstChildElement("ImageName");
		stream << child->GetText() << std::endl;

		stream >> camera.position.x >> camera.position.y >> camera.position.z;
		stream >> camera.gaze.x >> camera.gaze.y >> camera.gaze.z;
		stream >> camera.up.x >> camera.up.y >> camera.up.z;
		stream >> camera.near_plane.x >> camera.near_plane.y >> camera.near_plane.z >> camera.near_plane.w;
		stream >> camera.near_distance;
		stream >> camera.image_width >> camera.image_height;
		stream >> camera.image_name;

		cameras.push_back(camera);
		element = element->NextSiblingElement("Camera");
	}

	//Get Lights
	element = root->FirstChildElement("Lights");
	auto child = element->FirstChildElement("AmbientLight");
	stream << child->GetText() << std::endl;
	stream >> ambient_light.x >> ambient_light.y >> ambient_light.z;
	element = element->FirstChildElement("PointLight");
	PointLight point_light;
	while (element)
	{
		child = element->FirstChildElement("Position");
		stream << child->GetText() << std::endl;
		child = element->FirstChildElement("Intensity");
		stream << child->GetText() << std::endl;

		stream >> point_light.position.x >> point_light.position.y >> point_light.position.z;
		stream >> point_light.intensity.x >> point_light.intensity.y >> point_light.intensity.z;

		point_lights.push_back(point_light);
		element = element->NextSiblingElement("PointLight");
	}

	//Get Materials
	element = root->FirstChildElement("Materials");
	element = element->FirstChildElement("Material");
	Material material;
	while (element)
	{
		child = element->FirstChildElement("AmbientReflectance");
		stream << child->GetText() << std::endl;
		child = element->FirstChildElement("DiffuseReflectance");
		stream << child->GetText() << std::endl;
		child = element->FirstChildElement("SpecularReflectance");
		stream << child->GetText() << std::endl;
		child = element->FirstChildElement("MirrorReflectance");
		stream << child->GetText() << std::endl;
		child = element->FirstChildElement("PhongExponent");
		stream << child->GetText() << std::endl;

		stream >> material.ambient.x >> material.ambient.y >> material.ambient.z;
		stream >> material.diffuse.x >> material.diffuse.y >> material.diffuse.z;
		stream >> material.specular.x >> material.specular.y >> material.specular.z;
		stream >> material.mirror.x >> material.mirror.y >> material.mirror.z;
		stream >> material.phong_exponent;

		materials.push_back(material);
		element = element->NextSiblingElement("Material");
	}

	//Get VertexData
	element = root->FirstChildElement("VertexData");
	stream << element->GetText() << std::endl;
	Vec3f vertex;
	while (!(stream >> vertex.x).eof())
	{
		stream >> vertex.y >> vertex.z;
		vertex_data.push_back(vertex);
	}
	stream.clear();

	//Get Meshes
	element = root->FirstChildElement("Objects");
	element = element->FirstChildElement("Mesh");
	Mesh mesh;
	while (element)
	{
		child = element->FirstChildElement("Material");
		stream << child->GetText() << std::endl;
		stream >> mesh.material_id;
		mesh.material_id--;

		child = element->FirstChildElement("Faces");
		stream << child->GetText() << std::endl;
		Face face;
		while (!(stream >> face.v0_id).eof())
		{
			face.v0_id--;
			stream >> face.v1_id >> face.v2_id;
			face.v1_id--;
			face.v2_id--;
			mesh.faces.push_back(face);
		}
		stream.clear();

		meshes.push_back(mesh);
		mesh.faces.clear();
		element = element->NextSiblingElement("Mesh");
	}
	stream.clear();

	//Get Triangles
	element = root->FirstChildElement("Objects");
	element = element->FirstChildElement("Triangle");
	Triangle triangle;
	while (element)
	{
		child = element->FirstChildElement("Material");
		stream << child->GetText() << std::endl;
		stream >> triangle.material_id;
		triangle.material_id--;

		child = element->FirstChildElement("Indices");
		stream << child->GetText() << std::endl;
		stream >> triangle.indices.v0_id >> triangle.indices.v1_id >> triangle.indices.v2_id;
		triangle.indices.v0_id--;
		triangle.indices.v1_id--;
		triangle.indices.v2_id--;

		triangles.push_back(triangle);
		element = element->NextSiblingElement("Triangle");
	}

	//Get Spheres
	element = root->FirstChildElement("Objects");
	element = element->FirstChildElement("Sphere");
	Sphere sphere;
	while (element)
	{
		child = element->FirstChildElement("Material");
		stream << child->GetText() << std::endl;
		stream >> sphere.material_id;
		sphere.material_id--;

		child = element->FirstChildElement("Center");
		stream << child->GetText() << std::endl;
		stream >> sphere.center_vertex_id;
		sphere.center_vertex_id--;

		child = element->FirstChildElement("Radius");
		stream << child->GetText() << std::endl;
		stream >> sphere.radius;

		spheres.push_back(sphere);
		element = element->NextSiblingElement("Sphere");
	}
}

void parser::Scene::Render(Camera &camera)
{
	camera.initCamera();
	unsigned char* image = new unsigned char[camera.image_width * camera.image_height * 3];

	int i = 0;

	for (int y = 0; y < camera.image_height; ++y)
	{
		for (int x = 0; x < camera.image_width; ++x)
		{
			Ray ray = camera.makeRay(x, y);
			i = (y * camera.image_width + x) * 3;
			Vec3f color = castRay(ray, 0);
			
			image[i++] = clamp(color.x);
			image[i++] = clamp(color.y);
			image[i++] = clamp(color.z);
		}
	}

	write_ppm(camera.image_name.c_str(), image, camera.image_width, camera.image_height);
}

Intersection parser::Scene::getIntersection(Ray &ray)
{
	Intersection intersection(ray);
	for (auto it = triangles.begin(); it != triangles.end(); it++)
	{
		it->intersect(intersection, vertex_data);
	}

	for (auto it = spheres.begin(); it != spheres.end(); it++)
	{
		it->intersect(intersection, vertex_data);
	}

	for (auto it = meshes.begin(); it != meshes.end(); it++)
	{
		Mesh mesh = (*it);

		for (auto it2 = mesh.faces.begin(); it2 != mesh.faces.end(); it2++)
		{
			Triangle triangle;
			triangle.material_id = mesh.material_id;
			triangle.indices = (*it2);

			triangle.intersect(intersection, vertex_data);

		}

	}

	return intersection;
}

Vec3f parser::Scene::castRay(Ray& ray, int level)
{
	Intersection intersection = getIntersection(ray);

	if (intersection.intersected())
	{
		return lightItUp(intersection, level);
	}

	return Vec3f(background_color.x, background_color.y, background_color.z);
}

Vec3f parser::Scene::lightItUp(Intersection& intersection, int level)
{
	//TODO add reflections here
	Vec3f mirror_intensity(0);

	Vec3f ambient_intensity = ambient_light*materials[intersection.material_id].ambient;
	Vec3f diffuse_specular_intensity = getDiffuseSpecular(intersection);

	Vec3f mirror_effect = materials[intersection.material_id].mirror;
	if(level < max_recursion_depth && (mirror_effect.x > 0 || mirror_effect.y > 0 || mirror_effect.z > 0) )
	{
		Vec3f normalized_direction = intersection.ray.direction.normalized();
		Vec3f w_r = (normalized_direction + 
					intersection.surfaceNormal * 2 * intersection.surfaceNormal.dot(-normalized_direction)).normalized();
		Ray mirror_ray(intersection.hitPoint(), w_r);
		mirror_intensity = mirror_effect * castRay(mirror_ray, level+1);
	}

	return ambient_intensity + diffuse_specular_intensity + mirror_intensity;
}

Vec3f parser::Scene::getDiffuseSpecular(Intersection& intersection)
{
	Vec3f diffuseColor(0), specularColor(0);
	Point intersection_point = intersection.hitPoint();

	for (auto it = point_lights.begin(); it != point_lights.end(); it++)
	{
		PointLight light = *it;
		Vec3f light_vector = light.position - intersection_point;
		Vec3f light_direction = light_vector.normalized();
		Vec3f half_vector = (light_direction - intersection.ray.direction).normalized();
		float light_distance = light_vector.length();

		bool is_facing_light = intersection.surfaceNormal.dot(light_direction) >= 0.0f;
		if (is_facing_light)
		{
			Point shadow_ray_origin = intersection_point + (light_direction * shadow_ray_epsilon);
			Ray shadow_ray(shadow_ray_origin, light_direction);
			Intersection shadow_intersection = getIntersection(shadow_ray);
			// If in shadow, calculate other lights
			if (shadow_intersection.intersected())
			{
				float shadow_distance = (shadow_intersection.hitPoint() - shadow_ray_origin).length();
				if(shadow_distance < light_distance - shadow_ray_epsilon)
					continue;
			}
			float cosine = max(0.0f, light_direction.dot(intersection.surfaceNormal));

			diffuseColor += materials[intersection.material_id].diffuse * cosine * (light.intensity / light_vector.sqrLength()); //TODO: light_vector.sqrLength() or light_distance^2 ??
			
			cosine = max(0.0f, half_vector.dot(intersection.surfaceNormal));
			specularColor += materials[intersection.material_id].specular * pow(cosine, materials[intersection.material_id].phong_exponent) * (light.intensity / light_vector.sqrLength());
		}

	}
	return diffuseColor + specularColor;
}