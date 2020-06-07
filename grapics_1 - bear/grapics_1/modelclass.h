#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_
#include <d3d11.h>
#include <d3dx10math.h>
#include "textureclass.h"
#include <fstream>
using namespace std;

class ModelClass
{
private:
	struct VertexType //vertice textcoords normal
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};
	struct ModelType //face
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	typedef struct
	{
		float x, y, z;
	}VertexType_obj;

	typedef struct
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	}FaceType_obj;
public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*);	//로딩될 모델의 파일 이름 문자열을 입력 받음.
	bool Initialize(ID3D11Device* , WCHAR* );	//로딩될 모델의 파일 이름 문자열을 입력 받음.

	void Shutdown();
	void Render(ID3D11DeviceContext*);

	bool LoadModel(char*);
	void ReleaseModel();

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	void SetPosition(float, float, float);
	void GetPosition(float&, float&, float&);

private:
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool InitializeBuffers(ID3D11Device*);
	
	bool InitializeBuffers_Board(ID3D11Device*);

	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool ReadFileCounts(char*, int&, int&, int&, int&);
	bool LoadDataStructures(char*, int, int, int, int);


private:
	TextureClass* m_Texture;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	ModelType* m_model;

	float m_positionX;
	float m_positionY;
	float m_positionZ;

};
#endif