#pragma once
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_ 

//#include <windows.h> 
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
//#include "colorshaderclass.h"
//#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "textclass.h"
#include "Fogshaderclass.h"
#include "playerClass.h"
#include "GameObject.h"

#include "Minimapclass.h"
#include "Terrainclass.h"
#include "timerclass.h"
#include "positionclass.h"

#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

// Globals 
const bool FULL_SCREEN = false; //const bool FULL_SCREEN =  false; Tutorial1-2-1 => Tutorial1-3���� true�� �ٲٸ� ������ ���.. D3DClass�� EndScene���� ����ؼ� �׷� �� ����.
const bool VSYNC_ENABLED = false;
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
		 //bool Frame();
		 bool Frame(int, int, int, int, float, int, int);

private: 
	bool Render(float); //bool Render(float*) HW2 - 3
	D3DClass* m_D3D;

private:
	CameraClass* m_Camera; 
	ModelClass* m_Model;
//	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	BitmapClass* m_Bitmap;
	TextClass* m_Text;
	D3DXMATRIX m_baseViewMatrix;

	FogShaderClass* m_FogShader;

	GameObjectClass* m_player;

	MiniMapClass* m_MiniMap;
	TerrainClass* m_Terrain;
	TimerClass* m_Time;
	PositionClass* m_Position;


	//HW2 - 4
public:
	//TextureShaderClass* getTextureShader();
	D3DClass* getD3D();

	//HW2 - 3
	ModelClass* m_plane_Model, *m_Cube;
	int m_ModelIndex, m_ModelMax, m_ModelVertex;
	
	ModelClass* m_wallModel;
	GameObjectClass* m_wall;
	int wallNum;

	ModelClass* m_starModel;
	GameObjectClass* m_star;
	int m_starNum;


	//HW3 - 4
	void cameraMove(const char);
	void playerMove(const char);
	void MouseInput(const DIMOUSESTATE);

	bool HandleInput(float);


	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;

	//HW3 - 3
	int countPolygons();

	void SetPos(D3DXMATRIX*, D3DXMATRIX*, D3DXVECTOR3);
	void SetScale(D3DXMATRIX*, D3DXMATRIX*, D3DXVECTOR3);
	void SetRotY(D3DXMATRIX*, D3DXVECTOR3);


	void SetCameraView();
	bool GetCameraView();

	float move;	//��ֹ� �����̴� ��
	float move_pp; //������ ��ֹ� �����̴� ��
	float move_boo; //�� ��ֹ� �����̴� ��

	float speed10;	//���ϰ� ���ִ� ��

	int cnt;	//fps ����
	int cnt1;	//fps ����
	int cnt2;	//fps ����


	void playerCollision(); //player �ٸ� ������Ʈ �浹üũ
	void eatStar();
};
#endif