//  ========================================================================
//  COSC363: Computer Graphics (2021);  University of Canterbury.
//
//  FILE NAME: Assignment 1 - Ankur Patel
//
//  ========================================================================

#include <iostream>
#include <fstream>
#include <cmath>
#include <GL/freeglut.h>
#include "loadTGA.h"
#define GL_CLAMP_TO_EDGE 0x812F
using namespace std;

//--Globals ---------------------------------------------------------------
GLuint txId[9];

double theta_first_humanoid_right_leg = 10;
double theta_second_humanoid_right_leg = 10;
double sphere_x = -1;
double sphere_y = 1;
double sphere_z = 29;
int sphereState = 0;
int humanoidState = 0;

int ball_incrementing = 0;

float angle=0, look_x, look_z=-1., eye_x=17, eye_z= 20;  //Camera parameters

double angle_of_rotation = 0;
double angle_of_rotation_movement = 2.8;
double windmill_center_x = 0;
double windmill_center_y = 9.5;
double windmill_center_z = 14;

//----------------------------------------------------------------------
void myTimer(int value) {

    if (value < 10000) {

        if (sphere_z == 29.0) {
            sphereState = 1;
        }
        else if (sphere_z == 1.0) {
            sphereState = 0;
        }
        if (sphereState == 1) {
            angle_of_rotation += angle_of_rotation_movement;
            theta_first_humanoid_right_leg--;
            theta_second_humanoid_right_leg--;
            sphere_z--;
            glutPostRedisplay();
            value -= 0.5;
            glutTimerFunc(35, myTimer, value);
        }

        else if (sphereState == 0) {
            angle_of_rotation += angle_of_rotation_movement;
            theta_first_humanoid_right_leg++;
            theta_second_humanoid_right_leg++;
            sphere_z++;
            glutPostRedisplay();
            value += 0.5;
            glutTimerFunc(35, myTimer, value);
        }
    }

}
//----------------------------------------------------------------------

