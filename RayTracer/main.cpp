#include <iostream>
#include "parser.h"
#include <vector>
#include "ppm.h"

typedef unsigned char RGB[3];

int main(int argc, char* argv[])
{
	// Sample usage for reading an XML scene file
	parser::Scene scene;

	scene.loadFromXml(argv[1]);

	// The code below creates a test pattern and writes
	// it to a PPM file to demonstrate the usage of the
	// ppm_write function.

	const RGB BAR_COLOR[8] =
	{
		{ 255, 255, 255 },  // 100% White
		{ 255, 255,   0 },  // Yellow
		{ 0, 255, 255 },  // Cyan
		{ 0, 255,   0 },  // Green
		{ 255,   0, 255 },  // Magenta
		{ 255,   0,   0 },  // Red
		{ 0,   0, 255 },  // Blue
		{ 0,   0,   0 },  // Black
	};

	int width = 640, height = 480;
	int columnWidth = width / 8;

	cout << "Add recursion limit to \"Ray\"s:Ray.h\n" <<
		"Add reflections:parser.h\n"<<
		"Fix Infinity: Intersection.h\n"<<
		"ALPEREN TODO: Shape.h\n"<<
		"Iterate over cameras:parser.h/main.cpp\n" << endl;

	scene.Render(scene.cameras[0]);

}
