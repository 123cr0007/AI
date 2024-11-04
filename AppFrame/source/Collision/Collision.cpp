#include "DxLib.h"
#include "Collision.h"

float CheckAngle(VECTOR p1, VECTOR p2, VECTOR p3) {

	VECTOR v1 = VSub(p1, p2);
	VECTOR v2 = VSub(p3, p2);

	float radp2 = VDot(v1, v2);

	if (radp2 < 0) {
		return false;
	}
	else {
		return true;
	}
}

// 0～1の間にクランプ
void clamp01(float& v) {
	if (v < 0.0f)
		v = 0.0f;
	else if (v > 1.0f)
		v = 1.0f;
}

// -1～1の間にクランプ
void clanp1m1(float& v) {
	if (v < -1.0f)
		v = -1.0f;
	else if (v > 1.0f)
		v = 1.0f;
}

// min～maxの間にクランプ
void clamp(float& v, float min, float max) {
	if (v < min)
		v = min;
	else if (v > max)
		v = max;
}


bool isParallel(VECTOR p1, VECTOR p2) {

	//外積取る
	VECTOR v = VCross(p1, p2);

	//サイズ見る
	float d = VSize(v);

	// 誤差範囲内なら平行と判定
	if (-0.0001f < d && d < 0.0001f) {

		return true;
	}

	return false;
}

float CheckDistPointLine(VECTOR p1, VECTOR p2a, VECTOR p2b, VECTOR* h, float* t) {

	//p1 :求めたい点 
	//p2a:直線の座標1
	//p2b:直線の座標2

	//p2aとp2bで直作る
	// a→bのベクトル
	VECTOR v2 = VSub(p2b, p2a);

	//直線状の点Hを求める
	//公式　＝　p2+ｔv2
	//まずｔを求める
	*t = VDot(v2, VSub(p1, p2a)) / VDot(v2, v2);

	//公式に当てはめる
	*h = VAdd(p2a, VGet(v2.x * *t, v2.y * *t, v2.z * *t));

	//p1とＨの距離をとる
	VECTOR in = VSub(p1, *h);
	float length = sqrt(VDot(in, in));

	return length;
}

float CheckDistPointSegment(VECTOR p1, VECTOR p2a, VECTOR p2b, VECTOR* h, float* t) {

	//p1 :求めたい点 
	//p2a:線分の始点
	//p2b:線分終点

	//とりあえず直線との最短距離
	float length = CheckDistPointLine(p1, p2a, p2b, h, t);


	//内積が0未満なら点同士の最短距離にする
	//こっちp1a側
	if (CheckAngle(p1, p2a, p2b) == false) {

		*h = p2a;
		VECTOR in = VSub(p1, p2a);
		length = sqrt(VDot(in, in));
	}
	//こっちp1b側
	else if (CheckAngle(p1, p2b, p2a) == false) {

		*h = p2b;
		VECTOR in = VSub(p1, p2b);
		length = sqrt(VDot(in, in));
	}

	return length;
}


float CheckDistLineLine(VECTOR p1a, VECTOR p1b, VECTOR p2a, VECTOR p2b,
	VECTOR* h1, VECTOR* h2, float* t1, float* t2) {

	//p1a:直線の座標1
	//p1b:直線の座標2

	//p2a:直線の座標1
	//p2b:直線の座標2

	//座標二つから直線二種類作成
	VECTOR v1 = VSub(p1b, p1a);
	VECTOR v2 = VSub(p2b, p2a);

	//平行なら二点間の最短距離
	if (isParallel(v1, v2) == true) {
		//p1とＨの距離をとる
		VECTOR in = VSub(p1a, p2a);
		*h1 = p1a;
		float length = CheckDistPointSegment(p1a, p2a, p2b, h2, t2);

		return length;
	}


	float dv1v2 = VDot(v1, v2);
	float dv1v1 = VDot(v1, v1);
	float dv2v2 = VDot(v2, v2);
	VECTOR vp2p1 = VSub(p1a, p2a);

	float a = VDot(v1, v1);
	float b = VDot(v1, v2);
	float c = VDot(v2, v2);
	float d = VDot(v1, VSub(p1a, p2a));
	float e = VDot(v2, VSub(p1a, p2a));

	//
	*t1 = (dv1v2 * VDot(v2, vp2p1) - dv2v2 * VDot(v1, vp2p1))
		/ (dv1v1 * dv2v2 - dv1v2 * dv1v2);

	//
	*h1 = VAdd(p1a, VScale(v1, *t1));

	//
	*t2 = VDot(v2, VSub(*h1, p2a)) / dv2v2;

	//
	*h2 = VAdd(p2a, VScale(v2, *t2));

	VECTOR in = VSub(*h1, *h2);
	float length = sqrt(VDot(in, in));

	return length;
}

