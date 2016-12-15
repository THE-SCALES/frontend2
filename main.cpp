#include <GL/freeglut.h>
#ifndef UTIL_H
#include "util.h"
#endif
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

//回転用
float angle = 0.0f;
float roll = 0.0f;
//平行移動用
float zoom = 50.0f;
bool camera_roll = false;

//ライトの位置
const GLfloat lightpos[] = { 0.0, 0.0, 100.0, 1.0 };

GLfloat cushion[6][3] = {//クッションの位置
    { 130.0f,   0.0f, 10.0f },
    {-130.0f,   0.0f, 10.0f },
    { -65.0f,  67.5f, 10.0f },
    {  65.0f,  67.5f, 10.0f },
    { -65.0f, -67.5f, 10.0f },
    {  65.0f, -67.5f, 10.0f }    
};

GLfloat cover[6][3] = {//カバーサイドの位置
    { -65.0f, -77.0f, 10.0f },
    {  65.0f, -77.0f, 10.0f },
    { -65.0f,  77.0f, 10.0f },
    {  65.0f,  77.0f, 10.0f },
    { 140.0f,   0.0f, 10.0f },
    {-140.0f,   0.0f, 10.0f }    
};

GLfloat corner_cover[8][3] = {//コーナーカバーの位置
    { 134.0f,  75.0f, 10.0f },
    { 140.0f,  71.0f, 10.0f },
    { 134.0f, -75.0f, 10.0f },
    { 140.0f, -71.0f, 10.0f },
    {-134.0f,  75.0f, 10.0f },
    {-140.0f,  71.0f, 10.0f },
    {-134.0f, -75.0f, 10.0f },
    {-140.0f, -71.0f, 10.0f }    
};
GLfloat corner_pos[2][3] = {//コーナーカバーの位置
    { 23.0f,  15.0f, 10.0f },
    { 12.0f,  22.0f, 10.0f }    
};

extern Sphere balls[BALLS+1];
extern Hole pocket[POCKET];

int target;

//当り判定
bool Calc_Hit(Sphere& a,Sphere& b){
    if(sqrt((a.Pos.x-b.Pos.x)*(a.Pos.x-b.Pos.x)+(a.Pos.y-b.Pos.y)*(a.Pos.y-b.Pos.y)+(a.Pos.z-b.Pos.z)*(a.Pos.z-b.Pos.z))<=a.Radius+b.Radius){
	return true;
    }else{
	return false;
    }
}

//消去判定
bool Calc_Erase(Sphere& a,Hole& b){
    if(sqrt((a.Pos.x-b.Pos.x)*(a.Pos.x-b.Pos.x)+(a.Pos.y-b.Pos.y)*(a.Pos.y-b.Pos.y)+(a.Pos.z-b.Pos.z)*(a.Pos.z-b.Pos.z))<=a.Radius+b.Radius){
	return true;
    }else{
	return false;
    }
}

