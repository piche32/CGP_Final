#pragma once
#ifndef _PLAYERCLASS_H_
#define _PLAYERSCLASS_H_ 

#include "modelclass.h"
#include "d3dclass.h"
#include "GameObject.h"

class PlayerClass : public GameObjectClass {
private:
	D3DXVECTOR3 m_up, m_front, m_right, m_lookAt;
	D3DXVECTOR3 m_defaultUp, m_defaultFront, m_defaultRight;

public:
	PlayerClass();
	PlayerClass(const PlayerClass&);
	~PlayerClass();
	
	D3DXVECTOR3 GetFront();
	D3DXVECTOR3 GetRight();
	D3DXVECTOR3 GetLookAt();
	void SetLookAt(D3DXVECTOR3);

//	virtual bool Initialize(ID3D11Device*, char*, WCHAR*, HWND);
//	virtual void Shutdown();

};

#endif