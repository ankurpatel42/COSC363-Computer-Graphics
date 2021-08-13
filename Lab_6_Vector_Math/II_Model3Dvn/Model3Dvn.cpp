//  ========================================================================
//  COSC363: Computer Graphics (2021);  University of Canterbury.
//
//  FILE NAME: Model3Dvn.cpp
//  See Lab06.pdf for details
//  ========================================================================

#include <iostream>
#include <fstream>
#include <cmath>
#include <GL/freeglut.h>
#include <climits>
using namespace std;

//--Globals ---------------------------------------------------------------
float *x, *y, *z;               //vertex coordinates
float *fnx, *fny, *fnz;         //face normal components
float *vnx, *vny, *vnz;         //vertex normal components
int *t1, *t2, *t3;              //vertex indices of each face
int nvert, nface;               //total number of vertices and faces
float angle = 0;                //Rotation angle

//-- Loads mesh data in OFF format    -------------------------------------
void loadMeshFile(const char* fname)
{
    ifstream fp_in;
    int ne, nv;

    fp_in.open(fname, ios::in);
    if(!fp_in.is_open())
    {
        cout << "Error opening mesh file" << endl;
        exit(1);
    }

    fp_in.ignore(INT_MAX, '\n');                //ignore first line
    fp_in >> nvert >> nface >> ne;              // read number of vertices, polygons, edges (not used)

    //create arrays
    x = new float[nvert];       //vertices
    y = new float[nvert];
    z = new float[nvert];

    t1 = new int[nface];        //face indices
    t2 = new int[nface];
    t3 = new int[nface];

    fnx = new float[nface];     //face normals
    fny = new float[nface];
    fnz = new float[nface];

    vnx = new float[nvert];     //vertex normals
    vny = new float[nvert];
    vnz = new float[nvert];

    for(int i=0; i < nvert; i++)                         //read vertex list
        fp_in >> x[i] >> y[i] >> z[i];

    for(int i=0; i < nface; i++)                         //read polygon list
    {
        fp_in >> nv >> t1[i] >> t2[i] >> t3[i];
    }

    fp_in.close();
    cout << " File successfully read." << endl;
}

//--Function to compute the normal vector of a triangle with index indx ----------
void normal(int indx)
{
    float x1 = x[t1[indx]], y1 = y[t1[indx]], z1 = z[t1[indx]];     //P
    float x2 = x[t2[indx]], y2 = y[t2[indx]], z2 = z[t2[indx]];     //Q
    float x3 = x[t3[indx]], y3 = y[t3[indx]], z3 = z[t3[indx]];     //R
    float nx, ny, nz;
    nx = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);          //See slides [6]-8,9
    ny = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
    nz = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
    fnx[indx] = nx;     //Components of a face normal vector
    fny[indx] = ny;
    fnz[indx] = nz;

    //normalize
    float nx_normalized = nx / sqrt((nx * nx) + (ny * ny) + (nz * nz));
    float ny_normalized = nz / sqrt((nx * nx) + (ny * ny) + (nz * nz));
    float nz_normalized = ny / sqrt((nx * nx) + (ny * ny) + (nz * nz));

    vnx[t1[indx]] = float (nx_normalized + ny_normalized + nz_normalized);
    vny[t2[indx]] = float (nx_normalized + ny_normalized + nz_normalized);
    vnz[t3[indx]] = float (nx_normalized + ny_normalized + nz_normalized);

}

//--Display: -------------------------------
void display()
{
    float lpos[4] = {10., 10., 10., 1.0};           //light's position

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //GL_LINE = Wireframe;   GL_FILL = Solid
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 1, 20, 0, 0, 0, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);    //set light position

    glRotatef(angle, 0.0, 1.0, 0.0);            //rotate the object about the y-axis

    glColor3f(1, 0.5, 0);

    glBegin(GL_TRIANGLES);
    for(int indx = 0; indx < nface; indx++)     //draw each face
    {
        //glNormal3f(fnx[indx], fny[indx], fnz[indx]);    //One normal vector per face (Cows polygons more visible)
        //glVertex3d(x[t1[indx]], y[t1[indx]], z[t1[indx]]);
        //glVertex3d(x[t2[indx]], y[t2[indx]], z[t2[indx]]);
        //glVertex3d(x[t3[indx]], y[t3[indx]], z[t3[indx]]);

        glNormal3f(vnx[t1[indx]], vny[t1[indx]], vnz[t1[indx]]);
        glVertex3d(x[t1[indx]], y[t1[indx]], z[t1[indx]]);
        glNormal3f(vnx[t2[indx]], vny[t2[indx]], vnz[t2[indx]]);
        glVertex3d(x[t2[indx]], y[t2[indx]], z[t2[indx]]);
        glNormal3f(vnx[t3[indx]], vny[t3[indx]], vnz[t3[indx]]);
        glVertex3d(x[t3[indx]], y[t3[indx]], z[t3[indx]]);
    }
    glEnd();

    glFlush();
}

//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
    loadMeshFile("Cow.off");            //Specify mesh file name here
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   //Background colour

    glEnable(GL_LIGHTING);                  //Enable OpenGL states
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    for (int i = 0; i < nvert; i++)
    {
        vnx[i] = 0;
        vny[i] = 0;
        vnz[i] = 0;
    }


    for (int indx = 0; indx < nface; indx++)    //pre-compute normal vectors
    {
        normal(indx);
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2., 2., -1, 3, 10, 1000);  //The camera view volume
}

//------------ Special key event callback ---------------------------------
// To enable the use of left and right arrow keys to rotate the scene
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT) angle--;
    else if(key == GLUT_KEY_RIGHT) angle++;

    glutPostRedisplay();
}

//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH);
   glutInitWindowSize (600, 600);
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("Model3D");
   initialize();

   glutDisplayFunc(display);
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}