void display(void)
{
    Polygon obj;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	//視野角,アスペクト比(ウィンドウの幅/高さ),描画する範囲(最も近い距離,最も遠い距離)
    gluPerspective(zoom, (double)WIDTH / (double)HEIGHT, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	//視点の設定
    float x = angle * PI / 180;
    float arrow = roll * PI / 180; 
    gluLookAt(300*sin(x),-300.0*cos(x),225.0, //カメラの座標 0.0,-400.0,300.0
	      0.0,0.0,0.0, // 注視点の座標
	      0.0,0.0,1.0); // 画面の上方向を指すベクトル

	//ライトの設定
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    for(int i=0;i<=BALLS;i++){ //ボール生成
	balls[i].Draw(i);
    }

    for(int i=0;i<POCKET;i++){ //ポケット生成
	pocket[i].Draw(i);
    }

	//テーブル床
    glMaterialfv(GL_FRONT, GL_DIFFUSE, limelight);
    obj.Cuboid(290.0f,160.0f,5.0f);

	//クッションサイド
    for(int i=0;i<COVER;i++){
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, limelight);
	glTranslatef(cushion[i][0],cushion[i][1],cushion[i][2]);
	if(i==0 || i==1){
	    if(i==1) glRotatef(180.0f,0.0f,0.0f,1.0f);
	    obj.Tpyramid(8.0f,100.0f,8.0f,120.0f,10.0f);
	}else if(i==2 || i==3){
	    glRotatef(90.0f,0.0f,0.0f,1.0f);
	    obj.Tpyramid(8.0f,105.0f,8.0f,116.0f,10.0f);
	}else if(i==4 || i==5){
	    glRotatef(270.0f,0.0f,0.0f,1.0f);
	    obj.Tpyramid(8.0f,105.0f,8.0f,116.0f,10.0f);
	}
	glPopMatrix();
    }

	//カバーサイド
    for(int i=0; i<COVER; i++){
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
	glTranslatef(cover[i][0],cover[i][1],cover[i][2]);
	if(i < 4){
	    obj.Cuboid(116.0f,12.0f,10.0f);
	}else{
	    obj.Cuboid(12.0f,120.0f,10.0f);
	}
	glPopMatrix();
    }

	//ポケットサイドカバー
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(0.0f,76.0f,10.0f);
    obj.Pocket_side(7.0f,14.0f,14.0f,10.0f,8);//
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(0.0f,-76.0f,10.0f);
    glRotatef(180.0f,0.0f,0.0f,1.0f);
    obj.Pocket_side(7.0f,14.0f,14.0f,10.0f,8);//
    glPopMatrix();

	//ポケットコーナーカバー
    for(int i=0;i<CORNER_COVER;i++){
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(corner_cover[i][0],corner_cover[i][1],corner_cover[i][2]);
    obj.Cuboid(corner_pos[i%2][0],corner_pos[i%2][1],corner_pos[i%2][2]);
    glPopMatrix();
    }
	//キュー
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, lyellow);
    glTranslatef(balls[0].Pos.x, balls[0].Pos.y, 0.0f);
    obj.Cues(83.0f*cos(arrow+PI),83.0f*sin(arrow+PI), 30.0f, 5.5f*cos(arrow+PI), 5.5f*sin(arrow+PI), 7.0f);
    glPopMatrix();

	//矢印
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(balls[0].Pos.x, balls[0].Pos.y, 0.0f);
    obj.Arrowd(10.0f*cos(arrow),10.0f*sin(arrow),5.0f, 15.0f*cos(arrow), 15.0f*sin(arrow), 5.0f);//
    glPopMatrix();

	//メッシュ(地面)
    obj.Ground();

    glutSwapBuffers();
}


