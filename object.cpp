#include <GL/freeglut.h>
#ifndef UTIL_H
#include "util.h"
#endif
#include <cmath>
#include <iostream>
#include <cstdlib>

GLfloat normal[][3] = {//面の法線ベクトル
    {  0.0f,  0.0f,  1.0f },
    {  1.0f,  0.0f,  0.0f },
    { -1.0f,  0.0f,  0.0f },
    {  0.0f,  0.0f, -1.0f },
    {  0.0f,  1.0f,  0.0f },
    {  0.0f, -1.0f,  0.0f }
};

GLfloat face[4][3] = {//正規化行列
    {  1.0f,  1.0f,  1.0f },
    {  1.0f,  1.0f, -1.0f },
    {  1.0f, -1.0f, -1.0f },
    {  1.0f, -1.0f,  1.0f }
};

extern Sphere balls[BALLS+1];
extern Hole pocket[POCKET];

//角錐台
void Polygon::Tpyramid(float lw,float lh,float hw,float hh,float depth)
{
    float h_width = hw/2;
    float h_height = hh/2;
    float l_width = lw/2;
    float l_height = lh/2;
    float dep = depth/2;
    glBegin(GL_QUADS);
	//上面
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(h_width,h_height,dep);
    glVertex3f(-l_width,l_height,dep);
    glVertex3f(-l_width,-l_height,dep);
    glVertex3f(h_width,-h_height,dep);
	//右面
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(h_width,h_height,dep);
    glVertex3f(h_width,h_height,-dep);
    glVertex3f(h_width,-h_height,-dep);
    glVertex3f(h_width,-h_height,dep);
	//左面
    glNormal3f(-1.0,0.0,0.0);
    glVertex3f(-l_width,l_height,-dep);
    glVertex3f(-l_width,l_height,dep);
    glVertex3f(-l_width,-l_height,dep);
    glVertex3f(-l_width,-l_height,-dep);
	//下面
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(h_width,h_height,-dep);
    glVertex3f(-l_width,l_height,-dep);
    glVertex3f(-l_width,-l_height,-dep);
    glVertex3f(h_width,-h_height,-dep);
	//前面
    glNormal3f(0.0,1.0,0.0);
    glVertex3f(h_width,h_height,dep);
    glVertex3f(-l_width,l_height,dep);
    glVertex3f(-l_width,l_height,-dep);
    glVertex3f(h_width,h_height,-dep);
	//後面
    glNormal3f(0.0,-1.0,0.0);
    glVertex3f(h_width,-h_height,dep);
    glVertex3f(-l_width,-l_height,dep);
    glVertex3f(-l_width,-l_height,-dep);
    glVertex3f(h_width,-h_height,-dep);
    glEnd();
}

//直方体
void Polygon::Cuboid(float width,float height,float depth)
{
    float wid = width/2;
    float hei = height/2;
    float dep = depth/2;
    int x_col, y_col, z_col;
    float x_pm, y_pm, z_pm;

    glPushMatrix();
    glBegin(GL_QUADS);

    for(int i=0;i<6;i++){
	glNormal3f(normal[i][0], normal[i][1], normal[i][2]);
	if(normal[i][0] == 1.0f){        //行列変換
	    x_col=0; y_col=1; z_col=2;
	    x_pm=1;  y_pm=1;  z_pm=1;
	}else if(normal[i][0] == -1.0f){ //x行列を負に変換
	    x_col=0; y_col=1; z_col=2;
	    x_pm=-1; y_pm=1;  z_pm=1;
	}
	if(normal[i][1] == 1.0f){
	    x_col=2; y_col=0; z_col=1;
	    x_pm=1;  y_pm=1;  z_pm=1;
	}else if(normal[i][1] == -1.0f){
	    x_col=2; y_col=0; z_col=1;
	    x_pm=1;  y_pm=-1; z_pm=1;
	}
	if(normal[i][2] == 1.0f){
	    x_col=2; y_col=1; z_col=0;
	    x_pm=1;  y_pm=1;  z_pm=1;
	}else if(normal[i][2] == -1.0f){
	    x_col=2; y_col=1; z_col=0;
	    x_pm=-1; y_pm=1; z_pm=-1;
	}
	glVertex3f(wid*face[0][x_col]*x_pm,hei*face[0][y_col]*y_pm,dep*face[0][z_col]*z_pm);
	glVertex3f(wid*face[1][x_col]*x_pm,hei*face[1][y_col]*y_pm,dep*face[1][z_col]*z_pm);
	glVertex3f(wid*face[2][x_col]*x_pm,hei*face[2][y_col]*y_pm,dep*face[2][z_col]*z_pm);
	glVertex3f(wid*face[3][x_col]*x_pm,hei*face[3][y_col]*y_pm,dep*face[3][z_col]*z_pm);
    }

    glEnd();
    glPopMatrix();
}

