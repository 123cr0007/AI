#pragma once
#pragma once
// ObjectBase クラスの定義(Load 関数)で TCHAR 型を宣言(使用)しているのでインクルード
#include <tchar.h>
#include <unordered_map>
#include <tuple>
#include <string>

#include "DxLib.h"

// Game クラスと合わせるやつ
class ObjectBase {
public:
    ObjectBase();
    virtual ~ObjectBase();

    // これを自機と敵のクラス側で override して、それぞれクラス専用の関数書き換えたりする
    virtual bool Initialize();
    virtual bool Process();
    // type=0の時2Dを描画,type=1の時3Dを描画,tupe = 2の時ビルボード描画
    virtual bool Render(int type);

    virtual void End() { valid = false; }

    // キャッシュしているハンドルを解放する
    virtual bool DeleteLoadType();

    // typeに読み込みファイルに応じた番号を入れる。0:画像ファイル 1:MV1ファイル
    int Load(const TCHAR* fileName, int type);
    virtual bool Rend(int type);


    // ゲッター
    int GetX() const { return x; }
    int GetY() const { return y; }
    VECTOR GetPos() { return vPos; };
    VECTOR GetDir() { return vDir; };
    float GetRadius() const { return collision_r; };
    bool IsValid() const { return valid; }
    int GetEffect() { return ef_type;}

    //セッター
    void SetPos(VECTOR pos) { vPos = pos; };

protected:
    // 取り合えず描画に必要な最低限の変数
    // (DrawGraph が必要としている)
    int handle;
    int ef_type;
    //いろんなところで使える汎用変数
    int x;
    int y;
    int gSize;  // ビルボード描画用の画像サイズ
    float gAngle;    // ビルボード描画用の角度
    VECTOR vPos;       //
    VECTOR vDir;       //
    VECTOR capsuleTop;
    VECTOR capsuleRow;

    float collision_r;     //キャラの半径
    float ChHight;          //キャラの高さ（カプセル作るときの）

    
    bool valid;

    std::string fileName;
    
    static std::unordered_map<std::string, std::tuple<int>> handleCache;
};