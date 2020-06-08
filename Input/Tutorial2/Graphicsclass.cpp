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
	m_ModelMax = 0;

	m_ModelVertex = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other) { }

GraphicsClass::~GraphicsClass() { 
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;

	m_ModelMax = 8;

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
	m_Camera->SetPosition(0.0f, 100.0f, -100.0f); //m_Camera->SetPosition(0.0f, 0.0f, -10.0f); tutorial2 - 1 수정 HW2 - 4
	m_Camera->SetRotation(15.0f, 0.0f, 0.0f);
	// Create the model object.
	m_Model = new ModelClass[m_ModelMax]; 
	if(!m_Model)  {   return false;  } 

	//HW2 - 3
	m_plane_Model = new ModelClass;
	if (!m_plane_Model) {
		return false;
	}
  // Initialize the model object. 
	/*result = m_Model[0].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/goomba.obj", (WCHAR*)L"../Tutorial2/data/goomba.dds"); //error 시 여기 확인
	if(!result)  {  
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK); 
		return false;
	}*/
	// Initialize the model object. 
	result = m_Model[0].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/Super Mega Mushroom.obj", (WCHAR*)L"../Tutorial2/data/Super Mega Mushroom.dds"); //error 시 여기 확인
	if (!result) {
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
	for (int i = 3; i < m_ModelMax-1; i++)
	{
		result = m_Model[i].Initialize(m_D3D->GetDevice(),
			(char*)"../Tutorial2/data/cube.obj", (WCHAR*)L"../Tutorial2/data/floor.dds"); //error 시 여기 확인
		if (!result) {
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}
	//HW2 - 3
	result = m_plane_Model->Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/plane.obj", (WCHAR*)L"../Tutorial2/data/floor.dds"); //error 시 여기 확인
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[7].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/warppipe.obj", (WCHAR*)L"../Tutorial2/data/warppipe.dds"); //error 시 여기 확인
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

	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight,
		(WCHAR*)L"../Tutorial2/data/seafloor.dds", 1024, 1024); //배경 조작?
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

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

	countPolygons();
	result = m_Text->CountPolygons(m_ModelIndex, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	//Set the location of the mouse.
	result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	if (!result) return false;

	D3DXMATRIX projectionMatrix, worldMatrix;
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
//	m_Camera->move(screenWidth, screenHeight,projectionMatrix, worldMatrix, mouseX, mouseY);

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

	//Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f); //m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f); Tutorial1-3-1 //HW2 - 3

	// Generate the view matrix based on the camera's position.
	
	m_Camera->Render(); 

	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);//비트맵 어디 그릴지
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 50, 0);
	if (!result)
	{
		return false;
	}
	
	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(),
		worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture()); //2D랜더링이라 projectionMatrix 대신 orthoMatrix사용
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn(); //3D 랜더링 하려면 꼭 켜주기..

		// Rotate the world matrix by the rotation value so that the triangle will spin.

		D3DXMatrixRotationY(&worldMatrix, rotation); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 0.1f, 0.1f, 0.1f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, -20.0f, 0.0f, 100.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
	  // Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[0].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

			// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[0].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[0].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

		if (!result) { return false; }


		// Rotate the world matrix by the rotation value so that the triangle will spin.

		D3DXMatrixRotationY(&worldMatrix, rotation); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 10.0f, 10.0f, 10.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 0.0f, 100.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[1].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		// Render the model using the texture shader.
		result = result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[1].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[1].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.

		D3DXMatrixRotationY(&worldMatrix, rotation); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixTranslation(&translateMatrix, 20.0f, 0.0f, 100.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[2].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		// Render the model using the texture shader.
		 result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[2].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[2].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		//HW3 - 1 Wall
		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 150.0f, 30.0f, 10.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, -50.0f, 15.0f, 0.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[3].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[3].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[3].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 10.0f, 30.0f, 130.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, -120.0f, 15.0f, 65.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[4].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[4].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[4].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 250.0f, 30.0f, 10.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 0.0f, 15.0f, 130.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[5].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[5].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[5].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 10.0f, 30.0f, 130.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 120.0f, 15.0f, 65.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[6].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3


		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[6].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[6].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		//D3DXMatrixScaling(&translateMatrix, 1.0f, 30.0f, 130.0f);
		//D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		D3DXMatrixTranslation(&translateMatrix, 9.0f, 0.0f, 65.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 
		m_Model[7].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3


		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[7].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[7].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

	//HW2 - 3
	//HW3 - 1

	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	
	//rotation = 0;
	//D3DXMatrixRotationY(&worldMatrix, rotation);
	m_plane_Model->Render(m_D3D->GetDeviceContext());

	

	//HW3 - 1
	//HW2 - 3
	result = result = m_LightShader->Render(m_D3D->GetDeviceContext(),m_plane_Model->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_plane_Model->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result) { return false; }
	
	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();
	D3DXMatrixRotationY(&worldMatrix, 0); //	D3DXMatrixRotationY(&worldMatrix, rotation);

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();
	
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
	float speed = 1.0f;
	if (key == 'W')
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z + speed * 1.0f);
	}
	if (key == 'A')
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x + speed * -1.0f, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
	}
	if (key == 'S')
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z + speed * -1.0f);
	}
	if (key == 'D')
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x + speed * 1.0f, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
	}
}

//HW3 - 3
void GraphicsClass::countPolygons() {
	m_ModelIndex = 0;
	for (int i = 0; i < m_ModelMax; i++) {

		m_ModelIndex += m_Model[i].GetIndexCount();
	}


	m_ModelIndex += m_plane_Model->GetIndexCount();
}

void GraphicsClass::cameraMouseMove(float& x, float& y) {
	m_Camera->mouseMove(x, y);
}