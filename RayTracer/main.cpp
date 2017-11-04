#include <iostream>
#include "parser.h"
#include <vector>
#include "ppm.h"

typedef unsigned char RGB[3];

int main(int argc, char* argv[])
{
	parser::Scene scene;

	scene.loadFromXml(argv[1]);

	cout << "Add recursion limit to \"Ray\"s:Ray.h\n" <<
		"Add reflections:parser.h\n"<<
		"ALPEREN TODO: Shape.h\n"<< endl;

	for(auto it = scene.cameras.begin(); it != scene.cameras.end(); it++)
	{
		scene.Render(*it);
	}

}
