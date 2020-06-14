#include "GameObject.h"

GameObjectClass::GameObjectClass() {
	m_model = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
void GameObjectClass::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
	return;
}
void GameObjectClass::SetRot(D3DXVECTOR3 rot){
	m_rot = rot;
	return;
}

bool GameObjectClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename, HWND hwnd) {
	bool result;

	m_model = new ModelClass;
	if (!m_model) { return false; }

	result = m_model->Initialize(device, modelFilename, textureFilename);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	return true;
}

void GameObjectClass::Shutdown() {
	m_model->Shutdown();
	delete m_model;
	m_model = 0;

	return;
}