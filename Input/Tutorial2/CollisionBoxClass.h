#pragma once
#ifndef _COLLISIONBOXCLASS_H_
#define _COLLISIONBOXCLASS_H_

#include "d3dclass.h"
#include "modelclass.h"

class CollisionBoxClass {
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_dist;
	D3DXVECTOR3 m_maxPos;
	D3DXVECTOR3 m_minPos;
	bool isTrigger;


public:
	CollisionBoxClass();
	CollisionBoxClass(const CollisionBoxClass&);
	~CollisionBoxClass();

	bool Initialize(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
	void Shutdown();

	void SetPos(D3DXVECTOR3);
	void SetScale(D3DXVECTOR3);
	void SetDist(D3DXVECTOR3);
	void SetTrigger(bool);

	void Render(D3DXMATRIX*, D3DXMATRIX*);
	bool Collision(CollisionBoxClass* other);

	bool Initialize();
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetScale();
	D3DXVECTOR3 GetDist();
	void SetMinMax();
	void GetMinMax(D3DXVECTOR3&, D3DXVECTOR3&);
};

#endif