#include "graphicsclass.h" 
GraphicsClass::GraphicsClass() {
	m_Camera = 0;
	m_Model = 0;
//	m_ColorShader = 0;
//	m_TextureShader = 0;
	m_D3D = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_TextureShader = 0;
	m_Bitmap = 0;
	m_Text = 0;
	//HW2 - 3
	m_plane_Model = 0;
	m_ModelIndex = 0;
	m_FogShader = 0;

	m_StarNum = 5;
	m_WallNum = 21;
	m_ModelMax = 3 + m_WallNum + m_StarNum ;

	m_ModelVertex = 0;
	m_player = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other) { }

GraphicsClass::~GraphicsClass() { 
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;


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

	m_FogShader = new FogShaderClass;
	if (!m_FogShader) { return false; }

	result = m_FogShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the fog shader object", L"Error", MB_OK);
		return false;
	}

	// Create the camera object. 
	m_Camera = new CameraClass; 
	if(!m_Camera)  {   return false;  } 
	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight,
		(WCHAR*)L"../Tutorial2/data/sky.dds", screenWidth, screenHeight); //πË∞Ê ¡∂¿€?
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}
	m_Camera->SetPosition(0.0f, 0.0f, -100.0f); //m_Camera->SetPosition(0.0f, 0.0f, -10.0f); tutorial2 - 1 ºˆ¡§ HW2 - 4
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);
 // Set the initial position of the camera.
	m_Camera->SetPosition(10.0f, 10.0f, 10.0f); //m_Camera->SetPosition(0.0f, 0.0f, -10.0f); tutorial2 - 1 ºˆ¡§ HW2 - 4
	m_Camera->SetLookAt(D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	

	m_baseViewMatrix = baseViewMatrix;

	// Create the model object.
	m_player = new PlayerClass;
	if (!m_player) { return false; }

	result = m_player->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial2/data/warppipe.obj",
		(WCHAR*)L"../Tutorial2/data/warppipe.dds", hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the player object.", L"Error", MB_OK);
		return false;
	}

	m_player->SetPos(D3DXVECTOR3(10.0f, 0.0f, 110.f));
	m_player->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));


	m_Model = new ModelClass[m_ModelMax]; 
	if(!m_Model)  {   return false;  } 

	//HW2 - 3
	m_plane_Model = new ModelClass;
	if (!m_plane_Model) {
		return false;
	}
  // Initialize the model object. 
	
	// Initialize the model object. 
	result = m_Model[0].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/goomba.obj", (WCHAR*)L"../Tutorial2/data/goomba.dds"); //error Ω√ ø©±‚ »Æ¿Œ
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[1].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/MegaMushroom.obj", (WCHAR*)L"../Tutorial2/data/MegaMushroom.dds"); //error Ω√ ø©±‚ »Æ¿Œ
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	result = m_Model[2].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/SuperMushroom.obj", (WCHAR*)L"../Tutorial2/data/SuperMushroom.dds"); //error Ω√ ø©±‚ »Æ¿Œ
		//(char*)"../Tutorial2/data/chair.obj", (WCHAR*)L"../Tutorial2/data/chair.dds"); //error Ω√ ø©±‚ »Æ¿Œ
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	for (int i = 3; i < m_ModelMax-m_StarNum; i++)
	{
		result = m_Model[i].Initialize(m_D3D->GetDevice(),
			(char*)"../Tutorial2/data/cube.obj", (WCHAR*)L"../Tutorial2/data/floor.dds"); //error Ω√ ø©±‚ »Æ¿Œ
		if (!result) {
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}
	for (int i = 3 + m_WallNum; i < m_ModelMax; i++)
	{
		result = m_Model[i].Initialize(m_D3D->GetDevice(),
			(char*)"../Tutorial2/data/star.obj", (WCHAR*)L"../Tutorial2/data/star.dds"); //error Ω√ ø©±‚ »Æ¿Œ
		if (!result) {
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}
	//HW2 - 3
	result = m_plane_Model->Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/plane.obj", (WCHAR*)L"../Tutorial2/data/floor.dds"); //error Ω√ ø©±‚ »Æ¿Œ
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	
	/*// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader) {   return false;  }*/

 // // Initialize the color shader object.
	//result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd); 
	//if(!result)  {
	//	MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK); 
	//	return false;  
	//} 


		//HW2 - 3
	// Initialize the color shader object.
	/*result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	
	}*/

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	//m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	/*m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	m_baseViewMatrix = baseViewMatrix;*/
	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}
	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth,
		screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
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
	/*if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}*/

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	//HW2 - 3
	for (int i = 0; i < m_ModelMax; i++) {
		m_Model[i].Shutdown();
	}
	delete[] m_Model;
	m_Model = 0;



	/*if(m_Model)  {   
		m_Model->Shutdown(); 
		delete m_Model;  
		m_Model = 0; 
	} */

	if (m_player) {
		m_player->Shutdown();
		delete m_player;
		m_player = 0;
	}

	//HW2 - 3
	if (m_plane_Model){
		m_plane_Model->Shutdown();
		delete m_plane_Model;
		m_plane_Model = 0;
		}

  // Release the camera object.
	if(m_Camera)  { 
		delete m_Camera; 
		m_Camera = 0;  
	} 

	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	if (m_FogShader) {
		m_FogShader->Shutdown();
		delete m_FogShader;
		m_FogShader = 0;
	}

	return;
}
bool GraphicsClass::Frame(int screenWidth, int screenHeight, int fps, int cpu, float frameTime, int mouseX, int mouseY) {
	bool result;

	static float rotation = 0;
	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.001f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->CountPolygons(countPolygons(), m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	result = m_Text->SetCameraInfo(m_Camera->GetPosition(), m_Camera->GetLookAt(), m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	//Set the location of the mouse.
	result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	if (!result) return false;

<<<<<<< HEAD
	if (!m_Camera->GetIsFPS()) {
		m_Camera->SetPosition(m_player->GetPos() + m_Camera->GetTargetDist()); //m_Camera->SetPosition(0.0f, 0.0f, -10.0f); tutorial2 - 1 ºˆ¡§ HW2 - 4
		m_Camera->SetLookAt(m_player->GetPos() + D3DXVECTOR3(0.0f, 10.0f, 0.0f));
	}
=======
	/*D3DXMATRIX projectionMatrix, worldMatrix;
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);*/
>>>>>>> parent of 270960a... 3Ïù∏Ïπ≠ Ïπ¥Î©îÎùº

	//Render the graphics scene.
	result = Render(rotation);
	if (!result) {
		return false;
	}

	

	return true;
}
//HW2 - 3
bool GraphicsClass::Render(float rotation) {
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix, translateMatrix, orthoMatrix; 
	bool result;
	float fogColor, fogStart, fogEnd;

	fogColor = 0.5f;

	fogStart = 0.0f;
	fogEnd = 25.0f;

	//Clear the buffers to begin the scene.
	m_D3D->BeginScene(fogColor, fogColor, fogColor, 1.0f); //m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f); Tutorial1-3-1 //HW2 - 3

	// Generate the view matrix based on the camera's position.
	
	m_Camera->Render(); 

	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);//∫Ò∆Æ∏  æÓµ ±◊∏±¡ˆ
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 0, 0);
	if (!result)
	{
		return false;
	}
	
	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(),
		worldMatrix, m_baseViewMatrix, orthoMatrix, m_Bitmap->GetTexture()); //2D∑£¥ı∏µ¿Ã∂Û projectionMatrix ¥ÎΩ≈ orthoMatrixªÁøÎ
	if (!result)
	{
		return false;
	}
	
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn(); //3D ∑£¥ı∏µ «œ∑¡∏È ≤¿ ƒ—¡÷±‚..

		// Rotate the world matrix by the rotation value so that the triangle will spin.

	//m_D3D->GetWorldMatrix(worldMatrix);

	SetScale(&worldMatrix, &translateMatrix, &m_player->GetScale());
	SetPos(&worldMatrix, &translateMatrix, &m_player->GetPos());

	//SetScale(&worldMatrix, &translateMatrix, &D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//SetPos(&worldMatrix, &translateMatrix, &D3DXVECTOR3(-20.0f, 0.0f, 11.0f));


	/*result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_player->GetModel()->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_player->GetModel()->GetTexture(), fogStart, fogEnd);
	if (!result) {
		return false;
	}*/

	m_player->GetModel()->Render(m_D3D->GetDeviceContext());

	//HW3 - 1
	//HW2 - 3
	result = result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_player->GetModel()->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_player->GetModel()->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result) { return false; }

	
	D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
	SetScale(&worldMatrix, &translateMatrix, &D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	SetPos(&worldMatrix, &translateMatrix, &D3DXVECTOR3(-20.0f, 0.0f, 110.f));
	//D3DXMatrixScaling(&translateMatrix, 0.1f, 0.1f, 0.1f);
//	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
	//	D3DXMatrixTranslation(&translateMatrix, -20.0f, 0.0f, 110.0f);
		//D3DXMatrixTranslation(&translateMatrix, (m_Camera->GetPosition().x+m_Camera->GetLookAt().x), (m_Camera->GetPosition().y + m_Camera->GetLookAt().y), (m_Camera->GetPosition().z + m_Camera->GetLookAt().z));  //ƒ´∏ﬁ∂Û lookAtø° ¿÷±‚

	//	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
	  // Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[0].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

			// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[0].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[0].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

		if (!result) { return false; }


		// Rotate the world matrix by the rotation value so that the triangle will spin.

		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 1.0f, 1.0f, 1.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 10.0f, 3.0f, 40.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[1].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[1].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[1].GetTexture(), fogStart, fogEnd + 30);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[1].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[1].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		//star πËƒ°
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 10.0f, 10.0f, 10.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 100.0f, 5.0f, 110.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[2].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[2].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[2].GetTexture(), fogStart, fogEnd + 30);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		 result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[2].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[2].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		//===================================================================================================================================
		//HW3 - 1 Wall
		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 250.0f, 50.0f, 5.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 15.0f, -30.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[3].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3	bottom_length_wall

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[3].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[3].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[3].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[3].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 5.0f, 50.0f, 170.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, -125.0f, 15.0f, 55.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[4].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3	left_length_wall

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[4].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[4].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[4].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[4].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 250.0f, 50.0f, 5.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 15.0f, 130.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[5].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3	//up_length_wall

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[5].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[5].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[5].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[5].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 5.0f, 50.0f, 170.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 125.0f, 15.0f, 55.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[6].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3	//right_length_wall

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[6].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[6].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[6].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[6].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 3.0f, 50.0f, 30.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, -80.0f, 15.0f, 100.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[7].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[7].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[7].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[7].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[7].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 100.0f, 50.0f, 3.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, -50.0f, 15.0f, 85.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[8].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[8].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[8].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[8].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[8].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 50.0f, 50.0f, 3.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, -100.0f, 15.0f, 55.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[9].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[9].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[9].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[9].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[9].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 100.0f, 50.0f, 3.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 27.0f, 15.0f, 55.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[10].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[10].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[10].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[10].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[10].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 3.0f, 50.0f, 90.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 50.0f, 15.0f, 100.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[11].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[11].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[11].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[11].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[11].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 3.0f, 50.0f, 90.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 50.0f, 15.0f, 100.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[12].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[12].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[12].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[12].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[12].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 30.0f, 50.0f, 3.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 90.0f, 15.0f, 85.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[22].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[22].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[22].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[22].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[22].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 3.0f, 50.0f, 30.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 75.0f, 15.0f, 70.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[13].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[13].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[13].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}


		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[13].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[13].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 60.0f, 50.0f, 3.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, -50.0f, 15.0f, 35.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[14].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[14].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[14].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[14].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[14].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

			// Rotate the world matrix by the rotation value so that the triangle will spin.
			D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 60.0f, 50.0f, 3.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 90.0f, 15.0f, 35.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[15].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[15].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[15].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[15].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[15].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 130.0f, 50.0f, 3.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, -60.0f, 15.0f, 5.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[16].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[16].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[16].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[16].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[16].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 3.0f, 50.0f, 30.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, -50.0f, 15.0f, 20.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[17].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[17].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[17].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[17].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[17].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 3.0f, 50.0f, 20.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, -80.0f, 15.0f, -10.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[18].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3


		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[18].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[18].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[18].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[18].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 3.0f, 50.0f, 20.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, -50.0f, 15.0f, -20.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[19].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[19].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[19].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[19].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[19].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 3.0f, 50.0f, 20.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 3.7f, 15.0f, -7.5f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[20].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[20].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[20].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[20].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[20].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 3.0f, 50.0f, 50.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 30.0f, 15.0f, 30.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[21].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3


		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[21].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[21].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[21].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[21].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 3.0f, 50.0f, 50.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 80.0f, 15.0f, 10.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[22].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[22].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[22].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[22].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[22].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 250.0f, 10.0f, 100.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 20.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[23].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[23].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[23].GetTexture(), fogStart, fogEnd);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[23].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[23].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		//==================================================================================================
		//star 5∞≥ ¥ı πËƒ°
		D3DXMatrixRotationY(&worldMatrix, rotation); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixTranslation(&translateMatrix, -10.0f, 5.0f, -10.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[24].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[24].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[24].GetTexture(), fogStart, fogEnd + 30);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[24].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[24].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		D3DXMatrixRotationY(&worldMatrix, rotation); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixTranslation(&translateMatrix, -115.0f, 5.0f, -10.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[25].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[25].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[25].GetTexture(), fogStart, fogEnd + 30);
		if (!result) {
			return false;
		}

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[25].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[25].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		D3DXMatrixRotationY(&worldMatrix, rotation); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixTranslation(&translateMatrix, -115.0f, 5.0f, 120.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[26].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[26].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[26].GetTexture(), fogStart, fogEnd + 30);
		if (!result) {
			return false;
		}

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[26].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[26].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		D3DXMatrixRotationY(&worldMatrix, rotation); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixTranslation(&translateMatrix, 100.0f, 5.0f, 30.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[27].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[27].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[27].GetTexture(), fogStart, fogEnd + 30);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[27].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[27].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		D3DXMatrixRotationY(&worldMatrix, rotation); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixTranslation(&translateMatrix, -63.0f, 5.0f, 80.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[28].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3


		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[28].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[28].GetTexture(), fogStart, fogEnd + 30);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[28].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[28].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

	//HW2 - 3
	//HW3 - 1

	

	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	
	//rotation = 0;
	D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, -500.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

	//D3DXMatrixRotationY(&worldMatrix, rotation);
	m_plane_Model->Render(m_D3D->GetDeviceContext());

	result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_plane_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_plane_Model->GetTexture(), fogStart, fogEnd);
	if (!result) {
		return false;
	}

	//HW3 - 1
	//HW2 - 3
	result = result = m_LightShader->Render(m_D3D->GetDeviceContext(),m_plane_Model->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_plane_Model->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result) { return false; }
	
	m_D3D->TurnZBufferOff();
	// Turn on the alpha blending before rendering the text.
	
	m_D3D->TurnOnAlphaBlending();
	//D3DXMatrixRotationY(&worldMatrix, 0); //	D3DXMatrixRotationY(&worldMatrix, rotation);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();
	m_D3D->TurnZBufferOn();
	//Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}


