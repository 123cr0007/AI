#pragma once
#include "ObjectBase.h"
#include "appframe.h"

class ObjectManager : public ObjectBase {
public:

	// インスタンス
	static ObjectManager* ObjInstance;
	static ObjectManager* GetObjInstance() { return (ObjectManager*)ObjInstance; }

	ObjectManager();
	~ObjectManager();

	bool Initialize();
	bool Update();
	bool Draw();

	void AddObject(ObjectBase* obj);
	void RemoveObject(ObjectBase* obj);

	void Clear();

	// ゲッター
	bool GetIsClear() { return isClear; }

	// セッター
	void SetIsClear(bool flag) { isClear = flag; }

private:
	std::vector<ObjectBase*> m_objects;
	bool isClear;
};