# Readme
DX ライブラリと C++ 言語で作成した AIの研究プジェクトです。

# 開発環境
Windows 11  
Visual Studio Community 2022

# 使用モデル
モデル：変わったヒルチャール
提供：miHoYo様

# 使用ライブラリ
[DX ライブラリ](https://dxlib.xsrv.jp/) 

# プロジェクト構成と起動方法
下記 DxLib ディレクトリ内に [DX ライブラリ Windows版 VisualStudio(C++)用](https://dxlib.xsrv.jp/DxLib/DxLib_VC3_24d.zip) を DownLoad して解凍後の ***プロジェクトに追加すべきファイル_VC用*** ディレクトリの内容を全てコピーします。
<pre>
.
以下担当箇所になります
├── DxLib(ライブラリ用ディレクトリ)
│
├── AppFrame(自作ゲームフレームワーク用のライブラリ Project)
│   └─source
│     ├─Collision
│     │   ├── Collision.cpp(当たり判定用の関数が入っているクラス)
│     │   └── Collision.h
│     │    
│     │─GamePad    
│     │   ├── GamePad.cpp(コントローラーの入力クラス)
│     │   └── GamePad.h
│     │    
│     └──Mymath   
│        ├── mymath.cpp(よく使う計算関数が入っているクラス)
│        └──mymath.h
│  
└── Game(ゲーム本体の Project)
    │
    ├── Game
    │   │
    │   ├── Res(ゲーム用リソースディレクトリ)
    │   │
    │   └── Source(ソースファイル)
    │       ├── Camera.cpp(極座標で動かしてるカメラクラス)
    │       ├── Camera.h
    │       ├── ModeGame.cpp(ゲームのメインのクラス)
    │       ├── ModeGame.h
    │       ├── ObjectBase.cpp(プレイヤーや敵などのオブジェクトのもとになるクラス)
    │       ├── ObjectBase.h
    │       ├── ObjectManager.cpp(ObjectBaseを継承して作られたクラスを管理するクラス)
    │       ├── ObjectManager.h
    │       ├── Player.cpp(ターゲットを動かすクラス。敵の動きなどが完成したらシューティングゲームとして使えるように)
    │       ├── Player.h
    │       ├── UI.cpp(敵の動きなどが完成し,シューティングゲームとして使うときに敵の体力表示用)
    │       ├── UI.h
    │       ├── Enemy.cpp(A-starで動かす敵のクラス)
    │       ├── Enemy.h
    │       ├── Astar.cpp（Astarアルゴリズムのクラス。ここの関数をEnemy.cppで使う）
    │       └── Astar.h
    │
    └── Game.sln(こちらを起動して下さい)
</pre>

# 操作方法
Zキーでマスを探す手順を+1します。

# exeダウンロードは以下リンクからお願いします。
[ダウンロードはこちら](https://drive.google.com/drive/folders/1cC4KRzBNCDLQfH-SwzR3iZjvAp8r1TgH?usp=sharing)