//HW2 - 4
/*TextureShaderClass* GraphicsClass::getTextureShader() {
	return m_TextureShader;
}*/

//HW2 - 4
D3DClass* GraphicsClass::getD3D() {
	return m_D3D;
}

//HW3 - 2
void GraphicsClass::changeLight(const int input) {
	if (input == 1) {
		m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 0.0f);
		m_Light->SetSpecularPower(1000000);
	}
	if (input == 2) {
		m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		m_Light->SetSpecularPower(1000000);
	}
	if (input == 3) {
		m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light->SetSpecularPower(32.0f);
	}
}

void GraphicsClass::cameraMove(const char key) {
	D3DXVECTOR3 cameraPos = m_Camera->GetPosition();
	D3DXVECTOR3 cameraLookAt = m_Camera->GetLookAt();
	D3DXVECTOR3 cameraFront = m_Camera->GetForwardDirection();
	D3DXVECTOR3 cameraRight = m_Camera->GetRightDirection();
	float speed = 0.1f;
	if (key == 'W')
	{
		
		cameraPos.x += cameraFront.x *speed;
		cameraPos.y += cameraFront.y *speed;
		cameraPos.z += cameraFront.z *speed;
		cameraLookAt.x += cameraFront.x *speed;
		cameraLookAt.y += cameraFront.y *speed;
		cameraLookAt.z += cameraFront.z *speed;
		//m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z + speed * 1.0f);
	}
	if (key == 'A')
	{
		cameraPos.x -= cameraRight.x *speed;
		cameraPos.y -= cameraRight.y *speed;
		cameraPos.z -= cameraRight.z *speed;
		cameraLookAt.x -= cameraRight.x *speed;
		cameraLookAt.y -= cameraRight.y *speed;
		cameraLookAt.z -= cameraRight.z *speed;
		//m_Camera->SetPosition(m_Camera->GetPosition().x + speed * -1.0f, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
	}
	if (key == 'S')
	{

		cameraPos.x -= cameraFront.x *speed;
		cameraPos.y -= cameraFront.y *speed;
		cameraPos.z -= cameraFront.z *speed;
		cameraLookAt.x -= cameraFront.x *speed;
		cameraLookAt.y -= cameraFront.y *speed;
		cameraLookAt.z -= cameraFront.z *speed;
		//m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z + speed * -1.0f);
	}
	if (key == 'D')
	{
		cameraPos.x += cameraRight.x *speed;
		cameraPos.y += cameraRight.y *speed;
		cameraPos.z += cameraRight.z *speed;
		cameraLookAt.x += cameraRight.x *speed;
		cameraLookAt.y += cameraRight.y *speed;
		cameraLookAt.z += cameraRight.z *speed;
		//m_Camera->SetPosition(m_Camera->GetPosition().x + speed * 1.0f, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
	}
	if (key == 'Q')
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y + speed * 1.0f, m_Camera->GetPosition().z);
	}
	if (key == 'E')
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x , m_Camera->GetPosition().y + speed * -1.0f, m_Camera->GetPosition().z);
	}
	//D3DXVec3Normalize(&cameraLookAt, &cameraLookAt);

	m_Camera->SetPosition(cameraPos.x, cameraPos.y, cameraPos.z );
	m_Camera->SetLookAt(cameraLookAt);
	//m_Camera->GetForwardDirection();
	//m_Camera->GetRightDirection();
}

