#pragma once
#ifndef _PLAYERCLASS_H_
#define _PLAYERSCLASS_H_ 

#include "modelclass.h"
#include "d3dclass.h"
#include "GameObject.h"

class PlayerClass : public GameObjectClass {
private:

public:
	PlayerClass();
	PlayerClass(const PlayerClass&);
	~PlayerClass();
	

//	virtual bool Initialize(ID3D11Device*, char*, WCHAR*, HWND);
//	virtual void Shutdown();

};

#endif