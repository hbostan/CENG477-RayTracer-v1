#include <iostream>
#include "parser.h"
#include <vector>
#include "ppm.h"

int main(int argc, char* argv[])
{
	parser::Scene scene;

	scene.loadFromXml(argv[1]);

	for(auto it = scene.cameras.begin(); it != scene.cameras.end(); it++)
	{
		scene.Render(*it);
	}

}
