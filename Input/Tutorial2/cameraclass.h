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
		void SetPosition(D3DXVECTOR3);
		void SetRotation(float, float, float);
		void SetRotation(D3DXVECTOR3);
		D3DXVECTOR3 GetPosition();
		D3DXVECTOR3 GetRotation();



		void SetLookAt(D3DXVECTOR3 lookAt);

		void Render(); 
		void GetViewMatrix(D3DXMATRIX&);
		
		D3DXVECTOR3 GetLookAt();

		D3DXVECTOR3 GetRightDirection();
		D3DXVECTOR3 GetForwardDirection();
		


private:  
	//float m_positionX, m_positionY, m_positionZ;
	//float m_rotationX, m_rotationY, m_rotationZ;
	D3DXMATRIX m_viewMatrix;
	D3DXVECTOR3 m_lookAt; //보는 대상
	D3DXVECTOR3 m_front, m_right, m_pos, m_rot, m_up;
	float m_yaw, m_pitch, m_roll;
};

#endif