
#include "graphicsclass.h"


GraphicsClass::GraphicsClass(float x, float z)
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_TextureShader = 0;
	m_TextureShader2 = 0;
	m_TextureShader3 = 0;

	camera_x= 0.0f;
	camera_y= 5.0f;
	camera_z= -40.0f;

}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}
	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN,
		SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 5.0f, -40.0f);
	m_Camera->SetPosition(camera_x, camera_y, camera_z);


	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}
	// Initialize the model object.
	//result = m_Model->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/seafloor.dds");
	result = m_Model->Initialize(m_D3D->GetDevice(), "../Engine/data/MegaMushroom.obj", L"../Engine/data/lambert15.png");
	


	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	m_Model1 = new ModelClass;
	if (!m_Model1)
	{
		return false;
	}

	result = m_Model1->Initialize(m_D3D->GetDevice(), "../Engine/data/Hammer.obj", L"../Engine/data/Hammer.png");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	

	m_Model2 = new ModelClass;
	if (!m_Model2)
	{
		return false;
	}

	result = m_Model2->Initialize(m_D3D->GetDevice(), "../Engine/data/star.obj", L"../Engine/data/star.png");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	board = new ModelClass;
	if (!board) {
		return false;
	}

	result = board->Initialize(m_D3D->GetDevice(), L"../Engine/data/seafloor.dds");


	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader) {
		return false;
	}
	// Initialize the color shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);

	m_TextureShader2 = new TextureShaderClass;
	if (!m_TextureShader2) {
		return false;
	}
	// Initialize the color shader object.
	result = m_TextureShader2->Initialize(m_D3D->GetDevice(), hwnd);

	m_TextureShader3 = new TextureShaderClass;
	if (!m_TextureShader3) {
		return false;
	}
	// Initialize the color shader object.
	result = m_TextureShader3->Initialize(m_D3D->GetDevice(), hwnd);

	m_TextureShader4 = new TextureShaderClass;
	if (!m_TextureShader4) {
		return false;
	}
	// Initialize the color shader object.
	result = m_TextureShader4->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}
	bool Initialize(int, int, HWND);

	return true;

}


void GraphicsClass::Shutdown()
{

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}


	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;
	m_Camera->SetRotation(1, 1, 1);
	m_Camera->SetPosition(camera_x, camera_y, camera_z);
	static float rotation = 0.0f;
	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.01f;
	if (rotation > 360.0f)
	{
		rotation = 360.0f;
	}
	// 그래픽스 장면을 그림. 
	//(System::Frame()함수가 그래픽스클래스Frame()을 호출.)->Frame()함수가 Render()함수 호출
	result = Render(rotation);

	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render(float rotation)
{

	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, model1, model2, model3;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	D3DXMatrixRotationY(&worldMatrix, rotation);
	D3DXMatrixTranslation(&model1, 0.0f ,-7.0f, 10.0f);	//파라솔
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &model1);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture());

	m_D3D->GetWorldMatrix(model2);
	D3DXMatrixRotationY(&worldMatrix, rotation);
	D3DXMatrixTranslation(&model2, -10.0f, -2.0f, 40.0f);	//꽃
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &model2);

	m_Model1->Render(m_D3D->GetDeviceContext());
	result = m_TextureShader2->Render(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model1->GetTexture());
	if (!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixRotationY(&worldMatrix, rotation);
	D3DXMatrixTranslation(&model3, 7.0f, -4.0f, 10.0f);	//별

	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &model3);


	m_Model2->Render(m_D3D->GetDeviceContext());

	result = m_TextureShader3->Render(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model2->GetTexture());


	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixTranslation(&worldMatrix, 0.0f, -10.0f, 20.0f);	// 배경


	board->Render(m_D3D->GetDeviceContext());

	result = m_TextureShader4->Render(m_D3D->GetDeviceContext(), board->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		board->GetTexture());
	if (!board)
	{
		return false;
	}

	//m_D3D->GetWorldMatrix(worldMatrix);
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;


}

void GraphicsClass::ChangeTextureMode(int i) {
	
	m_TextureShader4->textureMode = i;
	m_TextureShader4->ChangeTexture();
}






