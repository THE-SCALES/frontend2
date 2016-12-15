#include <GL/freeglut.h>
#ifndef UTIL_H
#include "util.h"
#endif
#include <cmath>
#include <iostream>
#include <cstdlib>

GLfloat pocket_pos[POCKET][3] = {
    { 130.0f,  64.0f, 0.0f },
    { 130.0f, -64.0f, 0.0f },
    {   0.0f,  70.0f, 0.0f },
    {   0.0f, -70.0f, 0.0f },
    {-130.0f,  64.0f, 0.0f },
    {-130.0f, -64.0f, 0.0f }
};

Hole pocket[POCKET];

//ポケット構造体
void Hole::Draw(int num){
    Set(num);
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
    glTranslatef(Pos.x,Pos.y,Pos.z);
    Cylinder(Radius,6.0f,10.0f);
    glPopMatrix();
}

void Hole::Set(int num){
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	pocket[num].Pos.x=pocket_pos[num][0];
	pocket[num].Pos.y=pocket_pos[num][1];
	pocket[num].Pos.z=pocket_pos[num][2];
	pocket[num].Radius=6.75f;

}

//円柱
void Hole::Cylinder(float radius,float height,int sides)
{
	//上面
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    for(double i = 0; i < sides; i++) {
	double t = PI*2/sides * (double)i;
	glVertex3d(radius * cos(t), radius * sin(t), height);
    }
    glEnd();
	//側面
    glBegin(GL_QUAD_STRIP);
    for(double i = 0; i <= sides; i++){
	double t = i*2*PI/sides;
	glNormal3f((GLfloat)cos(t), (GLfloat)sin(t), 0.0);
	glVertex3f((GLfloat)(radius*cos(t)), (GLfloat)(radius*sin(t)), -height);
	glVertex3f((GLfloat)(radius*cos(t)), (GLfloat)(radius*sin(t)), height);
    }
    glEnd();
	//下面
    glNormal3d(0.0, 0.0, -1.0);
    glBegin(GL_POLYGON);
    for(double i = sides; i >= 0; --i) {
	double t = PI*2/sides * (double)i;
	glVertex3d(radius * cos(t), radius * sin(t), -height);
    }
    glEnd();
}