float CheckDistSegment(VECTOR p1a, VECTOR p1b, VECTOR p2a, VECTOR p2b,
	VECTOR* h1, VECTOR* h2, float* t1, float* t2) {


	VECTOR v1 = VSub(p1b, p1a);
	VECTOR v2 = VSub(p2b, p2a);

	if (isParallel(v1, v2) == true) {
		//p1とＨの距離をとる
		VECTOR in = VSub(p1a, p2a);

		float length = CheckDistPointSegment(p2a, p1a, p1b, h1, t1);
		length = CheckDistPointSegment(p1a, p2a, p2b, h2, t2);

		return length;
	}
	else {
		float length = CheckDistLineLine(p1a, p1b, p2a, p2b, h1, h2, t1, t2);

		if (
			0.0f <= *t1 && *t1 <= 1.0f &&
			0.0f <= *t2 && *t2 <= 1.0f
			) {

			return length;
		}
	}

	clamp01(*t1);
	//*t1 = 1;
	*h1 = VAdd(p1a, VScale(v1, *t1));
	float length = CheckDistPointSegment(p1a, p2a, p2b, h2, t2);
	if (0.0f <= *t1 && *t1 <= 1.0f)
		return length;

	clamp01(*t2);
	*h2 = VAdd(p2a, VScale(v2, *t2));
	float length2 = CheckDistPointSegment(p2a, p1a, p1b, h1, t1);
	if (0.0f <= *t2 && *t2 <= 1.0f)
		return length;
}

bool CheckHitPointCapsule(VECTOR p1a, VECTOR p1b, VECTOR p2, float r1, float r2) {

	VECTOR c1 = VGet(0, 0, 0), c2 = VGet(0, 0, 0);
	float f1 = 0, f2 = 0;

	float MaxLength = r1 + r2;
	float NowLength = CheckDistPointSegment(p2, p1a, p1b, &c2, &f2);

	if (MaxLength > NowLength) {

		return true;
	}

	return false;
}

bool CheckHitCapsule(VECTOR p1a, VECTOR p1b, VECTOR p2a, VECTOR p2b, float r1, float r2) {

	VECTOR c1 = VGet(0,0,0), c2 = VGet(0, 0, 0);
	float f1 = 0, f2 = 0;

	float MaxLength = r1 + r2;
	float NowLength = CheckDistSegment(p1a, p1b, p2a, p2b, &c1, &c2, &f1, &f2);

	if (MaxLength > NowLength) {

		return true;
	}
	
	return false;
}

VECTOR CheckCapsule(VECTOR p1a, VECTOR p1b, float r1, VECTOR p2a, VECTOR p2b, float r2) {

	VECTOR c1, c2;
	float f1 = 0, f2 = 0;

	//ここで触れてない状態で最大の二点間の距離をとる
	float _Max = r1 + r2;
	float MaxLen = CheckDistSegment(VGet(0, 0, 0), VGet(0, 50, 0), VGet(_Max, 0, 0), VGet(_Max, 50, 0), &c1, &c2, &f1, &f2);

	//引数から今の状態のカプセル二つの距離をとる
	float Len = CheckDistSegment(p1a, p1b, p2a, p2b, &c1, &c2, &f1, &f2);

	//線分同士の最短距離から最近点二つをとって角度を出してから単位化
	VECTOR rad = VSub(c1, c2);
	rad = VNorm(rad);

	if (Len < _Max) {

		float SubLen = MaxLen - Len;
		VECTOR v = VScale(rad, SubLen);

		return v;
	}


	return VGet(0, 0, 0);
}

VECTOR MakeWallLap(MV1_COLL_RESULT_POLY HitNorm, VECTOR MoveV) {

	//法線ベクトル(V)を求めるための公式
	// V = F * aN
	// F(移動ベクトル),a(-F * N),N(法線ベクトル（単位化したやつ）)

	// 法線ベクトル
	VECTOR Normal = HitNorm.Normal;
	Normal = VNorm(Normal);

	// 移動ベクトル
	VECTOR FrontV = MoveV;

	// 移動ベクトルに-1かけたやつ（ReverseMove）
	VECTOR RMove = VScale(FrontV,-1);

	//壁に対して平行なベクトル(壁擦り)求めるのに使うやつ
	//法線と逆移動ベクトルの内積
	float a = VDot(RMove, Normal);

	//壁に対して平行なベクトル(壁擦り)求めるのに使うやつその２
	//移動ベクトルに足すためのベクトル
	Normal = VScale(Normal, a);

	//壁擦りベクトル作成
	//WR = wall rapping = 壁擦り
	VECTOR WR = VAdd(FrontV, Normal);

	return WR;
}

