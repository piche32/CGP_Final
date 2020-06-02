#include "graphicsclass.h" 
GraphicsClass::GraphicsClass() {
	m_Camera = 0;
	m_Model = 0;
//	m_ColorShader = 0;
	m_TextureShader = 0;
	m_D3D = 0;

	//HW2 - 3
	m_plane_Model = 0;
	m_ModelIndex = 0;
	m_ModelMax = 3;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other) { }

GraphicsClass::~GraphicsClass() { 
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	 
	//Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D) { return false; }

	//Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}
	/*  HW2 - 3
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}*/

	// Create the camera object. 
	m_Camera = new CameraClass; 
	if(!m_Camera)  {   return false;  } 

 // Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f); //m_Camera->SetPosition(0.0f, 0.0f, -10.0f); tutorial2 - 1 수정 HW2 - 4
	
	// Create the model object.
	m_Model = new ModelClass[m_ModelMax]; 
	if(!m_Model)  {   return false;  } 

	//HW2 - 3
	m_plane_Model = new ModelClass;
	if (!m_plane_Model) {
		return false;
	}

  // Initialize the model object. 
	result = m_Model[0].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/Cube.obj", (WCHAR*)L"../Tutorial2/data/seafloor.dds"); //error 시 여기 확인
	if(!result)  {  
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK); 
		return false;
	} 

	result = m_Model[1].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/Manzana.obj", (WCHAR*)L"../Tutorial2/data/Tex_Manzana.dds"); //error 시 여기 확인
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	result = m_Model[2].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/star.obj", (WCHAR*)L"../Tutorial2/data/star.dds"); //error 시 여기 확인
		//(char*)"../Tutorial2/data/chair.obj", (WCHAR*)L"../Tutorial2/data/chair.dds"); //error 시 여기 확인
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	//HW2 - 3
	result = m_plane_Model->Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/plane.obj", (WCHAR*)L"../Tutorial2/data/brick.dds"); //error 시 여기 확인
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader) {   return false;  }

 // // Initialize the color shader object.
	//result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd); 
	//if(!result)  {
	//	MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK); 
	//	return false;  
	//} 


		//HW2 - 3
	// Initialize the color shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	
	}
	return true;
}

void GraphicsClass::Shutdown() {

	
	if (m_D3D) {
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	
	//// Release the color shader object.
	//if(m_ColorShader)  { 
	//	m_ColorShader->Shutdown();
	//	delete m_ColorShader; 
	//	m_ColorShader = 0;  
	//} 

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

  // Release the model object. 

	//HW2 - 3
	for (int i = 0; i < m_ModelMax; i++) {
		m_Model[i].Shutdown();
		delete[] m_Model;
		m_Model = 0;

	}


	/*if(m_Model)  {   
		m_Model->Shutdown(); 
		delete m_Model;  
		m_Model = 0; 
	} */

	//HW2 - 3
	if (m_plane_Model){
		m_plane_Model->Shutdown();
		delete m_plane_Model;
		m_plane_Model;
		}

  // Release the camera object.
	if(m_Camera)  { 
		delete m_Camera; 
		m_Camera = 0;  
	} 

	return;
}
bool GraphicsClass::Frame() {
	bool result;

	static float rotation = 0;
	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.01f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	//Render the graphics scene.
	result = Render(rotation);
	if (!result) {
		return false;
	}
	return true;
}
//HW2 - 3
bool GraphicsClass::Render(float rotation) {
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix, translateMatrix; 
	bool result;

	//Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f); //m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f); Tutorial1-3-1 //HW2 - 3


	

	// Generate the view matrix based on the camera's position.
	m_Camera->Render(); 


	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);


		// Rotate the world matrix by the rotation value so that the triangle will spin.

		D3DXMatrixRotationY(&worldMatrix, rotation); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixTranslation(&translateMatrix, -2.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
	  // Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[0].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

	 // // Render the model using the color shader. 
		//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, 
		//	viewMatrix, projectionMatrix);

		// Render the model using the texture shader.
		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model[0].GetIndexCount(),
			worldMatrix, viewMatrix, projectionMatrix, m_Model[0].GetTexture());
		if (!result) { return false; }


		// Rotate the world matrix by the rotation value so that the triangle will spin.

		D3DXMatrixRotationY(&worldMatrix, rotation); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[1].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

	 // // Render the model using the color shader. 
		//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, 
		//	viewMatrix, projectionMatrix);

		// Render the model using the texture shader.
		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model[1].GetIndexCount(),
			worldMatrix, viewMatrix, projectionMatrix, m_Model[1].GetTexture());
		if (!result) { return false; }


		// Rotate the world matrix by the rotation value so that the triangle will spin.

		D3DXMatrixRotationY(&worldMatrix, rotation); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixTranslation(&translateMatrix, 2.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[2].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

	 // // Render the model using the color shader. 
		//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, 
		//	viewMatrix, projectionMatrix);

		// Render the model using the texture shader.
		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model[2].GetIndexCount(),
			worldMatrix, viewMatrix, projectionMatrix, m_Model[2].GetTexture());
		if (!result) { return false; }


  // Get the world, view, and projection matrices from the camera and d3d objects. 
	/*
	m_Camera->GetViewMatrix(viewMatrix); 
	m_D3D->GetWorldMatrix(worldMatrix); 
	m_D3D->GetProjectionMatrix(projectionMatrix); 

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	
	D3DXMatrixRotationY(&worldMatrix, rotation); //	D3DXMatrixRotationY(&worldMatrix, rotation);

  // Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
	m_Model[0].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3
	
 // // Render the model using the color shader. 
	//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, 
	//	viewMatrix, projectionMatrix);

	// Render the model using the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model[0].GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_Model[0].GetTexture());
	if(!result)  {   return false;  } 
	*/
	/*	
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());
	if(!result)  {   return false;  } 
	*/

	//HW2 - 3
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	//rotation = 0;
	//D3DXMatrixRotationY(&worldMatrix, rotation);
	m_plane_Model->Render(m_D3D->GetDeviceContext());


	//HW2 - 3
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_plane_Model->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_plane_Model->GetTexture());
	if (!result) { return false; }


	//Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}


//HW2 - 4
TextureShaderClass* GraphicsClass::getTextureShader() {
	return m_TextureShader;
}

//HW2 - 4
D3DClass* GraphicsClass::getD3D() {
	return m_D3D;
}
