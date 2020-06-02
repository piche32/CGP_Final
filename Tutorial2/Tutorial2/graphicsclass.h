#pragma once
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_ 

//#include <windows.h> 
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
//#include "colorshaderclass.h"
#include "textureshaderclass.h"

// Globals 
const bool FULL_SCREEN = false; //const bool FULL_SCREEN =  false; Tutorial1-2-1 => Tutorial1-3���� true�� �ٲٸ� ������ ���.. D3DClass�� EndScene���� ����ؼ� �׷� �� ����.
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f; 

class GraphicsClass
{
public: 
	GraphicsClass(); 
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

		 bool Initialize(int, int, HWND);
		 void Shutdown(); 
		 bool Frame();

private: 
	bool Render(float); //bool Render(float*) HW2 - 3
	D3DClass* m_D3D;

private:
	CameraClass* m_Camera; 
	ModelClass* m_Model;
//	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;

	//HW2 - 4
public:
	TextureShaderClass* getTextureShader();
	D3DClass* getD3D();

	//HW2 - 3
	ModelClass* m_plane_Model;
	int m_ModelIndex, m_ModelMax;
	
};

#endif