void loadTexture()
{
    glGenTextures(8, txId);

    //---------------------------Sky Box--------------------------------
    glBindTexture(GL_TEXTURE_2D, txId[2]);
    loadTGA("up.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, txId[3]);
    loadTGA("right.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, txId[4]);
    loadTGA("left.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, txId[5]);
    loadTGA("front.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, txId[6]);
    loadTGA("down.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, txId[7]);
    loadTGA("back.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    //------------------Floor texture-----------------------------------

    glBindTexture(GL_TEXTURE_2D, txId[0]);
    loadTGA("field.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);

    //--------------------Sphere texture--------------------------------

    glBindTexture(GL_TEXTURE_2D, txId[1]);
    loadTGA("blue_sphere.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);

    //---------------------Wall texture---------------------------------
    glBindTexture(GL_TEXTURE_2D, txId[8]);
    loadTGA("Wall.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);


}

//----------------------------------------------------------------------
void drawFloor()
{
     glBindTexture(GL_TEXTURE_2D, txId[0]);

     glBegin(GL_QUADS);
         glTexCoord2f(0, 0);    //order vertices in anti-clockwise direction
         glVertex3f(30, -1, 40);
         glTexCoord2f(64, 0);
         glVertex3f(30, -1, -20);
         glTexCoord2f(64, 64);
         glVertex3f(-30, -1, -20);
         glTexCoord2f(0, 64);
         glVertex3f(-30, -1, 40);


    glEnd();
}

void drawWalls()
{
    glBindTexture(GL_TEXTURE_2D, txId[8]);
    //Front Wall
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1);
        glVertex3f(30, 4, -20);
        glTexCoord2f(0, 0);
        glVertex3f(30, -1, -20);
        glTexCoord2f(20, 0);
        glVertex3f(-30, -1, -20);
        glTexCoord2f(20, 1);
        glVertex3f(-30, 4, -20);
    glEnd();

    //Left Wall
    glBegin(GL_QUADS);
        glTexCoord2f(20, 1);
        glVertex3f(-30, 4, 40);
        glTexCoord2f(20, 0);
        glVertex3f(-30, -1, 40);
        glTexCoord2f(0, 0);
        glVertex3f(-30, -1, -20);
        glTexCoord2f(0, 1);
        glVertex3f(-30, 4, -20);
    glEnd();

    //Right Wall
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1);
        glVertex3f(30, 4, 40);
        glTexCoord2f(0, 0);
        glVertex3f(30, -1, 40);
        glTexCoord2f(20, 0);
        glVertex3f(30, -1, -20);
        glTexCoord2f(20, 1);
        glVertex3f(30, 4, -20);
    glEnd();

    //Back Wall
    glBegin(GL_QUADS);
        glTexCoord2f(20, 1);
        glVertex3f(30, 4, 40);
        glTexCoord2f(20, 0);
        glVertex3f(30, -1, 40);
        glTexCoord2f(0, 0);
        glVertex3f(-30, -1, 40);
        glTexCoord2f(0, 1);
        glVertex3f(-30, 4, 40);
    glEnd();

}

void drawFrontSkyBox()
{
    glBindTexture(GL_TEXTURE_2D, txId[5]);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 1);
        glVertex3f(401.5, 301.5, -400);
        glTexCoord2f(0, 0);
        glVertex3f(401.5, -301.5, -400);
        glTexCoord2f(1, 0);
        glVertex3f(-401.5, -301.5, -400);
        glTexCoord2f(1, 1);
        glVertex3f(-401.5, 301.5, -400);

    glEnd();
}

void drawBackSkyBox()
{
    glBindTexture(GL_TEXTURE_2D, txId[7]);

    glBegin(GL_QUADS);
        glTexCoord2f(1, 1);
        glVertex3f(401.5, 301.5, 380);
        glTexCoord2f(1, 0);
        glVertex3f(401.5, -301.5, 380);
        glTexCoord2f(0, 0);
        glVertex3f(-401.5, -301.5, 380);
        glTexCoord2f(0, 1);
        glVertex3f(-401.5, 301.5, 380);

    glEnd();
}

void drawRightSkyBox()
{
    glBindTexture(GL_TEXTURE_2D, txId[3]);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 1);
        glVertex3f(400, 301.5, 381.5);
        glTexCoord2f(0, 0);
        glVertex3f(400, -301.5, 381.5);
        glTexCoord2f(1, 0);
        glVertex3f(400, -301.5, -401.5);
        glTexCoord2f(1, 1);
        glVertex3f(400, 301.5, -401.5);

    glEnd();
}

void drawLeftSkyBox()
{
    glBindTexture(GL_TEXTURE_2D, txId[4]);

    glBegin(GL_QUADS);
        glTexCoord2f(1, 1);
        glVertex3f(-400, 301.5, 381.5);
        glTexCoord2f(1, 0);
        glVertex3f(-400, -301.5, 381.5);
        glTexCoord2f(0, 0);
        glVertex3f(-400, -301.5, -401.5);
        glTexCoord2f(0, 1);
        glVertex3f(-400, 301.5, -401.5);

    glEnd();
}


void drawTopSkyBox()
{
    glBindTexture(GL_TEXTURE_2D, txId[2]);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(401.5, 300, 381.5);
        glTexCoord2f(1, 0);
        glVertex3f(401.5, 300, -401.5);
        glTexCoord2f(1, 1);
        glVertex3f(-401.5, 300, -401.5);
        glTexCoord2f(0, 1);
        glVertex3f(-401.5, 300, 381.5);

    glEnd();
}

//--Draws a character model constructed using GLUT objects -------------
void drawModel()
{
    //----------------------First Humanoid------------------------------
     //~ float shadowMat[16] = {100.0,0,0,0, 80.0,0,-85.0,
                            //~ -1, 0,0,100.0,0, 0,0,0,100.0};
    float shadowMat[16] = {100.0,0,0,0, 60.0,0,-100.0,
                            -1, 0,0,100.0,0, 0,0,0,100.0};
    glDisable(GL_LIGHTING);

    glPushMatrix(); //Shadow of Humanoid head
        glColor3f(0, 0, 0);
        glMultMatrixf(shadowMat);
        glTranslatef(0, 7.7, 0);
        glutSolidCube(1.4);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glColor3f(1., 0.78, 0.06);      //Head
    glPushMatrix();
      glTranslatef(0, 7.7, 0);
      glutSolidCube(1.4);
    glPopMatrix();

    glDisable(GL_LIGHTING);

    glPushMatrix();             //Shadow of Humanoid Torso
        glColor3f(0, 0, 0);
        glMultMatrixf(shadowMat);
        glTranslatef(0, 5.5, 0);
        glScalef(3, 3, 1.4);
        glutSolidCube(1);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glColor3f(1., 0., 0.);          //Torso
    glPushMatrix();
      glTranslatef(0, 5.5, 0);
      glScalef(3, 3, 1.4);
      glutSolidCube(1);
    glPopMatrix();

    glDisable(GL_LIGHTING);

    glPushMatrix();             //Right leg shadow
      glColor3f(0, 0, 0);
      glMultMatrixf(shadowMat);
      glTranslatef(-0.8, 4, 0);
      glRotatef(theta_first_humanoid_right_leg, 1, 0, 0);
      glTranslatef(0.8, -4, 0);
      glTranslatef(-0.8, 2.2, 0);
      glScalef(1, 4.4, 1);
      glutSolidCube(1);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glColor3f(0., 0., 1.);          //Right leg
    glPushMatrix();
      glTranslatef(-0.8, 4, 0);
      glRotatef(theta_first_humanoid_right_leg, 1, 0, 0);
      glTranslatef(0.8, -4, 0);
      glTranslatef(-0.8, 2.2, 0);
      glScalef(1, 4.4, 1);
      glutSolidCube(1);
    glPopMatrix();

    glDisable(GL_LIGHTING);

    glPushMatrix();             //Left leg shadow
      glColor3f(0, 0, 0);
      glMultMatrixf(shadowMat);
      glTranslatef(0.8, 4, 0);
      glTranslatef(-0.8, -4, 0);
      glTranslatef(0.8, 2.2, 0);
      glScalef(1, 4.4, 1);
      glutSolidCube(1);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glColor3f(0., 0., 1.);          //Left leg
    glPushMatrix();
      glTranslatef(0.8, 4, 0);
      glTranslatef(-0.8, -4, 0);
      glTranslatef(0.8, 2.2, 0);
      glScalef(1, 4.4, 1);
      glutSolidCube(1);
    glPopMatrix();

    glDisable(GL_LIGHTING);

    glPushMatrix();             //Right arm shadow
      glColor3f(0, 0, 0);
      glMultMatrixf(shadowMat);
      glTranslatef(-2, 6.5, 0);
      glTranslatef(2, -6.5, 0);
      glTranslatef(-2, 5, 0);
      glScalef(1, 4, 1);
      glutSolidCube(1);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glColor3f(0., 0., 1.);          //Right arm
    glPushMatrix();
      glTranslatef(-2, 6.5, 0);
      glTranslatef(2, -6.5, 0);
      glTranslatef(-2, 5, 0);
      glScalef(1, 4, 1);
      glutSolidCube(1);
    glPopMatrix();

    glDisable(GL_LIGHTING);

    glPushMatrix();             //Left arm shadow
      glColor3f(0, 0, 0);
      glMultMatrixf(shadowMat);
      glTranslatef(2, 6.5, 0);
      glTranslatef(-2, -6.5, 0);
      glTranslatef(2, 5, 0);
      glScalef(1, 4, 1);
      glutSolidCube(1);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glColor3f(0., 0., 1.);          //Left arm
    glPushMatrix();
      glTranslatef(2, 6.5, 0);
      glTranslatef(-2, -6.5, 0);
      glTranslatef(2, 5, 0);
      glScalef(1, 4, 1);
      glutSolidCube(1);
    glPopMatrix();

    //---------------------------Windmill-------------------------------
    glPushMatrix();
        glTranslatef(windmill_center_x, windmill_center_y, windmill_center_z);
        glRotatef(angle_of_rotation, 0, 0, 1);
        glTranslatef(-windmill_center_x, -windmill_center_y, -windmill_center_z);

        //Blade 3
        glColor3f(1, 0, 1);
        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0, 9.5, 12.9);
            glVertex3f(-7, 12, 12.9);
            glVertex3f(-7, 10.5, 12.9);
            glVertex3f(0, 9.5, 12.9);
        glEnd();
        //Blade 2
        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0, 9.5, 12.9);
            glVertex3f(7, 12, 12.9);
            glVertex3f(7, 10.5, 12.9);
            glVertex3f(0, 9.5, 12.9);
        glEnd();
        //Blade 1
        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0, 9.5, 12.9);
            glVertex3f(-0.8, 2, 12.9);
            glVertex3f(0.8, 2, 12.9);
            glVertex3f(0, 9.5, 12.9); //Closed fan
        glEnd();
    glPopMatrix();
    //--------------------Bridge overhead cube--------------------------
    glColor3f(0, 0, 1);
    glPushMatrix();
        glTranslatef(0, 8.8, 14);
        glutSolidCube(2.0);
    glPopMatrix();
    //-----------------------Bridge overhead----------------------------
    glColor3f(0, 0, 1);
    glPushMatrix();
        glTranslatef(12, 7, 0);
        glRotatef(90, 0, 0, 1);
        glScalef(1, 6, 1);
        glTranslatef(0, 2, 14);
        glutSolidCube(2.0);
    glPopMatrix();

    //------------------------Bridge leg right-------------------------
    glColor3f(0, 0, 1);
    glPushMatrix();
        glTranslatef(5, 0, 0);
        glScalef(1, 2, 1);
        glTranslatef(0, 2, 14);
        glutSolidCube(2.0);
    glPopMatrix();

    //---------------------Bridge leg left------------------------------
    glColor3f(0, 0, 1);
    glPushMatrix();
        glTranslatef(-5, 0, 0);
        glScalef(1, 2, 1);
        glTranslatef(0, 2, 14);
        glutSolidCube(2.0);
    glPopMatrix();

    //---------------------------Sphere---------------------------------
    glColor3d(0.6, 0.25, 0.25);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[1]);
    glPushMatrix();
        glTranslatef(sphere_x, sphere_y, sphere_z);
        GLUquadric *q;
        q = gluNewQuadric();
        gluQuadricTexture(q, GL_TRUE);
        gluSphere(q, 1, 50, 50);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //------------------------Second Humanoid---------------------------

    glColor3f(1., 0.78, 0.06);      //Head
    glPushMatrix();
      glTranslatef(0, 7.7, 30);
      glutSolidCube(1.4);
    glPopMatrix();

    glColor3f(1., 0., 0.);          //Torso
    glPushMatrix();
      glTranslatef(0, 5.5, 30);
      glScalef(3, 3, 1.4);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(0., 0., 1.);          //Right leg
    glPushMatrix();
      glTranslatef(-0.8, 4, 30);
      glRotatef(theta_second_humanoid_right_leg, 1, 0, 0);
      glTranslatef(0.8, -4, 0);
      glTranslatef(-0.8, 2.2, 0);
      glScalef(1, 4.4, 1);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(0., 0., 1.);          //Left leg
    glPushMatrix();
      glTranslatef(0.8, 4, 30);
      //glRotatef(theta_humanoid , 1, 0, 0);
      glTranslatef(-0.8, -4, 0);
      glTranslatef(0.8, 2.2, 0);
      glScalef(1, 4.4, 1);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(0., 0., 1.);          //Right arm
    glPushMatrix();
      glTranslatef(-2, 6.5, 30);
      //glRotatef(theta_humanoid , 1, 0, 0);
      glTranslatef(2, -6.5, 0);
      glTranslatef(-2, 5, 0);
      glScalef(1, 4, 1);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(0., 0., 1.);          //Left arm
    glPushMatrix();
      glTranslatef(2, 6.5, 30);
      //glRotatef(theta_humanoid , 1, 0, 0);
      glTranslatef(-2, -6.5, 0);
      glTranslatef(2, 5, 0);
      glScalef(1, 4, 1);
      glutSolidCube(1);
    glPopMatrix();
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
void drawCone()
{

    float angle = 25;

    glColor3f(1.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    const int N = 4;

    float vx[N] = {0, -1, -1, -1};
    float vy[N] = {10};
    float vz[N] = {0, -1, -2, -3};

    float wx[N];
    float wy[N];
    float wz[N];

    glPushMatrix();
        glTranslatef(-10, 18.2, 30);
        glRotatef(180, 1, 0, 0);
        glTranslatef(10, 0, 0);

        for (int j = 0; j < 36; j++)
        {
             for(int i = 0; i < N; i++)
             {
                wx[i] = vx[i] * cos(angle * (M_PI / 180)) + (vz[i] * sin(angle * (M_PI / 180))); //convert to degrees
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

    glPopMatrix();
}

//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()
{
    float lpos[4] = {10., 10., 10., 1.0};  //light's position

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye_x, 8, eye_z,  look_x, 0, look_z,   0, 1, 0);
    glLightfv(GL_LIGHT0,GL_POSITION, lpos);   //Set light position

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);         //Disable lighting when drawing floor.
    drawFloor();
    drawFrontSkyBox();
    drawLeftSkyBox();
    drawRightSkyBox();
    drawBackSkyBox();
    drawTopSkyBox();
    drawWalls();
    glDisable(GL_TEXTURE_2D); //disable texture to keep other object(s) color
    drawCone();

    glEnable(GL_LIGHTING);         //Enable lighting when drawing the model

    drawModel();

    glutSwapBuffers();
}

//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   //Background colour

    loadTexture();
    glEnable(GL_TEXTURE_2D);
    glClearColor(0., 1., 1., 1.);    //Background colour
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);                  //Enable OpenGL states
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 1000.0);   //Camera Frustum

}

//------------ Special key event callback ---------------------------------
// To enable the use of left and right arrow keys to rotate the scene
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT) angle -= 0.1;  //Change direction
    else if(key == GLUT_KEY_RIGHT) angle += 0.1;
    else if(key == GLUT_KEY_DOWN)
    {  //Move backward
        eye_x -= 0.5*sin(angle);
        eye_z += 0.5*cos(angle);
    }
    else if(key == GLUT_KEY_UP)
    { //Move forward
        eye_x += 0.5*sin(angle);
        eye_z -= 0.5*cos(angle);
    }

    //Collision detection so doesn't go outside of floor area
    if (eye_z < -13) {
            eye_z = -13;
    }

    if (eye_z >= 33) {
            eye_z = 33;
    }

    if (eye_x >= 23) {
        eye_x = 23;
    }

    if (eye_x < -23) {
        eye_x = -23;
    }


    look_x = eye_x + 100*sin(angle);
    look_z = eye_z - 100*cos(angle);


    glutPostRedisplay();
}
//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize (600, 600);
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("akp41_assignment_1");
   initialize();
   glutTimerFunc(50, myTimer, 0);


   glutDisplayFunc(display);
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}

