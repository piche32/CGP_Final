#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "modelclass.h"
#include "d3dclass.h"
#include "CollisionBoxClass.h"

class GameObjectClass {
private:
	ModelClass* m_model;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_rot;
	CollisionBoxClass* m_coll;

protected:
	D3DXVECTOR3 m_pos;

public:
	GameObjectClass();
	GameObjectClass(const GameObjectClass&);
	virtual ~GameObjectClass();

	ModelClass* GetModel();
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetScale();
	D3DXVECTOR3 GetRot();
	CollisionBoxClass* GetColl();


	void SetModel(ModelClass*);
	virtual void SetPos(D3DXVECTOR3);
	virtual void SetPos(float, float, float);
	void SetScale(D3DXVECTOR3);
	void SetScale(float x, float y, float z);
	void SetRot(D3DXVECTOR3);

	virtual bool Initialize(ID3D11Device*, ModelClass*, CollisionBoxClass*, HWND);
	virtual void Shutdown();
};
#endif