void Polygon::Cues(double x0, double y0, double z0,
		   double x1, double y1, double z1)
{
    if(balls[0].shoot == false){
    GLUquadricObj *cue;
    double x2, y2, z2, len, ang;
    int sides = 8;

    x2 = x1-x0; y2 = y1-y0; z2 = z1-z0;
    len = sqrt(x2*x2 + y2*y2 + z2*z2);
    if(len != 0.0){

	ang = acos(z2*len/(sqrt(x2*x2+y2*y2+z2*z2)*len))/PI*180.0;
	glPushMatrix();
	glTranslated( x0, y0, z0);
	glRotated( ang, -y2*len, x2*len, 0.0);
	cue = gluNewQuadric();
	gluQuadricDrawStyle(cue, GLU_FILL);
	gluQuadricNormals(cue, GLU_SMOOTH);
	gluCylinder(cue, 2.0, 1.5, 80, 8, 8);//円柱
	glPushMatrix();
	glTranslated(0.0, 0.0, 80);
	gluDisk(cue, 0.01, 0.75, 8, 1);
	glPopMatrix();
	gluDisk(cue, 0.01, 1.0, 8, 1);
	glPopMatrix();
    }
    }
}

void Polygon::Arrowd(double x0, double y0, double z0, 
		     double x1, double y1, double z1)
{
    if(balls[0].shoot == false){
    GLUquadricObj *arrows[2];
    double x2, y2, z2, len, ang;

    x2 = x1-x0; y2 = y1-y0; z2 = z1-z0;
    len = sqrt(x2*x2 + y2*y2 + z2*z2);
    if(len != 0.0){
	ang = acos(z2*len/(sqrt(x2*x2+y2*y2+z2*z2)*len))/PI*180.0;

	glPushMatrix();
	glTranslated( x0, y0, z0);
	glRotated( ang, -y2*len, x2*len, 0.0);
	arrows[0] = gluNewQuadric();
	gluQuadricDrawStyle(arrows[0], GLU_FILL);
	gluCylinder(arrows[0], len/5, len/5, len*0.9, 8, 8);//円柱
	glPushMatrix();
	glTranslated( 0.0, 0.0, len*0.9);
	arrows[1] = gluNewQuadric();
	gluQuadricDrawStyle(arrows[1], GLU_FILL);
	gluCylinder(arrows[1], len/1.8, 0.0f, len/0.6, 8, 8);//円錐
	glPopMatrix();
	glPopMatrix();
    }
    }
}

void Polygon::Pocket_side(float radius,float height,float width,float depth,int sides)
{
    float wid = width/2;
    float hei = height/2;
    float dep = depth/2;
	//上面
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(wid,hei,dep);
    for(double i = 0; i <= sides/2; i++) {
	double t = PI/sides * (double)i;
	glVertex3f(radius * cos(t), radius * sin(t) - hei, dep);
    }
    glVertex3f(0.0f,hei,dep);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-wid,hei,dep);
    glVertex3f(0.0f,hei,dep);
    for(double i = sides/2; i <= sides; i++) {
	double t = PI/sides * (double)i;
	glVertex3f(radius * cos(t), radius * sin(t) - hei, dep);
    }
    glEnd();

    glBegin(GL_QUADS);
	//右面
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(wid,hei,dep);
    glVertex3f(wid,hei,-dep);
    glVertex3f(wid,-hei,-dep);
    glVertex3f(wid,-hei,dep);

	//左面
    glNormal3f(-1.0,0.0,0.0);
    glVertex3f(-wid,hei,-dep);
    glVertex3f(-wid,hei,dep);
    glVertex3f(-wid,-hei,dep);
    glVertex3f(-wid,-hei,-dep);
    glEnd();
	//下面
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(wid,hei,-dep);
    for(double i = 0; i <= sides/2; i++) {
	double t = PI/sides * (double)i;
	glVertex3f(radius * cos(t), radius * sin(t) - hei, -dep);
    }
    glVertex3f(0.0f,hei,-dep);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-wid,hei,-dep);
    glVertex3f(0.0f,hei,-dep);
    for(double i = sides/2; i <= sides; i++) {
	double t = PI/sides * (double)i;
	glVertex3f(radius * cos(t), radius * sin(t) - hei, -dep);
    }
    glEnd();

	//前面
    glBegin(GL_QUADS);
    glNormal3f(0.0,1.0,0.0);
    glVertex3f(wid,hei,dep);
    glVertex3f(-wid,hei,dep);
    glVertex3f(-wid,hei,-dep);
    glVertex3f(wid,hei,-dep);
    glEnd();

	//下面
    glBegin(GL_QUAD_STRIP);
    for(double i = 0; i <= sides; i++) {
	double t = PI/sides * (double)i;
	glNormal3f((GLfloat)cos(t), (GLfloat)sin(t), 0.0);
	glVertex3f(radius * cos(t), radius * sin(t) - hei, -dep);
	glVertex3f(radius * cos(t), radius * sin(t) - hei, dep);
    }
    glEnd();

}

