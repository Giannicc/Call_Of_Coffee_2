/*
Created by Gianni Ciccarelli
This program creates a Model class object by reading and storing the
data found in the .obj file specified in the constructor parameter.

Call <this>.drawNonTextured(colorArray) to draw the model with OpenGL
function calls for a Polygon using the color specified as a parameter

Texture support to come when I find a good (and not outdated) openGL
texture tutorial
*/
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <glut/GLUT.H>
using namespace std;

/*
A Face object stores its vertices, normals, and texture coordinates as
integer indices corresponding to the actual data stored in vectors in the
Model class
*/
class Face {
public:
	vector<int> faceVertexNums, faceNormNums, faceTexNums;
};

class Model {
public:
	/*
	Construct a Model object using the data provided in the .obj file passed
	as a string containing its full name, and the x/y/z coordinates
	of its pivot point
	*/
	Model(string objSource, 
		float _x, float _y, float _z,
		vector<string> children);
	/*
	Pass an array with 3 integers from 0 to 255 to specify the color in
	RGB order (colorArray[0] for red, [1] for blue, [2] for green)
	*/
	void drawNonTextured(int colorArray[3]);
	void doNorms(bool veracity);
	void rotateModel(float x, float y, float z);
	void moveModel(float x, float y, float z);
	string name;
	vector<string> childNames;
	vector<Model*> children;
	vector<Face> modelFaces;
	vector<vector<double>> modelVertices;
	vector<vector<double>> normVectors;
	vector<vector<double>> textureCoords;
	bool drawNormals;
	//pivotX, pivotY, and pivotZ store the position of the pivot point in the model
	//while x, y, and z store the corresponding offset for moving that part of the model specifically
	float pivotX, pivotY, pivotZ, x = 0, y = 0, z = 0, rotX, rotY, rotZ;
};