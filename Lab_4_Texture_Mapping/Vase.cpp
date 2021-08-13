//  ========================================================================
//  COSC363: Computer Graphics (2020);  University of Canterbury.
//
//  FILE NAME: Vase.cpp
//  See Lab03 (II) for details
//  ========================================================================

#include <iostream>
#include <cmath>
#include <GL/freeglut.h>

using namespace std;


const int N = 50;  // Total number of vertices on the base curve

float vx_init[N] = { 0, 8, 8, 7.5, 6.7, 5, 5.5, 4, 4, 5, 5.6, 6.1, 6.8, 7.1, 7.5, 8, 8.4, 8.7, 9, 9.3,
                      9.8, 10, 10.2, 10.4, 10.6, 10.9, 11, 11.1, 11.2, 11.3, 11.4, 11.3, 11.2, 11.1, 11, 10.5, 9.5, 8.2, 7, 6.2,
                      6, 6.2, 6.8, 7.6, 8.5, 7, 6.1, 5.3, 4.7, 4.5 };
float vy_init[N] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
                      19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
                      39, 40, 41, 42, 43, 43, 42, 41, 40, 39 };
float vz_init[N] = { 0 };

float angle = 25, cam_hgt = 50.0;  //Rotation angle, camera height


//-- Ground Plane --------------------------------------------------------
void drawFloor()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.7, 0.7,  0.7);          //Floor colour

    for(int i = -200; i <= 200; i +=5)
    {
        glBegin(GL_LINES);          //A set of grid lines on the xz-plane
            glVertex3f(-200, 0, i);
            glVertex3f(200, 0, i);
            glVertex3f(i, 0, -200);
            glVertex3f(i, 0, 200);
        glEnd();
    }
    glEnable(GL_LIGHTING);
}

//-------------------------------------------------------------------
void initialise(void)
{
    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};
    float mat[4] = { 1.0, 0.75, 0.5, 1.0 };

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glEnable(GL_SMOOTH);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);

    glClearColor (1.0, 1.0, 1.0, 0.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(40.0, 1.0, 20.0, 500.0);
}
//-------------------------------------------------------------------

void normal(float x1, float y1, float z1,
            float x2, float y2, float z2,
              float x3, float y3, float z3 )
{
      float nx, ny, nz;
      nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
      ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
      nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);

      glNormal3f(nx, ny, nz);
}

//-------------------------------------------------------------------
void display(void)
{
    float vx[N], vy[N], vz[N];
    float wx[N], wy[N], wz[N];
    float lgt_pos[]={5.0f, 50.0f, 100.0f, 1.0f};  //light0 position

    for (int i = 0; i < N; i++)     //Initialize data everytime
    {
        vx[i] = vx_init[i];
        vy[i] = vy_init[i];
        vz[i] = vz_init[i];
    }

    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0., cam_hgt, 100.0, 0., 20., 0., 0., 1., 0.);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glRotatef(angle, 0, 1, 0);      //Rotate the entire scene

    glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);   //light position

    drawFloor();

    glColor3f (0.0, 0.0, 1.0);    //Used for wireframe display
    glEnable(GL_LIGHTING);

    //  Include code for drawing the surface of revolution here.
    // ---- Start here ----


    for (int j = 0; j < 36; j++)
    {
         for(int i = 0; i < N; i++)
         {
            wx[i] = vx[i] * cos(angle * (M_PI / 180)) + (vz[i] * sin(angle * (M_PI / 180)));
            wy[i] = vy[i];
            wz[i] = -vx[i] * sin(angle * (M_PI / 180)) + (vz[i] * cos(angle * (M_PI / 180)));
        }

        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < N; i++) {
            if (i > 0) normal(vx[i-1], vy[i-1], vz[i-1],
                              wx[i-1], wy[i-1], wz[i-1],
                              vx[i], vy[i], vz[i]);
            glVertex3f(vx[i], vy[i], vz[i]);
            if (i > 0) normal(wx[i-1], wy[i-1], wz[i-1],
                              wx[i], wy[i], wz[i],
                              vx[i], vy[i], vz[i]);
            glVertex3f(wx[i], wy[i], wz[i]);
        }
        glEnd();

        for(int i = 0; i < N; i++)
         {
            vx[i] = wx[i];
            vy[i] = wy[i];
            vz[i] = wz[i];
        }


    }


    glFlush();
}

//--------------------------------------------------------------------------------
void special(int key, int x, int y)
{
    if(key==GLUT_KEY_LEFT) angle --;        //Rotate wagon
    else if(key==GLUT_KEY_RIGHT) angle ++;
    else if(key==GLUT_KEY_UP) cam_hgt ++;   //Change camera height
    else if(key==GLUT_KEY_DOWN) cam_hgt --;

    if(cam_hgt < 10) cam_hgt = 10;
    else if(cam_hgt > 100) cam_hgt = 100;

    glutPostRedisplay();
}

//-------------------------------------------------------------------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE| GLUT_DEPTH);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Vase");
   initialise ();
   glutDisplayFunc(display);
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}
