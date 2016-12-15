#ifndef UTIL_H
#define UTIL_H
const int BALLS = 9; //ボールの数
const int POCKET = 6; //ポケットの数
const float PI = 3.141592; //円周率

const int WIDTH = 640; //画面幅
const int HEIGHT = 480; //画面高さ
const int COVER = 6; //カバーの数
const int CORNER_COVER = 8; //コーナーカバーの数

const float ball_e = 0.8; //球体同士の反発係数
const float wall_e = 1.0; //壁の反発係数
const float floor_e = 0.995; //床の反発係数

//ボールの色定義
const GLfloat white[] = { 1.0, 1.0, 1.0 };//白
const GLfloat yellow[] = { 1.0, 1.0, 0.0 };//黄
const GLfloat blue[] = { 0.0, 0.0, 1.0 };//青
const GLfloat red[] = { 1.0, 0.0, 0.0 };//赤
const GLfloat purple[] = { 1.0, 0.0, 1.0 };//紫
const GLfloat orange[] = { 1.0, 0.7, 0.3 };//橙
const GLfloat green[] = { 0.0, 1.0, 0.0 };//緑
const GLfloat brown[] = { 0.5, 0.4, 0.2 };//茶
const GLfloat black[] = { 0.1, 0.1, 0.1 };//黒
const GLfloat lyellow[] = { 1.0, 1.0, 0.3 };//淡黄色
const GLfloat limelight[] = { 0.5, 1.0, 0.5 };//緑
const GLfloat pink[] = { 1.0, 0.5, 0.5 };//ピンク


//3つのベクトル
struct Vector3f{
 float x;
 float y;
 float z;
};


//ボールクラス
class Sphere{
  public:
    GLfloat Radius;     //ボールの半径
    Vector3f Pos;       //ボールの位置
    Vector3f Speed;     //ボールのスピード

    bool setdec;	//ボールを初期位置に配置する一度だけのフラグ
    bool shoot;		//ボールが射出状態かのフラグ
    bool flag;		//ボールが台上にあるかのフラグ

    void Set(int num);  //初期位置に配置する
    void Draw(int num); //ボールを生成する
};

extern Sphere balls[BALLS+1];

//ポケットクラス
class Hole{
   public:
     GLfloat Radius;	//半径

     Vector3f Pos;	//位置

     void Set(int num);	//ポケットの配置
     void Draw(int num);//ポケットの生成
     void Cylinder(float radius, float height, int sides);  //ポケットの円柱生成
};

extern Hole pocket[POCKET];

//ポリゴンクラス
class Polygon{
  public:
//角錐台の生成,クッションカバーに使用
    void Tpyramid(float low_width, float low_height, float high_width, float high_height, float depth);
//直方体の生成,ビリヤード台やサイドカバーに使用
    void Cuboid(float width, float height, float depth);
//キューの生成,白球を発射させるために使用
    void Cues(double x0, double y0, double z0, double x1, double y1, double z1);
//矢印の生成,白球の射出方向に使用
    void Arrowd(double x0, double y0, double z0, double x1, double y1, double z1);
//ポケットカバーの生成,3番,4番ポケットのカバーに使用
    void Pocket_side(float radius, float height, float width, float depth, int sides);
//ポケットコーナーカバーの生成,1,2,5,6番ポケットカバーに使用
    void Pocket_corner(float radius, float height, float width, float depth, int sides);
//メッシュの生成,座標確認に使用
    void Ground();
};
#endif