float VectorAbs(VECTOR v)
{
	float v_comp[] = {v.x,v.y,v.z};
	int length = sizeof(v_comp) / sizeof(v_comp[0]);
	for(int i=0;i<length;++i)
	{
		v_comp[i] = abs(v_comp[i]);
	}
	VECTOR absV = VGet(v_comp[0], v_comp[1], v_comp[2]);
	return  sqrt(VSquareSize(absV));
}

bool CheckHitPointCorn(VECTOR top, VECTOR bottom, float r, VECTOR p)
{
	float h = VectorAbs(VSub(bottom, top));
	VECTOR PnT = VSub(p, top);
	VECTOR BnT = VSub(bottom, top);
	if(0.0f <= VDot(PnT,BnT) &&
		VDot(PnT,BnT) <= h*h &&
		VectorAbs(VCross(PnT, BnT)) <= VectorAbs(PnT)*r*h/sqrt(r*r+h*h))
	{
		return true;
	}
	return false;
}

// gpt産です
bool CheckHitSegmentPlane(VECTOR p1a, VECTOR p1n, VECTOR p2a, VECTOR p2b, VECTOR& h)
{
	// 平面の法線ベクトルの成分
	float a = p1n.x, b = p1n.y, c = p1n.z;
	// 平面上の点の座標
	float x0 = p1a.x, y0 = p1a.y, z0 = p1a.z;

	// 線分の端点の座標
	float x1 = p2a.x, y1 = p2a.y, z1 = p2a.z;
	float x2 = p2b.x, y2 = p2b.y, z2 = p2b.z;

	// tの分母部分の計算（平面と線分の方向ベクトルの内積）
	float denominator = a * (x2 - x1) + b * (y2 - y1) + c * (z2 - z1);
	if(denominator == 0) {
		// 分母が0の場合、平面と線分は平行であるため交点なし
		return false;
	}

	// tの分子部分の計算（平面上の点と線分の始点のベクトルの内積）
	float numerator = a * (x0 - x1) + b * (y0 - y1) + c * (z0 - z1);

	// tの計算（線分上のどの位置に交点があるかを示すパラメータ）
	float t = numerator / denominator;
	if(t < 0.0f || t > 1.0f) {
		// tが0から1の範囲外であれば、交点は線分上に存在しない
		return false;
	}

	// 交点の計算（線分上の点のパラメータ表示にtを代入）
	h.x = (1 - t) * x1 + t * x2;
	h.y = (1 - t) * y1 + t * y2;
	h.z = (1 - t) * z1 + t * z2;


	return true;
}

// gptを元に自分で作りました
bool CheckHitTriangleSegment(VECTOR p1a, VECTOR p1b, VECTOR p2a, VECTOR p2b, VECTOR p2c, VECTOR& h, float& t) {
	
	// ①平面の方程式を求める
	// 三角形の法線ベクトルの成分
	// 外積n = AB x AC
	// plane normalでpn
	VECTOR pn = VCross(VSub(p2b, p2a), VSub(p2c, p2a));

	if (pn.x == 0.0f && pn.y == 0.0f && pn.z == 0.0f) {
		return false;
	}

	// 平面の方程式
	// ax + by + cz + d = 0
	// d = -(pn.x * p2a.x + pn.y * p2a.y + pn.z * p2a.z)
	float d = -(pn.x * p2a.x + pn.y * p2a.y + pn.z * p2a.z);

	// ②線分が平面を横切るかどうかを判定する
	// 線分平面のどちらにあるか
	float a = pn.x * p1a.x + pn.y * p1a.y + pn.z * p1a.z + d;
	float b = pn.x * p1b.x + pn.y * p1b.y + pn.z * p1b.z + d;

	// a,bの符号が異なる場合、線分は平面を横切る
	if(a * b >= 0) {
		return false;
	}

	// ③線分と平面の交点を求める
	// 線分の方向ベクトル
	VECTOR v = VSub(p1b, p1a);

	// 線分上のP(t) = p1 + t * v が平面上にあるためのｔを求める
	// pn.x * (p1a.x + t(p1b.x - p1a.x)) + pn.y * (p1a.y + t(p1b.y - p1a.y)) 
	//		+ pn.z * (p1a.z + t(p1b.z - p1a.z)) + d = 0
	// 
	//		-(pn.x * p1a.x + pn.y * p1a.y + pn.z * p1a.z + d) 
	// t = ----------------------------------------------------
	//			 pn.x * v.x + pn.y * v.y + pn.z * v.z

	float denominator = pn.x * v.x + pn.y * v.y + pn.z * v.z;
	if (denominator == 0.0f) {
		return false;
	}

	t =  -a / denominator;

	// tが0から1の範囲外であれば、交点は線分上に存在しない
	if(t < 0.0f || t > 1.0f) {
		return false;
	}

	// 交点の計算（線分上の点のパラメータ表示にtを代入）
	h.x = p1a.x + t * v.x;
	h.y = p1a.y + t * v.y;
	h.z = p1a.z + t * v.z;

	return true;
}