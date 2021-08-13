//  ========================================================================
//  COSC363: Computer Graphics;  University of Canterbury (2020)
//
//  FILE NAME: Seashell.cpp
//
//	The program  loads the mesh data for the model of a seashell.
//  The vertex shader includes code for both transformations and lighting.
//  Required files: Shader.h, Seashell.vert, Seashell.frag
//  See Lab09.pdf for details.
//  ========================================================================


#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

using namespace std;

//------Globals---------
GLuint mvpMatrixLoc, mvMatrixLoc, norMatrixLoc, lgtLoc;
GLuint vaoID;

float angle = 0;
const float CDR = 3.14159265/180.0;		//Conversion from degrees to radians
glm::mat4 viewMatrix, projMatrix;		//View and projection matrices
int ntri;								//Number of triangles in the model's definition
//---------------------

//  Loads vertex and normal information from a model definition file
//  and creates VBOs  using them.
void loadData()
{
	int nverts;					
	ifstream ifile("Seashell.dat");
	ifile >> nverts >> ntri;		//Read number of vertices and number of triangles

	float *verts = new float[nverts * 3];				//3 coords per vertex
	float *normals = new float[nverts * 3];				//3 coords per normal
	unsigned int *elems = new unsigned int[ntri * 3];	//3 elements per primitive

	//Read vertex coordinates
	for (int i = 0; i < nverts; i++)
		ifile >> verts[i * 3] >> verts[i * 3 + 1] >> verts[i * 3 + 2];

	//Read vertex normal components
	for (int i = 0; i < nverts; i++)
		ifile >> normals[i * 3] >> normals[i * 3 + 1] >> normals[i * 3 + 2];

	//vertex indices
	for (int i = 0; i < ntri; i++)
		ifile >> elems[i * 3] >> elems[i * 3 + 1] >> elems[i * 3 + 2];

	ifile.close();

	glGenVertexArrays(1, &vaoID);		//First, create a VAO and bind it
	glBindVertexArray(vaoID);

	GLuint vboID[3];
	glGenBuffers(3, vboID);				//Create 3 VBOs as part of the above VAO

	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);	//A VBO for vertex positions
	glBufferData(GL_ARRAY_BUFFER, (nverts * 3) * sizeof(float), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);	//A VBO for vertex normals
	glBufferData(GL_ARRAY_BUFFER, (nverts * 3) * sizeof(float), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[2]);	//A VBO for vertex indices
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (ntri * 3) * sizeof(unsigned int), elems, GL_STATIC_DRAW);

	delete[] verts;
	delete[] normals;
	delete[] elems;

	glBindVertexArray(0);

}


void initialize()
{
	glm::vec4 light = glm::vec4(-20.0, 5.0, 0, 1.0);      //Light's position in world coordinates
	GLuint program = createShaderProg("Seashell.vert", "Seashell.frag");

	mvMatrixLoc = glGetUniformLocation(program, "mvMatrix");  //Get locations of uniform variables declared in shader
	mvpMatrixLoc = glGetUniformLocation(program, "mvpMatrix");
	norMatrixLoc = glGetUniformLocation(program, "norMatrix");
	lgtLoc = glGetUniformLocation(program, "lightPos");
  
	projMatrix = glm::perspective(40.0f*CDR, 1.0f, 1.0f, 10.0f);
	viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));    

	glm::vec4 lightEye = viewMatrix * light;	//Light's position in eye coordinates
	glUniform4fv(lgtLoc, 1, &lightEye[0]);		//Pass this value to the shader
	
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	loadData();
}


void update(int value)
{
	angle++;
	glutTimerFunc(50.0, update, 0);
	glutPostRedisplay();
}


void display()
{
	glm::mat4 identity = glm::mat4(1.0f);  //Identity matrix
	glm::mat4 rotationMatrix = glm::rotate(identity, angle*CDR, glm::vec3(1.0f, 0.0f, 0.0f));  //rotation matrix
	glm::mat4 mvMatrix = viewMatrix * rotationMatrix;  //The model-view matrix
	glm::mat4 mvpMatrix = projMatrix * mvMatrix; //The model-view-projection matrix

	glm::mat4 invMatrix = glm::inverse(mvMatrix);  //Inverse of model-view matrix for normal transformation
	glUniformMatrix4fv(mvMatrixLoc, 1, GL_FALSE, &mvMatrix[0][0]);
	glUniformMatrix4fv(mvpMatrixLoc, 1, GL_FALSE, &mvpMatrix[0][0]);
	glUniformMatrix4fv(norMatrixLoc, 1, GL_TRUE, &invMatrix[0][0]);  //Use transpose matrix here

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vaoID);
	glDrawElements(GL_TRIANGLES, ntri * 3, GL_UNSIGNED_INT, NULL);

	glFlush();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("A Seashell");
	glutInitContextVersion (4, 1);
	glutInitContextProfile ( GLUT_CORE_PROFILE );

	if(glewInit() == GLEW_OK)
	{
		cout << "GLEW initialization successful! " << endl;
		cout << " Using GLEW version " << glewGetString(GLEW_VERSION) << endl;
	}
	else
	{
		cerr << "Unable to initialize GLEW  ...exiting." << endl;
		exit(EXIT_FAILURE);
	}

	initialize();
	glutDisplayFunc(display);
	glutTimerFunc(50, update, 0); 
	glutMainLoop();
}