void Hitbox(void){//当たり判定による衝突後の座標計算

    float v0, v1, v2, dir1, dir2, dir, diffx, diffy;
    float ux, uy, vx, vy;
    float udx, udy, vdx, vdy;
    float wall_ang = PI/4;

    for(int i=0; i<BALLS; i++){
	for(int j=i+1; j<=BALLS; j++){ 
	    if(Calc_Hit(balls[i],balls[j])){
		    //自球側から相手球のベクトル計算
		v0 = sqrt((balls[i].Speed.x*balls[i].Speed.x)+(balls[i].Speed.y*balls[i].Speed.y));
		diffx = balls[j].Pos.x-balls[i].Pos.x;//球間のx距離
		diffy = balls[j].Pos.y-balls[i].Pos.y;//球間のy距離
		dir1 = atan2f(diffy,diffx);//自球と相手球の角度
		dir2 = atan2f(balls[i].Speed.y, balls[i].Speed.x);//自球進行方向
                dir = dir2 - dir1;//角度差
                v1 = fabs(v0*cos(dir));//衝突後相手球の速度
                v2 = fabs(v0*sin(dir));//衝突後自球の速度
                vx = v1*cos(dir1);//相手球x速度
                vy = v1*sin(dir1);//相手球y速度

		if(sin(dir)<0){
                    ux = v2*cos(dir1-PI/2);//衝突後自球x速度
                    uy = v2*sin(dir1-PI/2);//衝突後自球y速度
		}else{
		    ux = v2*cos(dir1+PI/2);
		    uy = v2*sin(dir1+PI/2);
		}
		    //相手球側から自球のベクトル計算
		v0 = sqrt((balls[j].Speed.x*balls[j].Speed.x)+(balls[j].Speed.y*balls[j].Speed.y));
                diffx = balls[i].Pos.x-balls[j].Pos.x;
		diffy = balls[i].Pos.y-balls[j].Pos.y;
                dir1 = atan2f(diffy,diffx);
		dir2 = atan2f(balls[j].Speed.y, balls[j].Speed.x);
		dir = dir2 - dir1;
		v1 = fabs(v0*cos(dir));
		v2 = fabs(v0*sin(dir));
		vdx = v1*cos(dir1);
		vdy = v1*sin(dir1);

		if(sin(dir)<0){
		    udx = v2*cos(dir1-PI/2);
		    udy = v2*sin(dir1-PI/2);
		}else{
		    udx = v2*cos(dir1+PI/2);
		    udy = v2*sin(dir1+PI/2);
		}
		    //衝突による速度合成
		balls[i].Speed.x = 0.5*(1+ball_e)*(ux+vdx);
		balls[i].Speed.y = 0.5*(1+ball_e)*(uy+vdy);
		balls[j].Speed.x = 0.5*(1+ball_e)*(vx+udx);
		balls[j].Speed.y = 0.5*(1+ball_e)*(vy+udy);
	    }
	}
    }

	//壁の反射や床の摩擦による速度減衰
    for(int i=0; i<=BALLS; i++){
	    //4方向斜めの球体x座標とy座標
	float rh_wallx = balls[i].Pos.x+balls[i].Radius*cos(wall_ang);
	float lh_wallx = balls[i].Pos.x+balls[i].Radius*cos(wall_ang+PI/2);
	float ll_wallx = balls[i].Pos.x+balls[i].Radius*cos(wall_ang+PI);
	float rl_wallx = balls[i].Pos.x+balls[i].Radius*cos(wall_ang+3*PI/2);
	float rh_wally = balls[i].Pos.y+balls[i].Radius*sin(wall_ang);
	float lh_wally = balls[i].Pos.y+balls[i].Radius*sin(wall_ang+PI/2);
	float ll_wally = balls[i].Pos.y+balls[i].Radius*sin(wall_ang+PI);
	float rl_wally = balls[i].Pos.y+balls[i].Radius*sin(wall_ang+3*PI/2);
	float tmp;

	balls[i].Pos.x += balls[i].Speed.x;
	balls[i].Pos.y += balls[i].Speed.y;
	balls[i].Speed.x *= floor_e;
	balls[i].Speed.y *= floor_e;
	if((pow(balls[i].Speed.x, 2.0) + pow(balls[i].Speed.y, 2.0)) < 5.0e-4){
	    balls[i].Speed.x = 0.0f;
	    balls[i].Speed.y = 0.0f;
	}
	if(balls[i].Pos.y>=-55.0f && balls[i].Pos.y<=55.0f){ 
	    if((balls[i].Pos.x+balls[i].Radius)>127.0f){//クッション右側の反射
		balls[i].Speed.x*=-1.0f*wall_e;
		balls[i].Speed.y*=wall_e;
		balls[i].Pos.x-=balls[i].Pos.x-127.0+balls[i].Radius;
	    }else if((balls[i].Pos.x-balls[i].Radius)<-127.0f){//クッション左側の反射
		balls[i].Speed.x*=-1.0f*wall_e;
		balls[i].Speed.y*=wall_e;
		balls[i].Pos.x+=-1.0*(balls[i].Pos.x)-127.0+balls[i].Radius;
	    }
	}
	if(balls[i].Pos.x>=-117.5f && balls[i].Pos.x<=-12.5f){//クッションの左側上下の反射
	    if((balls[i].Pos.y+balls[i].Radius)>63.5f){
		balls[i].Speed.y*=-1.0f*wall_e;
		balls[i].Speed.x*=wall_e;
		if(balls[i].flag==false) balls[i].Pos.y-=balls[i].Pos.y-63.5+balls[i].Radius;
	    }else if((balls[i].Pos.y-balls[i].Radius)<-63.5f){
		balls[i].Speed.y*=-1.0f*wall_e;
		balls[i].Speed.x*=wall_e;
		if(balls[i].flag==false) balls[i].Pos.y+=-1.0*(balls[i].Pos.y)-63.5+balls[i].Radius;
	    }
	}
    

	if(balls[i].Pos.x>=12.5f && balls[i].Pos.x<=117.5f){//クッション右側上下の反射
	    if((balls[i].Pos.y+balls[i].Radius)>63.5f){
		balls[i].Speed.y*=-1.0f*wall_e;
		balls[i].Speed.x*=wall_e;
		if(balls[i].flag==false) balls[i].Pos.y-=balls[i].Pos.y-63.5+balls[i].Radius;
	    }else if((balls[i].Pos.y-balls[i].Radius)<-63.5f){
		balls[i].Speed.y*=-1.0f*wall_e;
		balls[i].Speed.x*=wall_e;
		if(balls[i].flag==false) balls[i].Pos.y+=-1.0*(balls[i].Pos.y)-63.5+balls[i].Radius;
	    }
	}
    
	if((63.5+(71.5-63.5)/(123.0-117.5)*(lh_wallx-117.5)) < lh_wally && lh_wallx >= 117.5f && lh_wallx <= 123.0f){//ポケット右上の反射
	    tmp = balls[i].Speed.y;
	    balls[i].Speed.y=-1.0*wall_e*balls[i].Speed.x;
	    balls[i].Speed.x=-1.0*wall_e*tmp;
	    if(balls[i].flag==false){
		balls[i].Pos.y-= lh_wally-(63.5+(71.5-63.5)/(123.0-117.5)*(lh_wallx-117.5));
		balls[i].Pos.x-= lh_wallx-(123.0+(117.5-123.0)/(-63.5+71.5)*(lh_wally+71.5));
	    }
	}else if((126.0+(134.0-126.0)/(60.0-50.0)*(rl_wallx-50.0)) > rl_wally && rl_wallx >= 126.0f && rl_wallx <= 134.0f){
	    tmp = balls[i].Speed.y;
	    balls[i].Speed.y=-1.0*wall_e*balls[i].Speed.x;
	    balls[i].Speed.x=-1.0*wall_e*tmp;
	    if(balls[i].flag==false){
		balls[i].Pos.y-= rl_wally-(126.0+(134.0-126.0)/(60.0-50.0)*(rl_wallx-50.0));
		balls[i].Pos.x-= rl_wallx-(60.0+(50.0-60.0)/(-126.0+134.0)*(rl_wally+134.0));
	    }
	}
    
	if((-63.5+(-71.5+63.5)/(123.0-117.5)*(ll_wallx-117.5)) > ll_wally && ll_wallx >= 117.5f && ll_wallx <= 123.0f){//ポケット右下の反射
	    tmp = balls[i].Speed.y;
	    balls[i].Speed.y=-1.0*wall_e*balls[i].Speed.x;
	    balls[i].Speed.x=-1.0*wall_e*tmp;
	    if(balls[i].flag==false){
		balls[i].Pos.y-= ll_wally-(-63.5+(-71.5+63.5)/(123.0-117.5)*(ll_wallx-117.5));
		balls[i].Pos.x-= ll_wallx-(123.0+(117.5-123.0)/(63.5-71.5)*(ll_wally-71.5));
	    }
	}else if((-50.0+(-60.0+50.0)/(134.0-126.0)*(rh_wallx-126.0)) && rh_wallx >= 126.0f && rh_wallx <= 134.0f){
	    tmp = balls[i].Speed.y;
	    balls[i].Speed.y=-1.0*wall_e*balls[i].Speed.x;
	    balls[i].Speed.x=-1.0*wall_e*tmp;
	    if(balls[i].flag==false){
		balls[i].Pos.y-= rh_wally-(-50.0+(-60.0+50.0)/(134.0-126.0)*(rh_wallx-126.0));
		balls[i].Pos.x-= rh_wallx-(134.0+(126.0-134.0)/(50.0-60.0)*(rh_wally-60.0));
	    }
	}
	   
	if((-69.0+(-61.0+69.0)/(12.5-7.0)*(rl_wallx-7.0)) > rl_wally && rl_wallx >= 7.0f && rl_wallx <= 12.5f){//ポケット下の反射
	    tmp = balls[i].Speed.y;
	    balls[i].Speed.y=-1.0*wall_e*balls[i].Speed.x;
	    balls[i].Speed.x=-1.0*wall_e*tmp;
	    if(balls[i].flag==false){
		balls[i].Pos.y-= rl_wally-(-69.0+(-61.0+69.0)/(12.5-7.0)*(rl_wallx-7.0));
		balls[i].Pos.x-= rl_wallx-(12.5+(7.0-12.5)/(-69.0+61.0)*(rl_wally+61.0));
	    }
	}else if((-61.0+(-69.0+61.0)/(-12.5+7.0)*(ll_wallx+7.0)) > ll_wally && ll_wallx <= -7.0f && ll_wallx >= -12.5f){
	    tmp = balls[i].Speed.y;
	    balls[i].Speed.y=-1.0*wall_e*balls[i].Speed.x;
	    balls[i].Speed.x=-1.0*wall_e*tmp;
	    if(balls[i].flag==false){
		balls[i].Pos.y-= ll_wally-(-61.0+(-69.0+61.0)/(-12.5+7.0)*(ll_wallx+7.0));
		balls[i].Pos.x-= ll_wallx-(-12.5+(-7.0+12.5)/(-61.0+61.0)*(ll_wally+61.0));
	    }
	}
	if((69.0+(61.0-69.0)/(12.5-7.0)*(rh_wallx-7.0)) < rh_wally && rh_wallx >= 7.0f && rh_wallx <= 12.5f){//ポケット上の反射
	    tmp = balls[i].Speed.y;
	    balls[i].Speed.y=-1.0*wall_e*balls[i].Speed.x;
	    balls[i].Speed.x=-1.0*wall_e*tmp;
	    if(balls[i].flag==false){
		balls[i].Pos.y-= rh_wally-(69.0+(61.0-69.0)/(12.5-7.0)*(rh_wallx-7.0));
		balls[i].Pos.x-= rh_wallx-(12.5+(7.0-12.5)/(69.0-61.0)*(rh_wally-61.0));
	    }
	}else if((61.0+(69.0-61.0)/(-7.0+12.5)*(lh_wallx+12.5)) < lh_wally  && lh_wallx <= -7.0f && lh_wallx >= -12.5f){
	    tmp = balls[i].Speed.y;
	    balls[i].Speed.y=-1.0*wall_e*balls[i].Speed.x;
	    balls[i].Speed.x=-1.0*wall_e*tmp;
	    if(balls[i].flag==false){
		balls[i].Pos.y-= lh_wally-(61.0+(69.0-61.0)/(-7.0+12.5)*(lh_wallx+12.5));
		balls[i].Pos.x-= lh_wallx-(-12.5+(-7.0+12.5)/(61.0-69.0)*(lh_wally-69.0));
	    }		
	}
    
	if((-71.5+(-63.5+71.5)/(-117.5+123.0)*(rl_wallx+123.0)) > rl_wally && rl_wallx <= -117.5f && rl_wallx >= -123.0f){//ポケット左下の反射
	    tmp = balls[i].Speed.y;
	    balls[i].Speed.y=-1.0*wall_e*balls[i].Speed.x;
	    balls[i].Speed.x=-1.0*wall_e*tmp;
	    if(balls[i].flag==false){
		balls[i].Pos.y-= rl_wally-(-71.5+(-63.5+71.5)/(-117.5+123.0)*(rl_wallx+123.0));
		balls[i].Pos.x-= rl_wallx-(-123.0+(-117.5+123.0)/(-71.5+63.5)*(rl_wally+63.5));
	    }	
	}else if((-60.0+(-50.0+60.0)/(-126.0+134.0)*(lh_wally+134.0)) < lh_wally && lh_wallx <= -126.0f && lh_wallx >= -134.0f){
	    tmp = balls[i].Speed.y;
	    balls[i].Speed.y=-1.0*wall_e*balls[i].Speed.x;
	    balls[i].Speed.x=-1.0*wall_e*tmp;
	    if(balls[i].flag==false){
		balls[i].Pos.y-= lh_wally-(-60.0+(-50.0+60.0)/(-126.0+134.0)*(lh_wally+134.0));
		balls[i].Pos.x-= lh_wallx-(-134.0+(-126.0+134.0)/(-60.0+50.0)*(lh_wally+50.0));
	    }	
	}
    
	if((71.5+(63.5-71.5)/(-117.5+123.0)*(rh_wallx+123.0)) < rh_wally && rh_wallx <= -117.5f && rh_wallx >= -123.0f){//ポケット左上の反射
	    tmp = balls[i].Speed.y;
	    balls[i].Speed.y=-1.0*wall_e*balls[i].Speed.x;
	    balls[i].Speed.x=-1.0*wall_e*tmp;
	    if(balls[i].flag==false){
		balls[i].Pos.y-= rh_wally-(71.5+(63.5-71.5)/(-117.5+123.0)*(rh_wallx+123.0));
		balls[i].Pos.x-= rh_wallx-(-123.0+(-117.5+123.0)/(71.5-63.5)*(rh_wally-63.5));
	    }		
	}else if((60.0+(50.0-60.0)/(-126.0+134.0)*(ll_wallx+134.0)) > ll_wally && ll_wallx <= -126.0f && ll_wallx >= -134.0f){
		tmp = balls[i].Speed.y;
		balls[i].Speed.y=-1.0*wall_e*balls[i].Speed.x;
		balls[i].Speed.x=-1.0*wall_e*tmp;
		if(balls[i].flag==false){
		    balls[i].Pos.y-= ll_wally-(60.0+(50.0-60.0)/(-126.0+134.0)*(ll_wallx+134.0));
		    balls[i].Pos.x-= ll_wallx-(-134.0+(-126.0+134.0)/(60.0-50.0)*(ll_wally-50.0));
		}		
	    }		
    }		
	 
    for(int i=0; i<=BALLS; i++){
	if(balls[i].Speed.x != 0.0f || balls[i].Speed.y != 0.0f){
	    break;
	}else{
	    if(i==BALLS){
		balls[0].shoot=false;
	    }
	}
    }
    
}

