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
	D3DXVECTOR3 up, position, lookAt; 
	float yaw, pitch, roll; 
	D3DXMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up = m_up;
	// Setup the position of the camera in the world. 
	position = m_pos;

	lookAt = m_lookAt; //밑에 주석해제하면 이거 잠그기
	//D3DXVec3Normalize(&lookAt, &m_lookAt); //이상하면 이거 풀기
	// Setup where the camera is looking by default.
	/*lookAt.x = m_lookAt.x; 
	lookAt.y = m_lookAt.y;
	lookAt.z = m_lookAt.z;*/

	
	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians. 
	pitch = m_pitch;//m_rot.x * 0.0174532925f; 
	yaw = m_yaw;//m_rot.y * 0.0174532925f; 
	roll  = m_rot.z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values. 
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll); 

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix); 

  // Translate the rotated camera position to the location of the viewer.  
	lookAt = position + lookAt;

  // Finally create the view matrix from the three updated vectors. 
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up); 
	
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
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 rightVector;
	D3DXVec3Cross(&rightVector, &up, &m_front);
	D3DXVec3Normalize(&m_right, &rightVector);

	return m_right;

}

D3DXVECTOR3 CameraClass::GetForwardDirection() {
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 lookAt = GetLookAt();

	D3DXVec3Normalize(&m_front, &(lookAt - pos));
	
	return m_front;

}

void CameraClass::SetLookAt(D3DXVECTOR3 lookAt) {
	m_lookAt = lookAt;
	return;
}