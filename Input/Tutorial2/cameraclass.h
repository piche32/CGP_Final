#pragma once
#ifndef _CAMERACLASS_H_ 
#define _CAMERACLASS_H_ 

#include <d3dx10math.h> 
#include <DirectXMath.h>
class CameraClass {
public: 
	CameraClass(); 
	CameraClass(const CameraClass&); 
	~CameraClass();

		 void SetPosition(float, float, float); 
		 void SetRotation(float, float, float);
		 void SetLookAt(D3DXVECTOR3 lookAt);


		 D3DXVECTOR3 GetPosition(); 
		 D3DXVECTOR3 GetRotation();

		 void Render(); 
		 void GetViewMatrix(D3DXMATRIX&);
		 float m_yaw, m_pitch;
		 D3DXVECTOR3 GetLookAt();

		D3DXVECTOR3 GetRightDirection();
		D3DXVECTOR3 GetForwardDirection();


private:  
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXMATRIX m_viewMatrix;
	D3DXVECTOR3 m_lookAt, m_front, m_right;
};

#endif