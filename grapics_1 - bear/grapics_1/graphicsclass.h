#pragma once
#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////

#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "textureshaderclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass(float, float);
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	void ChangeTextureMode(int);

private:
	bool Render(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera , m_Cameraa;
	ModelClass* m_Model;
	TextureShaderClass* m_TextureShader;
	TextureShaderClass* m_TextureShader2;
	TextureShaderClass* m_TextureShader3;
	TextureShaderClass* m_TextureShader4;

	ModelClass *m_Model1, *m_Model2, *m_Model3, *board;

	//TextureShaderClass* m_TextureShader;
public:
	float camera_x;
	float camera_y;
	float camera_z;



};
#endif