//HW3 - 3
int GraphicsClass::countPolygons() {
	m_ModelIndex = 0;
	for (int i = 0; i < m_ModelMax; i++) {

		m_ModelIndex += m_Model[i].GetIndexCount();
	}


	m_ModelIndex += m_plane_Model->GetIndexCount();
	m_ModelIndex += m_player->GetModel()->GetIndexCount();

	return (m_ModelIndex / 3);
}

void GraphicsClass::MouseInput(const DIMOUSESTATE mouseState) {
	const float moveValue = 0.3f;
	const float value = 50.0f;
	D3DXVECTOR3 lookat = m_Camera->GetLookAt();
	m_Camera->GetForwardDirection();
	D3DXVECTOR3 cameraRight = m_Camera->GetRightDirection();

	if (mouseState.lX > 0) {
		lookat.x += cameraRight.x * moveValue;
		lookat.z += cameraRight.z * moveValue;
	}
	else if (mouseState.lX < 0) {
		lookat.x -= cameraRight.x * moveValue;
		lookat.z -= cameraRight.z * moveValue;
	}
	if (mouseState.lY > 0) {
		lookat.y -= moveValue;
	}
	else if (mouseState.lY < 0) {
		lookat.y += moveValue;
	}
	//D3DXVec3Normalize(&lookat, &lookat);
	/*lookat.x = lookat.x*value;
	lookat.y = lookat.y*value;
	lookat.z = lookat.z*value;*/
	m_Camera->SetLookAt(lookat);
}


void GraphicsClass::SetPos(D3DXMATRIX* worldMatrix, D3DXMATRIX* translateMatrix, D3DXVECTOR3* pos) {
	D3DXMatrixTranslation(translateMatrix, pos->x, pos->y, pos->z);
	D3DXMatrixMultiply(worldMatrix, worldMatrix, translateMatrix);
	return;
}
void GraphicsClass::SetScale(D3DXMATRIX* worldMatrix, D3DXMATRIX* translateMatrix, D3DXVECTOR3* scale) {
	D3DXMatrixScaling(translateMatrix, scale->x, scale->y, scale->z);
	D3DXMatrixMultiply(worldMatrix, worldMatrix, translateMatrix);
	return;
}