void rule_check(void){

    if(balls[0].flag==false){
	    //ファウル処理
    }

	//コンビネーションショットでゲームが終了した場合の処理
    if(balls[0].shoot==false && balls[0].flag==false && balls[9].flag==true){
	for(int i=0; i<=BALLS; i++){
	    balls[i].flag=true;
	    balls[i].Pos.x=0.0f+11.0f*i;
	    balls[i].Pos.y=-100.0f;
	    balls[i].Speed.x=0.0f;
	    balls[i].Speed.y=0.0f;
	}
    }
}

void Erasebox(void){//当たり判定によるビリヤード球の消去
    for(int i=0; i<=BALLS; i++){
	for(int j=0; j<=POCKET; j++){
	    if(Calc_Erase(balls[i], pocket[j])){
		balls[i].flag=true;
		balls[i].Pos.x=0.0f+11.0f*i;
		balls[i].Pos.y=-100.0f;
		balls[i].Speed.x=0.0f;
		balls[i].Speed.y=0.0f;
		rule_check();
	    }
	}
    }
}

void idle(void)
{
    if(camera_roll){
	angle+=0.2f;
	if(angle>360.0f) angle-=360.0f;
    }
    Hitbox();
    Erasebox();
    glutPostRedisplay();
}

void Init(){

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}

