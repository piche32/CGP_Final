#ifndef _MODELCLASS_H_ 
#define _MODELCLASS_H_ 

#include <d3d11.h> 
#include <d3dx10math.h> 
#include <fstream>

#include "textureclass.h"

using namespace std;

class ModelClass 
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position; 
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;

	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct FaceType	//HW2 - 1
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	};

public:
	ModelClass(); 
	ModelClass(const ModelClass&); 
	~ModelClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	ID3D11ShaderResourceView* GetTexture();
	void Shutdown(); 
	void Render(ID3D11DeviceContext*);
	bool LoadModel(char*);
	void ReleaseModel();

	int GetIndexCount();

private: 
	bool InitializeBuffers(ID3D11Device*); 
	void ShutdownBuffers(); 
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	TextureClass* m_Texture;
	ModelType* m_model;



private:
	bool ReadFileCounts(char*, int&, int&, int&, int&);
	bool LoadDataStructures(char*, int, int, int, int);

	//HW2 - 3
	//int m_plane_vertexCount, m_plane_indexCount;
//	ID3D11Buffer *m_plane_vertexBuffer, *m_plane_indexBuffer;
//public:
//	int GetplaneIndexCount();
};
#endif 