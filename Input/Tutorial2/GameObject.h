#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "modelclass.h"
#include "d3dclass.h"

class GameObjectClass {
private:
	ModelClass* m_model;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_rot;

public:
	GameObjectClass();
	GameObjectClass(const GameObjectClass&);
	virtual ~GameObjectClass();

	ModelClass* GetModel();
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetScale();
	D3DXVECTOR3 GetRot();

	void SetModel(ModelClass*);
	void SetPos(D3DXVECTOR3);
	void SetScale(D3DXVECTOR3);
	void SetRot(D3DXVECTOR3);

	virtual bool Initialize(ID3D11Device*, char*, WCHAR*, HWND);
	virtual void Shutdown();
};
#endif

