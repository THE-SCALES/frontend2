#include <GL/freeglut.h>
#include "util.h"
#include <cmath>
#include <iostream>
#include <cstdlib>

Sphere balls[BALLS+1];
GLfloat balls_pos[BALLS+1][3] = {
    { -65.0f,   0.0f, 5.0f },
    {  50.0f,   0.0f, 5.0f },
    {  70.0f,  10.0f, 5.0f },
    {  90.0f,   0.0f, 5.0f },
    {  70.0f, -10.0f, 5.0f },
    {  60.0f,   5.0f, 5.0f },
    {  60.0f,  -5.0f, 5.0f },
    {  80.0f,   5.0f, 5.0f },
    {  80.0f,  -5.0f, 5.0f },
    {  70.0f,   0.0f, 5.0f }
};


void Sphere::Draw(int num){

    if(setdec){
	Set(num);
    }
    glPushMatrix();
    glEnable(GL_LIGHT0);

    switch(num){
    case 0:
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	break;

    case 1:
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	break;

    case 2:
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
	break;

    case 3:
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	break;

    case 4:
	glMaterialfv(GL_FRONT, GL_DIFFUSE, purple);
	break;

    case 5:
	glMaterialfv(GL_FRONT, GL_DIFFUSE, orange);
	break;

    case 6:
	glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
	break;

    case 7:
	glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
	break;

    case 8:
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	break;

    case 9:
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lyellow);
	break;

    default:
	break;
    }
    glTranslatef(Pos.x,Pos.y,Pos.z);
    glutSolidSphere(Radius,16,16);
    glPopMatrix();
}


void Sphere::Set(int num){

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

	//自球0番ボール
    balls[num].Pos.x=balls_pos[num][0];
    balls[num].Pos.y=balls_pos[num][1];
    balls[num].Pos.z=balls_pos[num][2];
    balls[num].Radius=5.0f;


    setdec = false;
   
}