void command(unsigned char key, int x, int y){
    float dir = roll * PI /180;
    switch(key){
	    //space key
    case ' '://自球の射出
	if(balls[0].shoot==false){
	balls[0].Speed.x=10.0f*cos(dir);
	balls[0].Speed.y=10.0f*sin(dir);
	balls[0].shoot=true;
	glutIdleFunc(idle);
	}
	break;
    case 'w'://自球を初期位置へリセット
	balls[0].Pos.x=-65.0f;
	balls[0].Pos.y=0.0f;
	break;
    case 's'://カメラの方向移動(円形)
	camera_roll = true;
	break;
    case 'd'://カメラの移動停止
	camera_roll = false;
	break;
    case 'r'://全球の初期位置スタート、リセット
	for(int i=0; i<=9; i++){
	    balls[i].setdec=true;
	    balls[i].shoot=false;
	    balls[i].Speed.x=0.0f;
	    balls[i].Speed.y=0.0f;
	    target = 1;
	}
	Init();
	break;
    case 'q'://終了
	exit(0);
	break;
    default:
	break;
    }
}

void action(int key, int x, int y){
    switch(key){
    case GLUT_KEY_UP://上キーでズームアウト
	zoom += 0.5f;
	break;
    case GLUT_KEY_DOWN://下キーでズームアップ
	zoom -= 0.5f;
	break;
    case GLUT_KEY_LEFT://左回りに射出方向の決定
	roll += 1.0f;
	break;
    case GLUT_KEY_RIGHT://右回りに射出方向の決定
	roll -= 1.0f;
	break;
    default:
	break;
    }
}

int main(int argc, char *argv[])
{
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("billiards");
    glutDisplayFunc(display);
    glutKeyboardFunc(command);
    glutSpecialFunc(action);
    glutIdleFunc(idle);
    Init();
    glutMainLoop();
    return 0;
}
