//===================================================
//  COSC363 Computer Graphics (2021)
//  File Name: GLM_Examples.cpp
//
//  This program provides a brief introduction to the usage of 
//  GLM types, operations and functions
//
//  COSC363 slides: GLM.pdf  (Lab 06)
//  GLM Homepage:  https://glm.g-truc.net/0.9.9/
//  GLM API Documentation:  https://glm.g-truc.net/0.9.9/api/modules.html
//====================================================


#include <iostream>
//======== GLM include statements ===========
#define GLM_FORCE_SWIZZLE			//Required if any swizzle operation is used
// #define GLM_ENABLE_EXPERIMENTAL // uncomment this if you get errors from use of experimental features (which can happen with old versions of GLM).
#include <climits>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace std;

int main()
{
	//vec4  is a 4-component vector that could be specified in two ways:
	glm::vec4  u1;						//Declaration followed by
	u1 = glm::vec4(3, 0,  4, 1);		//assignment
										//or
	glm::vec4   u2(-2, 7, 0.5, 1);		//Declaration and initialization

	//Vector operations
	glm::vec4 v1, v2, v3, v4;
	glm::vec3 w1, w2, w3, w4;
	float val1, val2, val3;
	v1 = u1 * u2;						//Elementwise product	(-6, 0, 2, 1)
	v2 = u1 + u2;						//Vector addition		(1, 7, 4.5, 2)
	v3 = 10.0f * u2;					//Scalar multiplication.  NOTE: The scalar must be of type float. (-20, 70, 5, 10)
	w1 = u1.xyz();						//Swizzle operator  (3, 0, 4)
	w2 = u2.wxx();						//Swizzle operator  (1, -2, -2)
	v4 = glm::vec4(w2, 1);				//Vector concatenation (1, -2, -2, 1)

	//Use the following functions on variables of type vec3 only
	val1 = glm::dot(w1, w2);			//Vector dot product    -5
	w3 = glm::cross(w1, w2);			//Vector cross product (8, 10, -6)
	w4 = glm::normalize(w1);			//Unit vector	(0.6, 0, 0.8)
	val2 = glm::length(w1);				//Magnitude   5
	val3 = glm::length(w4);				//Magnitude   1

	//Printing vector components
	cout << "v1 = " << glm::to_string(v1) << endl;

    //Example: Computing normal vector of a triangle with vertices ptA, ptB, ptC
	glm::vec3  ptA(1, 0, 1);
	glm::vec3  ptB(5, 2, 3);
	glm::vec3  ptC(5, 4, 0);
	glm::vec3  norm;
	norm = glm::cross(ptB - ptA, ptC - ptA);
	norm = glm::normalize(norm);

	//3x3 Matrices
	glm::mat3 m1;				//Declaration followed by
	m1 = glm::mat3(1);			//assignment.  m1 is an identity matrix.
								//or
	glm::mat3 m2(0);			//Declaration and initialization.  m2 is a null matrix

	//Creating a matrix using values of its elements
	glm::mat3 m3(5, 2, 1, 0, -1, 3, 6, 0, -2);	//The elements are stored in column-major order

	//Creating a matrix using vectors
	glm::mat3 m4(w1, w2, w3);					//w1 is the first column vector of the matrix.

	//Matrix-vector multiplication
	//A vec3 object should be treated as a 3x1 column vector.  A vec4 object is a 4x1 vector
	//A  mat3 object can be post-multiplied by a vec3 object to yield a vec3 result
	glm::vec3 w5, w6, w7, w8;
	w5 = m3 * w1;		//here w1 = (3, 0, 4).  w5 = (39, 6, -5). Please verify!

	//Extracting a column of a matrix
	w6 = glm::column(m3, 2);		//Column of m3 with index 2. Third column   (6, 0, -2)
	w7 = m3[2];						//Same as above.  (6, 0, -2)

	//Extracting a row of a matrix
	w8 = glm::row(m3, 0);			//First row of m3    (5, 0, 6)

	//Extracting  elements of a matrix [col][row]
	float a = m3[0][2];		//Element on first column, third row:  1
							//Elements of the first column are given by m3[0][0], m3[0][1], m3[0][2].

	//Determinant, Inverse
	glm::mat3 m5, m6;
	m5 = glm::inverse(m3);			//Inverse
	m6 = glm::transpose(m3);		//Transpose
	float d = glm::determinant(m3);	//Determinant

	//Printing a matrix
	cout << "m3 = " << glm::to_string(m3) << endl;  //First column, then second column and so on.

	//4x4 Matrices  (Similar functions and operations as 3x3 matrices)
	glm::mat4 idMat(1);		//Identity matrix
	glm::mat4 zeroMat(0);	//Null matrix

	//Matrix-vector product
	glm::mat4 m(3, 1, 0, 0, -1, 2, 1, 0, 0, 3, 2, 0, -3, 1, -1, 1);
	glm::vec4 v(2, 5, 3, 1);
	glm::vec4 w = m * v;	//Transformed vector (-2, 22, 10, 1). See GLM.pdf

	//Matrix-Matrix product
	glm::mat4 m7 = glm::transpose(m);
	glm::mat4 m8 = m * m7;			//Matrix product AB in the given order

	return 0;
}
