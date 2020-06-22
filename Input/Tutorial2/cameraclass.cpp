#include "cameraclass.h"

CameraClass::CameraClass() {
	
	m_lookAt.x = 0.0f;
	m_lookAt.y = 0.0f;
	m_lookAt.z = 1.0f;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_front = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_yaw = m_rot.y * 0.0174532925f;
	m_pitch = m_rot.x * 0.0174532925f;
	m_roll = m_rot.z * 0.0174532925f;

	m_targetDist = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	isFPS = false;
}

CameraClass::CameraClass(const CameraClass& other) { }
CameraClass::~CameraClass() { }
void CameraClass::SetPosition(float x, float y, float z) {
	m_pos.x = x; 
	m_pos.y = y;
	m_pos.z = z;

	return; 
}

void CameraClass::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
	return;
}

void CameraClass::SetRotation(float x, float y, float z) { 
	m_rot.x = x;
	m_rot.y = y;
	m_rot.z = z;

	return;
}

void CameraClass::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
	return;
}

D3DXVECTOR3 CameraClass::GetPosition() {
	return m_pos;
}

D3DXVECTOR3 CameraClass::GetRotation() { 
	return m_rot;
}

void CameraClass::Render() {


	D3DXMATRIX rotationMatrix;
	D3DXVECTOR3 lookAt = m_front;
	D3DXVECTOR3 up = m_up;

	//if (isFPS == true) lookAt = GetForwardDirection();
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, m_yaw, m_pitch, m_roll);

	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	lookAt += m_pos;

	D3DXMatrixLookAtLH(&m_viewMatrix, &m_pos, &lookAt, &up);

	return;
}

void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix) {
	viewMatrix = m_viewMatrix;
	return; 
}

D3DXVECTOR3 CameraClass::GetLookAt() {
	return m_lookAt;
}

D3DXVECTOR3 CameraClass::GetRightDirection() {
	D3DXVec3Cross(&m_right, &m_up, &m_front);
	D3DXVec3Normalize(&m_right, &m_right);

	return m_right;

}

D3DXVECTOR3 CameraClass::GetForwardDirection() {
	D3DXVec3Normalize(&m_front, &(m_lookAt - m_pos));
	
	return m_front;

}


void CameraClass::SetLookAt(D3DXVECTOR3 lookAt) {
	m_lookAt = lookAt;
	return;
}

void CameraClass::SetFPS() {
	isFPS = !isFPS;
	return;
}

bool CameraClass::GetIsFPS() {
	return isFPS;
}

void CameraClass::SetTargetDist(D3DXVECTOR3 dist) {
	m_targetDist = dist;
	return;
}

D3DXVECTOR3 CameraClass::GetTargetDist() {
	return m_targetDist;
}

void CameraClass::SetYaw(float yaw) {
	m_yaw = yaw;
	return;
}

float CameraClass::GetYaw() {
	return m_yaw;
}
