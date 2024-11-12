#include "ObjectManager.h"
#include "Enemy.h" 
#include "Player.h"
#include "ModeGameClear.h"

ObjectManager* ObjectManager::ObjInstance = new ObjectManager();
ObjectManager::ObjectManager() {

	ObjInstance = this;

	// オブジェクトの追加
	AddObject(new Enemy);
	// ここコメントアウト外せば敵増やせる
	//AddObject(new Enemy);
	AddObject(new Player);

	isClear = false;
}

ObjectManager::~ObjectManager() {
}

void ObjectManager::AddObject(ObjectBase* object) {

	m_objects.push_back(object);
}

bool ObjectManager::Initialize() {

	for (auto object : m_objects) {
		object->Initialize();
	}

	return true;
}

bool ObjectManager::Update() {

	for (auto object : m_objects) {
		object->Process();
	}

	// 敵の体力が0ならゲームクリアへ
	if (Enemy::GetEnInstance()->GetEnemyHP() <= 0) {

		isClear = true;
	}

	return true;
}

bool ObjectManager::Draw() {

	for (auto object : m_objects) {
		object->Render(1);
	}

	return true;
}

void ObjectManager::RemoveObject(ObjectBase* obj) {

	for (auto it = m_objects.begin(); it != m_objects.end(); ++it) {
		if (*it == obj) {
			m_objects.erase(it);
			break;
		}
	}
}

void ObjectManager::Clear() {

	m_objects.clear();
}