#include "GameObject.h"

GameObjectClass::GameObjectClass() {
	m_model = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_coll = nullptr;
	isActive = true;
}

GameObjectClass::GameObjectClass(const GameObjectClass&) {}
GameObjectClass::~GameObjectClass() {}

ModelClass* GameObjectClass::GetModel() { return m_model; }
D3DXVECTOR3 GameObjectClass::GetPos() { return m_pos; }
D3DXVECTOR3 GameObjectClass::GetScale() { return m_scale; }
D3DXVECTOR3 GameObjectClass::GetRot() { return m_rot; }

void GameObjectClass::SetModel(ModelClass* model) {
	m_model = model;
	return;
}
void GameObjectClass::SetPos(D3DXVECTOR3 pos) {
	m_pos = pos;
	return;
}
void GameObjectClass::SetPos(float x, float y, float z) {
	m_pos = D3DXVECTOR3(x, y, z);
	m_coll->SetPos(m_pos);
	return;
}
void GameObjectClass::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
	return;
}

void GameObjectClass::SetScale(float x, float y, float z) {
	m_scale = D3DXVECTOR3(x, y, z);
	return;
}

void GameObjectClass::SetRot(D3DXVECTOR3 rot){
	m_rot = rot;
	return;
}

void GameObjectClass::SetRot(float x, float y, float z ) {
	m_rot = D3DXVECTOR3(x, y, z);
	return;
}

bool GameObjectClass::Initialize(ID3D11Device* device, ModelClass* model, CollisionBoxClass* coll, HWND hwnd) {

	m_model = model;
	if (m_model == nullptr) return false;

	m_coll = coll;
	if (m_coll == nullptr) return false;

	return true;
}

void GameObjectClass::Shutdown() {
	if (m_model)
	{
		m_model->Shutdown();
		delete m_model;
		m_model = 0;
	}

	if (m_coll) {
		m_coll->Shutdown();
		delete m_coll;
		m_coll = 0;
	}

	return;
}

CollisionBoxClass* GameObjectClass::GetColl() {
	return m_coll;
}

void GameObjectClass::SetActive(bool value) {
	isActive = value;
	return;
}

bool GameObjectClass::GetActive(){
	return isActive;
}
