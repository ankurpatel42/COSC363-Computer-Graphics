//  ========================================================================
//  COSC363: Computer Graphics (2021)
//
//  FILE NAME: FlightPath.cpp
//  See Lab06.pdf for details.
//  ========================================================================

#include <iostream>
#include <fstream>
#include <cmath>
#include <GL/freeglut.h>
using namespace std;

float angle = -40;      //Scene rotation angle
const int NPTS = 70;    //Number of points on the flight path
int option = 1;         //1: model view, 2: room view
float ptx[NPTS], pty[NPTS], ptz[NPTS];
GLUquadric *q;
int indx = 0;

void timer(int value) {
    if (value < 10000) {
        if (indx == NPTS) {
            indx = 0;
            glutPostRedisplay();
            glutTimerFunc(65, timer, value);
        }
        else {
            indx++;
            glutPostRedisplay();
            glutTimerFunc(65, timer, value);
        }
    }
}

//Reads flight path data from FlightPath.txt
void loadFlightPath()
{
    ifstream ifile;
    ifile.open("FlightPath.txt");
    if (!ifile){
        std::cout << "File not found!" << std::endl;
        throw;
    }
    for (int i = 0; i < NPTS; i++)
        ifile >> ptx[i] >> pty[i] >> ptz[i];

    ifile.close();
}


void drawFin()
{
    glColor3f(1, 0, 0);
    glNormal3f(0, 0, 1);
    glBegin(GL_TRIANGLES);
      glVertex3f(-1, 0.5, 0);
      glVertex3f(2, 0.5, 0);
      glVertex3f(-1, 4, 0);
    glEnd();
}

void drawModel()
{
    glColor3f(0, 1, 1);
    glPushMatrix();  //body
      glRotatef(90, 0, 1, 0);
      gluCylinder(q, 1, 1, 7, 36, 5);
      gluDisk(q, 0, 1, 36, 3);
    glPopMatrix();

    glColor3f(0, 0, 1);
    glPushMatrix();  //nose
      glTranslatef(7, 0, 0);
      glRotatef(90, 0, 1, 0);
      glutSolidCone(1, 2, 36, 3);
    glPopMatrix();

    for (int i = 0; i < 3; i++)  //3 fins
    {
        glPushMatrix();
          glRotatef(120 * i, 1, 0, 0);
          drawFin();
        glPopMatrix();
    }
}

void drawRoom()
{
    glDisable(GL_LIGHTING);
    glColor3f(0.7, 0.7,  0.7);          //Floor colour
    for(int i = -100; i <= 100; i +=5)
    {
        glBegin(GL_LINES);          //A set of grid lines on the floor-plane
            glVertex3f(-100, 0, i);
            glVertex3f(100, 0, i);
            glVertex3f(i, 0, -100);
            glVertex3f(i, 0, 100);
        glEnd();
    }

    glEnable(GL_LIGHTING);
    glBegin(GL_QUADS);          //4 walls
      glColor3f(0.75, 0.75, 0.75);
      glNormal3f(0, 0, 1);
      glVertex3f(-100, 0, -100);
      glVertex3f(100, 0, -100);
      glVertex3f(100, 140, -100);
      glVertex3f(-100, 140, -100);

      glNormal3f(0, 0, -1);
      glVertex3f(-100, 0, 100);
      glVertex3f(100, 0, 100);
      glVertex3f(100, 140, 100);
      glVertex3f(-100, 140, 100);

      glColor3f(1, 0.75, 0.75);
      glNormal3f(1, 0, 0);
      glVertex3f(-100, 0, -100);
      glVertex3f(-100, 140, -100);
      glVertex3f(-100, 140, 100);
      glVertex3f(-100, 0, 100);

      glNormal3f(-1, 0, 0);
      glVertex3f(100, 0, -100);
      glVertex3f(100, 140, -100);
      glVertex3f(100, 140, 100);
      glVertex3f(100, 0, 100);

      glColor3f(1, 1, 0.6);
      glNormal3f(0, -1, 0);
      glVertex3f(-100, 140, 100);
      glVertex3f(100, 140, 100);
      glVertex3f(100, 140, -100);
      glVertex3f(-100, 140, -100);
    glEnd();

}

void drawFlightPath()
{
    glColor3f(0.0, 0.0, 1.0);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < NPTS; i++)
        glVertex3f(ptx[i], pty[i], ptz[i]);
    glEnd();
    glEnable(GL_LIGHTING);
}

//---------------------------------------------
void initialise(void)
{
    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};
    float black[4] = { 0, 0, 0, 1 };
    q = gluNewQuadric();

    loadFlightPath();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glEnable(GL_SMOOTH);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
    glClearColor (1.0, 1.0, 1.0, 0.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(80.0, 1.0, 10.0, 500.0);
}


//------------------------------------------
void display(void)
{
    float lgt_pos[]={0, 50.0f, 0.0f, 1.0f};  //light0 position (above the origin)

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (option == 2)
       gluLookAt(0., 10, 30.0, 0., 0., 0., 0., 1., 0.);
    else
        gluLookAt(0., 80, 100.0, 0., 50., 0., 0., 1., 0.);


    glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);   //light position

    glRotatef(angle, 0, 1, 0);

    //points from vector P
    float currentPointOnPath_x = ptx[indx];
    float currentPointOnPath_y = pty[indx];
    float currentPointOnPath_z = ptz[indx];

    //points from vector q
    float nextPointOnPath_x = ptx[indx+1];
    float nextPointOnPath_y = pty[indx+1];
    float nextPointOnPath_z = ptz[indx+1];

    //vector v (q - p)
    float v[] = {nextPointOnPath_x - currentPointOnPath_x, nextPointOnPath_y - currentPointOnPath_y, nextPointOnPath_z - currentPointOnPath_z};

    //--------------------------normalize v-----------------------------
    float length_v = 0;

    for(int i = 0; i < 3; i++) {
        length_v += (pow(v[i], 2));
    }

    length_v = pow(length_v, 0.5);

    for(int i = 0; i < 3; i++) {
        v[i] = v[i] / length_v; //vector v now normalized
    }

    //------------------------------------------------------------------
    float u[] = {1.0, 0.0, 0.0};

    float dot_product_u_and_v = 0;

    for (int i = 0; i < 3; i++) {
        dot_product_u_and_v += (u[i] * v[i]);
    }

    float theta = acos(dot_product_u_and_v) * 180.0 / M_PI;

    float w[] = {(u[1] * v[2]) - (u[2] * v[1]), (u[2] * v[0]) - (u[0] * v[2]), (u[0] * v[1]) - (u[1] * v[0])}; //cross product (w = axis of rotation)



    drawRoom();
    drawFlightPath();

    glPushMatrix();
        glTranslatef(currentPointOnPath_x, currentPointOnPath_y, currentPointOnPath_z);
        glRotatef(theta, w[0], w[1], w[2]);
        drawModel();
    glPopMatrix();

    glutSwapBuffers();
}



//  Keyboard call-back function
void keyboard(unsigned char key, int x, int y)
{
    if (key == '1') option = 1;
    else if (key == '2') option = 2;
    glutPostRedisplay();
}


//  Special keyboard call-back function
void special(int key, int x, int y)
{
    if(key==GLUT_KEY_LEFT) angle--;
    else if(key==GLUT_KEY_RIGHT) angle++;
    glutPostRedisplay();
}

//----------------------------------------------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize (700, 700);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Flight");
   initialise ();
   glutTimerFunc(50, timer, 0);
   glutDisplayFunc(display);
   glutSpecialFunc(special);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