void Polygon::Pocket_corner(float radius,float height,float width,float depth,int sides)
{
    float wid = width/2;
    float hei = height/2;
    float dep = depth/2;

	//上面
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(wid,hei,dep);
    glVertex3f(wid,-hei,dep);
    glVertex3f(radius,-hei,dep);
    for(double i = 0; i <= sides; i++) {
	double t = (PI/2) / sides * (double)i;
	glVertex3f(radius * cos(t), radius * sin(t), dep);
    }
    glVertex3f(-wid,radius,dep);
    glVertex3f(-wid,hei,dep);
    glEnd();

    glBegin(GL_QUADS);
	//右面
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(wid,hei,dep);
    glVertex3f(wid,hei,-dep);
    glVertex3f(wid,-hei,-dep);
    glVertex3f(wid,-hei,dep);

	//左面
    glNormal3f(-1.0,0.0,0.0);
    glVertex3f(-wid,hei,dep);
    glVertex3f(-wid,radius,dep);
    glVertex3f(-wid,radius,-dep);
    glVertex3f(-wid,hei,-dep);
    glEnd();
	//下面
    glNormal3d(0.0, 0.0, -1.0);
    glBegin(GL_POLYGON);
    glVertex3f(wid,hei,-dep);
    glVertex3f(wid,-hei,-dep);
    glVertex3f(radius,-hei,-dep);
    for(double i = 0; i <= sides; i++) {
	double t = (PI/2) / sides * (double)i;
	glVertex3f(radius * cos(t), radius * sin(t), -dep);
    }
    glVertex3f(-wid,radius,-dep);
    glVertex3f(-wid,hei,-dep);
    glEnd();

	//後面
    glBegin(GL_QUADS);
    glNormal3f(0.0,1.0,0.0);
    glVertex3f(wid,hei,dep);
    glVertex3f(-wid,hei,dep);
    glVertex3f(-wid,hei,-dep);
    glVertex3f(wid,hei,-dep);

	//前面
    glNormal3f(0.0,-1.0,0.0);
    glVertex3f(wid,-hei,dep);
    glVertex3f(wid,-hei,-dep);
    glVertex3f(radius,-hei,-dep);
    glVertex3f(radius,-hei,dep);
    glEnd();

	//カーブ面
    glBegin(GL_QUAD_STRIP);
    for(double i = 0; i <= sides; i++) {
	double t = (PI/2) / sides * (double)i;
	glNormal3f((GLfloat)cos(t), (GLfloat)sin(t), 0.0);
	glVertex3f(radius * cos(t), radius * sin(t), -dep);
	glVertex3f(radius * cos(t), radius * sin(t), dep);
    }
    glEnd();

}

void Polygon::Ground(void) {
    double ground_max_x = 300.0;
    double ground_max_y = 300.0;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, limelight);  // 地面の色
    glBegin(GL_LINES);
    for(double ly = -ground_max_y ;ly <= ground_max_y; ly+=20.0){
	glVertex3d(-ground_max_x, ly,0);
	glVertex3d(ground_max_x, ly,0);
    }
    for(double lx = -ground_max_x ;lx <= ground_max_x; lx+=20.0){
	glVertex3d(lx, ground_max_y,0);
	glVertex3d(lx, -ground_max_y,0);
    }
    glEnd();
}
