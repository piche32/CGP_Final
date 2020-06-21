#include "playerClass.h"

PlayerClass::PlayerClass():GameObjectClass() {
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_front = D3DXVECTOR3(0.0f, 0.0f, 1.0f); 
	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_pastPos = m_pos;

	m_defaultUp = m_up;
	m_defaultFront = m_front;
	m_defaultRight = m_right;
	m_lookAt = m_front;
}

PlayerClass::PlayerClass(const PlayerClass& other) {}

PlayerClass::~PlayerClass() {}

void PlayerClass::SetPos(D3DXVECTOR3 pos) {
	m_pastPos = m_pos;
	m_pos = pos;
	GetColl()->SetPos(m_pos);
	return;
}

void PlayerClass::SetPos(float x, float y, float z) {
	m_pastPos = m_pos;
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;

	GetColl()->SetPos(m_pos);
	return;
}void PlayerClass::SetPastPos(D3DXVECTOR3 pos) {
	m_pastPos = pos;
	return;
}

void PlayerClass::SetPastPos(float x, float y, float z) {
	m_pastPos.x = x;
	m_pastPos.y = y;
	m_pastPos.z = z;

	return;
}
D3DXVECTOR3 PlayerClass::GetFront() {
	D3DXVECTOR3 pos = m_pos;
	D3DXVec3Normalize(&m_front, &(m_lookAt - pos));

	return m_front;
}

D3DXVECTOR3 PlayerClass::GetRight() {
	D3DXVec3Cross(&m_right, &m_up, &m_front);
	D3DXVec3Normalize(&m_right, &m_right);

	return m_right;
}

//bool PlayerClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename, HWND hwnd) { 	return true; }
//void PlayerClass::Shutdown() {}

void PlayerClass::SetLookAt(D3DXVECTOR3 lookAt) {
	m_lookAt = lookAt;
	return;
}
D3DXVECTOR3 PlayerClass::GetLookAt() {
	return m_lookAt;
}

D3DXVECTOR3 PlayerClass::GetPastPos() {
	return m_pastPos;
}


