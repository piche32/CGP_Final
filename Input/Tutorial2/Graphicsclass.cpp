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
	m_starUI = 0;
	m_Text = 0;
	//HW2 - 3
	m_plane_Model = 0;
	m_ModelIndex = 0;
	m_FogShader = 0;

	m_Terrain = 0;
	m_MiniMap = 0;
	m_Time = 0;
	m_Position = 0;

	m_ModelMax = 5;

	m_Cube = 0;

	m_ModelVertex = 0;
	m_player = 0;

	move = 100.0f;
	move_pp = 1.0f;
	move_boo = 10.0f;
	speed10 = 1.0f;
	cnt = 0;
	cnt1 = 0;
	cnt2 = 0;

	m_Sound = 0;
	m_Sound2 = 0;
	wallNum = 22;
	m_starNum = 5;

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_count = 0;
	m_countNum = 6;
	m_getedStarCount = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other) { }

GraphicsClass::~GraphicsClass() { 
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;

	ModelClass* model = nullptr;
	CollisionBoxClass* coll = nullptr;


	//Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D) { return false; }

	//Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

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
		(WCHAR*)L"../Tutorial2/data/sky.dds", screenWidth, screenHeight); //배경 조작?
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	m_starUI = new BitmapClass;
	if (!m_starUI)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_starUI->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight,
		(WCHAR*)L"../Tutorial2/data/starUI.dds", 50, 50);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the starUI object.", L"Error", MB_OK);
		return false;
	}

	m_count = new BitmapClass[m_countNum];
	result = m_count[0].Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../Tutorial2/data/0.dds", 50, 50);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the 0 object.", L"Error", MB_OK);
		return false;
	}
	result = m_count[1].Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../Tutorial2/data/1.dds", 50, 50);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the 1 object.", L"Error", MB_OK);
		return false;
	}
	result = m_count[2].Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../Tutorial2/data/2.dds", 50, 50);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the 2 object.", L"Error", MB_OK);
		return false;
	}
	result = m_count[3].Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../Tutorial2/data/3.dds", 50, 50);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the 3 object.", L"Error", MB_OK);
		return false;
	}
	result = m_count[4].Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../Tutorial2/data/4.dds", 50, 50);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the 4 object.", L"Error", MB_OK);
		return false;
	}
	result = m_count[5].Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"../Tutorial2/data/5.dds", 50, 50);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the 5 object.", L"Error", MB_OK);
		return false;
	}


	m_Camera->SetPosition(0.0f, 0.0f, -100.0f);
	D3DXVECTOR3 camera = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);
 // Set the initial position of the camera.

	m_baseViewMatrix = baseViewMatrix;

	// Create the model object.
	m_player = new PlayerClass;
	if (!m_player) { return false; }

	model = new ModelClass;
	result = model->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial2/data/goomba.obj", (WCHAR*)L"../Tutorial2/data/goomba.dds");
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	coll = new CollisionBoxClass;
	result = coll->Initialize(m_player->GetPos(),
		D3DXVECTOR3(8.0f, 8.0f, 8.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f), m_player->GetRot());
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the collision Box.", L"Error", MB_OK);
		return false;
	}
	result = m_player->Initialize(m_D3D->GetDevice(), model, coll, hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the player object.", L"Error", MB_OK);
		return false;
	}
	
	PlayerClass* player = (PlayerClass *) m_player;
	player->SetPos(115.0f, 0.0f, -22.0f); //(-110.0f, 0.0f, -20.0f); //(-35.0f, 0.0f, 217.0f);

	//player->SetPos(-35.0f, 0.0f, -10.0f); //(-110.0f, 0.0f, -20.0f); //(-35.0f, 0.0f, 217.0f);
	m_player->SetScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	player->SetPastPos(player->GetPos()); //첫 past pos에는 현 위치 넣어주기
	player->SetLookAt(player->GetPos() + D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	player->SetRot(0.0f, 180.0f, 0.0f); // 플레이어 모델의 초기값이 카메라를 바라보게 되어있음.

	D3DXVECTOR3 targetDist;
	D3DXVec3Normalize(&targetDist, &((PlayerClass*)m_player)->GetFront());
	//targetDist = D3DXVECTOR3(0.0f, 100.0f, 0.0f);//카메라 탑뷰로 볼 때..
	targetDist = -80.0f*targetDist + D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	m_Camera->SetTargetDist(targetDist);
	m_Camera->SetPosition(m_player->GetPos() + targetDist);
	//m_Camera->SetLookAt(m_player->GetPos() + D3DXVECTOR3(0.0f, 0.0f, 1.0f)); //카메라 탑뷰로 볼 때
	m_Camera->SetLookAt(m_player->GetPos()+ D3DXVECTOR3(0.0f, 20.0f, 0.0f));

	//별 모델 1개로 돌려쓰기..
	m_starModel = new ModelClass;
	result = m_starModel->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial2/data/star.obj", (WCHAR*)L"../Tutorial2/data/star.dds");
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the wall model object.", L"Error", MB_OK);
		return false;
	}

	//별 오브젝트
	m_star = new GameObjectClass[m_starNum];
	if (!m_star) return false;
	for (int i = 0; i < m_starNum; i++) {
		//콜라이더 만들기
		coll = new CollisionBoxClass;

		result = m_star[i].Initialize(m_D3D->GetDevice(), m_starModel, coll, hwnd);
		if (!result) {
			MessageBox(hwnd, L"Could not initialize the wall object.", L"Error", MB_OK);
			return false;
		}
		result = m_star[i].GetColl()->Initialize(m_star[i].GetPos(), m_star[i].GetScale(), D3DXVECTOR3(0.0f, 5.0f, 0.0f), m_star[i].GetRot());
		if (!result) {
			MessageBox(hwnd, L"Could not initialize the wall collider.", L"Error", MB_OK);
			return false;
		}
		m_star[i].GetColl()->SetScale(D3DXVECTOR3(10.0f, 10.0f, 10.0f));
	}

	//별 오브젝트 크기, 위치 세팅
	m_star[0].SetPos(40.0f, 5.0f, 90.0f);

	m_star[1].SetPos(-115.0f, 5.0f, -10.0f);

	m_star[2].SetPos(-115.0f, 5.0f, 110.0f);

	m_star[3].SetPos(65.0f, 5.0f, 70.0f);

	m_star[4].SetPos(-60.0f, 5.0f, 20.0f);

	//벽 모델 1개로 돌려쓰기!(오류시 수정)
	m_wallModel = new ModelClass;
	result = m_wallModel->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial2/data/cube.obj", (WCHAR*)L"../Tutorial2/data/floor.dds");
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the wall model object.", L"Error", MB_OK);
		return false;
	}

	//벽 오브젝트 만들기
	m_wall = new GameObjectClass[wallNum];
	if (!m_wall) return false;
	for (int i = 0; i < wallNum; i++) {
		//벽 콜라이더 만들기
		coll = new CollisionBoxClass;

		result = m_wall[i].Initialize(m_D3D->GetDevice(), m_wallModel, coll, hwnd);
		if (!result) {
			MessageBox(hwnd, L"Could not initialize the wall object.", L"Error", MB_OK);
			return false;
		}
	}

	float m_y = 10.0f;
	//벽 오브젝트 크기, 위치 세팅
	m_wall[0].SetPos(-350.0f, 0.0f- m_y, 2300.0f);
	m_wall[0].SetScale(250.0f, m_y, 5.0f);
	m_wall[0].GetColl()->SetScale(m_wall[0].GetScale());

	m_wall[1].SetPos(0.0f, 15.0f - m_y, -30.0f);
	m_wall[1].SetScale(250.0f, m_y, 5.0f);
	m_wall[1].GetColl()->SetScale(m_wall[1].GetScale());

	m_wall[2].SetPos(-125.0f, 15.0f - m_y, 55.0f);
	m_wall[2].SetScale(5.0f, m_y, 170.0f);
	m_wall[2].GetColl()->SetScale(m_wall[2].GetScale());

	m_wall[3].SetPos(0.0f, 15.0f - m_y, 130.0f);
	m_wall[3].SetScale(250.0f, m_y, 5.0f);
	m_wall[3].GetColl()->SetScale(m_wall[3].GetScale());

	m_wall[4].SetPos(125.0f, 15.0f - m_y, 55.0f);
	m_wall[4].SetScale(5.0f, m_y, 170.0f);
	m_wall[4].GetColl()->SetScale(m_wall[4].GetScale());

	m_wall[5].SetPos(-80.0f, 15.0f - m_y, 100.0f);
	m_wall[5].SetScale(3.0f, m_y, 30.0f);
	m_wall[5].GetColl()->SetScale(m_wall[5].GetScale());

	m_wall[6].SetPos(-50.0f, 15.0f - m_y, 85.0f);
	m_wall[6].SetScale(100.0f, m_y, 3.0f);
	m_wall[6].GetColl()->SetScale(m_wall[6].GetScale());

	m_wall[7].SetPos(-100.0f, 15.0f - m_y, 55.0f);
	m_wall[7].SetScale(50.0f, m_y, 3.0f);
	m_wall[7].GetColl()->SetScale(m_wall[7].GetScale());

	m_wall[8].SetPos(27.0f, 15.0f - m_y, 55.0f);
	m_wall[8].SetScale(100.0f, m_y, 3.0f);
	m_wall[8].GetColl()->SetScale(m_wall[8].GetScale());

	m_wall[9].SetPos(50.0f, 15.0f - m_y, 100.0f);
	m_wall[9].SetScale(3.0f, m_y, 90.0f);
	m_wall[9].GetColl()->SetScale(m_wall[9].GetScale());

	m_wall[10].SetPos(50.0f, 15.0f - m_y, 100.0f);
	m_wall[10].SetScale(3.0f, m_y, 90.0f);
	m_wall[10].GetColl()->SetScale(m_wall[10].GetScale());

	m_wall[11].SetPos(90.0f, 15.0f - m_y, 85.0f);
	m_wall[11].SetScale(30.0f, m_y, 3.0f);
	m_wall[11].GetColl()->SetScale(m_wall[11].GetScale());
	
	m_wall[12].SetPos(75.0f, 15.0f - m_y, 70.0f);
	m_wall[12].SetScale(3.0f, m_y, 30.0f);
	m_wall[12].GetColl()->SetScale(m_wall[12].GetScale());

	m_wall[13].SetPos(-50.0f, 15.0f - m_y, 35.0f);
	m_wall[13].SetScale(60.0f, m_y, 3.0f);
	m_wall[13].GetColl()->SetScale(m_wall[13].GetScale());

	m_wall[14].SetPos(90.0f, 15.0f - m_y, 35.0f);
	m_wall[14].SetScale(65.0f, m_y, 3.0f);
	m_wall[14].GetColl()->SetScale(m_wall[14].GetScale());

	m_wall[15].SetPos(-60.0f, 15.0f - m_y, 5.0f);
	m_wall[15].SetScale(130.0f, m_y, 3.0f);
	m_wall[15].GetColl()->SetScale(m_wall[15].GetScale());

	m_wall[16].SetPos(-50.0f, 15.0f - m_y, 20.0f);
	m_wall[16].SetScale(3.0f, m_y, 30.0f);
	m_wall[16].GetColl()->SetScale(m_wall[16].GetScale());
	
	m_wall[17].SetPos(-80.0f, 15.0f - m_y, -7.0f);
	m_wall[17].SetScale(3.0f, m_y, 20.0f);
	m_wall[17].GetColl()->SetScale(m_wall[17].GetScale());

	m_wall[18].SetPos(-50.0f, 15.0f - m_y, -20.0f);
	m_wall[18].SetScale(3.0f, m_y, 20.0f);
	m_wall[18].GetColl()->SetScale(m_wall[18].GetScale());

	m_wall[19].SetPos(3.7f, 15.0f - m_y, -3.5f);
	m_wall[19].SetScale(3.0f, m_y, 18.5f);
	m_wall[19].GetColl()->SetScale(m_wall[19].GetScale());

	m_wall[20].SetPos(30.0f, 15.0f - m_y, 30.0f);
	m_wall[20].SetScale(3.0f, m_y, 50.0f);
	m_wall[20].GetColl()->SetScale(m_wall[20].GetScale());

	m_wall[21].SetPos(80.0f, 15.0f- m_y, 10.0f);
	m_wall[21].SetScale(3.0f, m_y, 50.0f);
	m_wall[21].GetColl()->SetScale(m_wall[21].GetScale());

	/*m_wall[22].SetPos(0.0f, 0.0f, 20.0f);
	m_wall[22].SetScale(250.0f, 10.0f, 100.0f);
	m_wall[22].GetColl()->SetScale(m_wall[22].GetScale());*/


	m_Model = new ModelClass[m_ModelMax]; 
	if(!m_Model)  {   return false;  } 

	//HW2 - 3

	m_Cube = new ModelClass;
	if (!m_Cube) return false;

	result =m_Cube->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial2/data/Cube.obj",
		(WCHAR*)L"../Tutorial2/data/warppipe.dds");
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_plane_Model = new ModelClass;
	if (!m_plane_Model) {
		return false;
	}
  // Initialize the model object. 
	
	// Initialize the model object.
	result = m_Model[0].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/warppipe.obj", (WCHAR*)L"../Tutorial2/data/warppipe.dds"); //error 시 여기 확인
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[1].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/MegaMushroom.obj", (WCHAR*)L"../Tutorial2/data/MegaMushroom.dds"); //error 시 여기 확인
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	result = m_Model[2].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/SuperMushroom.obj", (WCHAR*)L"../Tutorial2/data/SuperMushroom.dds"); //error 시 여기 확인
		//(char*)"../Tutorial2/data/chair.obj", (WCHAR*)L"../Tutorial2/data/chair.dds"); //error 시 여기 확인
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[3].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/ChiefChilly.obj", (WCHAR*)L"../Tutorial2/data/ice_donketu.png"); //error 시 여기 확인
		//(char*)"../Tutorial2/data/chair.obj", (WCHAR*)L"../Tutorial2/data/chair.dds"); //error 시 여기 확인
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	//boo 장애물
	result = m_Model[4].Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/boo.obj", (WCHAR*)L"../Tutorial2/data/50f1611d.png"); //error 시 여기 확인
		//(char*)"../Tutorial2/data/chair.obj", (WCHAR*)L"../Tutorial2/data/chair.dds"); //error 시 여기 확인
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	//HW2 - 3
	result = m_plane_Model->Initialize(m_D3D->GetDevice(),
		(char*)"../Tutorial2/data/plane.obj", (WCHAR*)L"../Tutorial2/data/floor.dds"); //error 시 여기 확인
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

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

	// 지형 객체를 생성합니다.
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}

	// 지형 객체를 초기화 합니다.
	result = m_Terrain->Initialize(m_D3D->GetDevice(), "../Tutorial2/data/heightmap01.bmp", (WCHAR*)L"../Tutorial2/data/dirt01.dds", "../Tutorial2/data/colorm01.bmp");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// 미니맵에서 이 정보가 필요하기 때문에 지형의 크기를 가져옵니다.
	int terrainWidth = 0;
	int terrainHeight = 0;
	m_Terrain->GetTerrainSize(terrainWidth, terrainHeight);

	// 미니맵 객체를 생성합니다.
	m_MiniMap = new MiniMapClass;
	if (!m_MiniMap)
	{
		return false;
	}

	// 미니맵 객체를 초기화 합니다.
	result = m_MiniMap->Initialize(m_D3D->GetDevice(), hwnd, screenWidth, screenHeight, baseViewMatrix, (float)(terrainWidth - 1),
		(float)(terrainHeight - 1));
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the mini map object.", L"Error", MB_OK);
		return false;
	}

	m_Time = new TimerClass;
	if (!m_Time)
	{
		return false;
	}

	
	// Create the sound object.
	m_Sound = new SoundClass;
	if (!m_Sound)
	{
		return false;
	}
	// Initialize the sound object.
	result = m_Sound->Initialize_Effect(hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
		return false;
	}
	// Create the sound object.
	m_Sound2 = new SoundClass;
	if (!m_Sound2)
	{
		return false;
	}
	// Initialize the sound object.
	result = m_Sound2->Initialize_Coll(hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
		return false;
	}

	m_Position = new PositionClass;
	if (!m_Position) {
		return false;
	}
	m_Position->SetPosition(camera);

	return true;
}

void GraphicsClass::Shutdown() {


	if (m_Sound2)
	{
		m_Sound2->Shutdown();
		delete m_Sound2;
		m_Sound2 = 0;
	}
	// Release the sound object.
	if (m_Sound)
	{
		m_Sound->Shutdown();
		delete m_Sound;
		m_Sound = 0;
	}

	// 미니맵 객체를 해제합니다.
	if (m_Time)
	{
		delete m_Time;
		m_Time = 0;
	}

	// 미니맵 객체를 해제합니다.
	if (m_MiniMap)
	{
		m_MiniMap->Shutdown();
		delete m_MiniMap;
		m_MiniMap = 0;
	}

	// 지형 객체를 해제합니다.
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	if (m_D3D) {
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

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

	if (m_player) {
		m_player->Shutdown();
		delete m_player;
		m_player = 0;
	}

	//별 모델 해제
	if (m_starModel) {
		m_starModel->Shutdown();
		delete m_starModel;
		m_starModel;
		if (m_star) {
			for (int i = 0; i < m_starNum; i++) {
				m_star[i].SetModel(nullptr);
			}
		}
	}

	//별 해제
	if (m_star) {
		for (int i = 0; i < m_starNum; i++) {
			m_star[i].Shutdown();
		}
		delete[] m_star;
		m_star = 0;
	}
	
	//벽 모델 해제
	if (m_wallModel) {
		m_wallModel->Shutdown();
		delete m_wallModel;
		m_wallModel;
		if (m_wall) {
			for (int i = 0; i < wallNum; i++) {
				m_wall[i].SetModel(nullptr);
			}
		}
	}

	//벽 해제
	if (m_wall) {
		for (int i = 0; i < wallNum; i++) {
			m_wall[i].Shutdown();
		}
		delete[] m_wall;
		m_wall = 0;
	}

	

	if (m_Cube) {
		m_Cube->Shutdown();
		delete m_Cube;
		m_Cube = 0;
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

	// 별 UI
	if (m_starUI)
	{
		m_starUI->Shutdown();
		delete m_starUI;
		m_starUI = 0;
	}

	//별 갯수 UI
	if (m_count) {
		for (int i = 0; i < m_getedStarCount; i++) {
			m_count[i].Shutdown();
		}
		delete[] m_count;
		m_count = 0;
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
	rotation += 0.1f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	for (int i = 0; i < m_starNum; i++) {
		m_star[i].SetRot(0.0f, rotation, 0.0f);
	}

	result = HandleInput(m_Time->GetTime());
	if (!result)
	{
		return false;
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

	result = m_Text->SetPlayerInfo(m_player->GetPos(), ((PlayerClass*)m_player)->GetLookAt(), m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	//Set the location of the mouse.
	result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	if (!result) return false;

	result = m_Text->SetScreen(screenWidth, screenHeight, m_D3D->GetDeviceContext());
	if (!result) return false;


	if (!m_Camera->GetIsFPS())
	{
		D3DXVECTOR3 targetDist;
		D3DXVec3Normalize(&targetDist, &((PlayerClass*)m_player)->GetFront());
		targetDist = -80.0f*targetDist + D3DXVECTOR3(0.0f, 30.0f, 0.0f);
		m_Camera->SetTargetDist(targetDist);
		m_Camera->SetPosition(m_player->GetPos() + m_Camera->GetTargetDist());

		m_Camera->SetLookAt(m_player->GetPos() + D3DXVECTOR3(0.0f, -10.0f, 0.0f));
	}

	playerCollision();
	

	//Render the graphics scene.
	result = Render(rotation);
	if (!result) {
		return false;
	}

	

	return true;
}

bool GraphicsClass::HandleInput(float frameTime) {

	// 갱신된 위치를 계산하기 위한 프레임 시간을 설정합니다.
	m_Position->SetFrameTime(frameTime);

	// 시점 위치 / 회전을 가져옵니다.
	m_Position->GetPosition(pos);
	m_Position->GetRotation(rot);

	/*
	// 카메라의 위치를 ​​설정합니다.
	m_Camera->SetPosition(pos);
	m_Camera->SetRotation(rot);
	*/

	// 미니 맵에서 카메라의 위치를 ​​업데이트 합니다.
	m_MiniMap->PositionUpdate(m_player->GetPos().x, m_player->GetPos().z);

	return true;
}
//HW2 - 3
bool GraphicsClass::Render(float rotation) {
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix, translateMatrix, orthoMatrix; 
	bool result;
	float fogColor, fogStart, fogEnd;

	fogColor = 0.5f;

	fogStart = 0.0f;
	if (m_Camera->GetIsFPS() == true) {
		fogEnd = 25.0f;
	}
	else if (m_Camera->GetIsFPS() == false) {
		fogEnd = 60.0f;
	}

	//Clear the buffers to begin the scene.
	m_D3D->BeginScene(fogColor, fogColor, fogColor, 1.0f); //m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f); Tutorial1-3-1 //HW2 - 3

	// Generate the view matrix based on the camera's position.
	
	m_Camera->Render(); 

	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// 지형 버퍼를 렌더링 합니다.
	m_Terrain->Render(m_D3D->GetDeviceContext());

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);//비트맵 어디 그릴지
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 0, 0);
	if (!result)
	{
		return false;
	}
	
	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(),
		worldMatrix, m_baseViewMatrix, orthoMatrix, m_Bitmap->GetTexture()); //2D랜더링이라 projectionMatrix 대신 orthoMatrix사용
	if (!result)
	{
		return false;
	}


	
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn(); //3D 랜더링 하려면 꼭 켜주기..

		// Rotate the world matrix by the rotation value so that the triangle will spin.

	

	//m_D3D->GetWorldMatrix(worldMatrix);
	PlayerClass* player = (PlayerClass*)m_player;
	SetRotY(&worldMatrix, player->GetRot());

	SetScale(&worldMatrix, &translateMatrix, m_player->GetScale());
	SetPos(&worldMatrix, &translateMatrix, m_player->GetPos());

	m_player->GetModel()->Render(m_D3D->GetDeviceContext());

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_player->GetModel()->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_player->GetModel()->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	
	if (!result) { return false; }

	//플레이어 lookAt 랜더링
	/*m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	SetScale(&worldMatrix, &translateMatrix, D3DXVECTOR3(5.0f, 5.0f, 5.0f));
	SetPos(&worldMatrix, &translateMatrix, player->GetLookAt());

	m_Cube->Render(m_D3D->GetDeviceContext());

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Cube->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Cube->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result) { return false; }*/

	//별 랜더링
	for (int i = 0; i < m_starNum; i++)
	{
		if (!(m_star[i].GetActive())) continue;

		m_D3D->GetWorldMatrix(worldMatrix);

		SetRotY(&worldMatrix, m_star[i].GetRot());
		SetPos(&worldMatrix, &translateMatrix, m_star[i].GetPos());

		m_starModel->Render(m_D3D->GetDeviceContext());

		//안개 효과 적용
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_starModel->GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_starModel->GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	}

	//벽 랜더링
	for (int i = 0; i < wallNum; i++)
	{
		m_D3D->GetWorldMatrix(worldMatrix);

		SetScale(&worldMatrix, &translateMatrix, m_wall[i].GetScale());
		SetPos(&worldMatrix, &translateMatrix, m_wall[i].GetPos());

		m_wallModel->Render(m_D3D->GetDeviceContext());

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_wallModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_wallModel->GetTexture(), fogStart, fogEnd + 30);

		//안개 효과 적용
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_wallModel->GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_wallModel->GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	}

	//버섯장애물m_Model[0]
	D3DXMatrixRotationY(&worldMatrix, -90.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
	SetScale(&worldMatrix, &translateMatrix, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//SetPos(&worldMatrix, &translateMatrix, &D3DXVECTOR3(-20.0f, 0.0f, 110.f));
	if (cnt == 25) {
		if (move <95.0f || move >115.0f) {
			speed10 = speed10 * (-1);
		}
		move += speed10;
		cnt = 0;
	}
	cnt++;

	D3DXMatrixTranslation(&translateMatrix, -20.0f, 0.0f, move);

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

		//장애물_뾰족이
		// Rotate the world matrix by the rotation value so that the triangle will spin.	
		D3DXMatrixRotationY(&worldMatrix, 160.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 0.3f, 0.3f, 0.3f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

		if (cnt1 == 25) {
			if (move_pp <-150.0f || move_pp >30.0f) {
				speed10 = speed10 * (-1);
			}
			move_pp += speed10;
			cnt1 = 0;
		}
		cnt1++;
		m_Model[3].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3
		D3DXMatrixTranslation(&translateMatrix, move_pp, 5.0f, 70.0f);
	
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing. 

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[3].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[3].GetTexture(), fogStart, fogEnd + 30);
		if (!result) {
			return false;
		}
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[3].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[3].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

		//boo 장애물
		D3DXMatrixRotationY(&worldMatrix, 0.0f); //	D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixScaling(&translateMatrix, 0.3f, 0.3f, 0.3f);
		//SetPos(&worldMatrix, &translateMatrix, &D3DXVECTOR3(-20.0f, 5.0f, 110.f));
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

		if (cnt2 == 25) {
			if (move_boo <-0.0f || move_boo >30.0f) {
				speed10 = speed10 * (-1);
			}
			move_boo += speed10;
			cnt2 = 0;
		}
		cnt2++;
		m_Model[4].Render(m_D3D->GetDeviceContext());//	m_Model->Render(m_D3D->GetDeviceContext());  HW2 - 3
		D3DXMatrixTranslation(&translateMatrix, 80.0f, move_boo, 70.0f);

		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

		result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model[4].GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[4].GetTexture(), fogStart, fogEnd + 30);
		if (!result) {
			return false;
		}

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[4].GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Model[4].GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }

	//콜라이더 랜더링
	result = m_D3D->ChangeFillMode('W');
	if (!result) return false;

	//플레이어 콜라이더
	m_player->GetColl()->SetPos(m_player->GetPos());
	m_player->GetColl()->SetRot(m_player->GetRot());
	m_D3D->GetWorldMatrix(worldMatrix);
	m_player->GetColl()->Render(&worldMatrix, &translateMatrix);

	m_Cube->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Cube->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_Cube->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result) { return false; }

	//별 콜라이더
	for (int i = 0; i < m_starNum; i++) {
		if(!(m_star[i].GetActive())) continue;
		m_D3D->GetWorldMatrix(worldMatrix);
		m_star[i].GetColl()->Render(&worldMatrix, &translateMatrix);

		m_Cube->Render(m_D3D->GetDeviceContext());
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Cube->GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Cube->GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }
	}

	//벽 콜라이더
	for (int i = 0; i < wallNum; i++) {
		m_D3D->GetWorldMatrix(worldMatrix);
		m_wall[i].GetColl()->Render(&worldMatrix, &translateMatrix);

		m_Cube->Render(m_D3D->GetDeviceContext());
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Cube->GetIndexCount(), worldMatrix,
			viewMatrix, projectionMatrix, m_Cube->GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) { return false; }
	}

	m_D3D->ChangeFillMode('S');

	//if(m_player->GetPos()==)

	//플레인 랜더링
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

	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	
	//별 숫자 UI
	result = m_count[m_getedStarCount].Render(m_D3D->GetDeviceContext(), 555, 5);
	if (!result)
	{
		return false;
	}

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_count[m_getedStarCount].GetIndexCount(),
		worldMatrix, m_baseViewMatrix, orthoMatrix, m_count[m_getedStarCount].GetTexture()); //2D랜더링이라 projectionMatrix 대신 orthoMatrix사용
	if (!result)
	{
		return false;
	}


	//별 UI
	result = m_starUI->Render(m_D3D->GetDeviceContext(), 500, 5);
	if (!result)
	{
		return false;
	}

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_starUI->GetIndexCount(),
		worldMatrix, m_baseViewMatrix, orthoMatrix, m_starUI->GetTexture()); //2D랜더링이라 projectionMatrix 대신 orthoMatrix사용
	if (!result)
	{
		return false;
	}

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// 미니맵을 렌더링 합니다.
	if (!m_MiniMap->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix, m_TextureShader))
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

D3DClass* GraphicsClass::getD3D() {
	return m_D3D;
}

void GraphicsClass::playerMove(const char key) {
	D3DXVECTOR3 targetPos;
	D3DXVECTOR3 targetLookAt;
	D3DXVECTOR3 targetFront;
	D3DXVECTOR3 targetRight;
	D3DXVECTOR3 targetRot;

	PlayerClass* player = (PlayerClass*)m_player;
	if (player == nullptr) {
		if (m_Camera->GetIsFPS() == false) m_Camera->SetFPS();
		return;
	}
	else {
		targetPos = player->GetPos();
		targetLookAt = player->GetLookAt();
		targetFront = player->GetFront();
		targetRight = player->GetRight();
		targetRot = targetLookAt;
	}
	float speed = 0.5f;
	if (key == 'W')
	{
		targetPos.x += targetFront.x *speed;
		targetPos.y += targetFront.y *speed;
		targetPos.z += targetFront.z *speed;
		targetLookAt.x += targetFront.x *speed;
		targetLookAt.y += targetFront.y *speed;
		targetLookAt.z += targetFront.z *speed;


	}
	if (key == 'A')
	{
		targetLookAt.x -= targetRight.x * speed / 50.0f;
		targetLookAt.z -= targetRight.z * speed / 50.0f;

	}
	if (key == 'S')
	{
		targetPos.x -= targetFront.x *speed;
		targetPos.y -= targetFront.y *speed;
		targetPos.z -= targetFront.z *speed;
		targetLookAt.x -= targetFront.x *speed;
		targetLookAt.y -= targetFront.y *speed;
		targetLookAt.z -= targetFront.z *speed;

	}
	if (key == 'D')
	{

		targetLookAt.x += targetRight.x * speed / 50.0f;
		targetLookAt.z += targetRight.z * speed / 50.0f;

	}
	player->SetPos(targetPos);
	D3DXVECTOR3 temp;
	D3DXVec3Normalize(&temp, &(targetLookAt - targetPos));
	player->SetLookAt(targetPos + temp);

	if (key == 'A')
	{
		D3DXVec3Normalize(&targetRot, &(targetRot - targetPos));
		D3DXVec3Normalize(&targetLookAt, &(targetLookAt - targetPos));
		targetRot.y = D3DXVec3Dot(&targetRot, &targetLookAt); //플레이어가 전에 바라보고 있던 "방향"벡터와 지금 바라보고 있는 "방향"벡터를 내적해서 cos값을 구해준다
		targetRot.y = acos(targetRot.y); //cos값을 이용해서 두 방향 벡터 사이의 각을 구한다.
		
		m_Camera->SetYaw(m_Camera->GetYaw() - targetRot.y);

		targetRot.y = D3DXToDegree(targetRot.y); //라디안보다 degree가 여전히 익숙하다...

		targetRot.y = player->GetRot().y - targetRot.y;
		if (targetRot.y < -360.0f) targetRot.y = 0.0f;

		player->SetRot(targetRot);

	}
	else if (key == 'D') {

		D3DXVec3Normalize(&targetRot, &(targetRot - targetPos));
		D3DXVec3Normalize(&targetLookAt, &(targetLookAt - targetPos));
		targetRot.y = D3DXVec3Dot(&targetRot, &targetLookAt);

		targetRot.y = acos(targetRot.y);

		m_Camera->SetYaw(m_Camera->GetYaw() + targetRot.y);

		targetRot.y = D3DXToDegree(targetRot.y);
		targetRot.y = player->GetRot().y + targetRot.y;

		if (targetRot.y > 360.0f) targetRot.y = 0.0f;
		player->SetRot(targetRot);
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
	}
	if (key == 'A')
	{
		cameraPos.x -= cameraRight.x *speed;
		cameraPos.y -= cameraRight.y *speed;
		cameraPos.z -= cameraRight.z *speed;
		cameraLookAt.x -= cameraRight.x *speed;
		cameraLookAt.y -= cameraRight.y *speed;
		cameraLookAt.z -= cameraRight.z *speed;

	}
	if (key == 'S')
	{
		cameraPos.x -= cameraFront.x *speed;
		cameraPos.y -= cameraFront.y *speed;
		cameraPos.z -= cameraFront.z *speed;
		cameraLookAt.x -= cameraFront.x *speed;
		cameraLookAt.y -= cameraFront.y *speed;
		cameraLookAt.z -= cameraFront.z *speed;
	}
	if (key == 'D')
	{
		cameraPos.x += cameraRight.x *speed;
		cameraPos.y += cameraRight.y *speed;
		cameraPos.z += cameraRight.z *speed;
		cameraLookAt.x += cameraRight.x *speed;
		cameraLookAt.y += cameraRight.y *speed;
		cameraLookAt.z += cameraRight.z *speed;

	}
	m_Camera->SetPosition(cameraPos.x, cameraPos.y, cameraPos.z);
	m_Camera->SetLookAt(cameraLookAt);
}


//HW3 - 3
int GraphicsClass::countPolygons() {
	m_ModelIndex = 0;
	for (int i = 0; i < m_ModelMax; i++) {

		m_ModelIndex += m_Model[i].GetIndexCount();
	}

	m_ModelIndex += m_plane_Model->GetIndexCount(); //바닥 폴리곤 갯수
	m_ModelIndex += m_player->GetModel()->GetIndexCount(); //플레이어 폴리곤 갯수
	for (int i = 0; i < wallNum; i++) {
		m_ModelIndex += m_wallModel->GetIndexCount(); //벽 폴리곤 갯수
	}
	for (int i = 0; i < m_starNum; i++) {
		if(m_star[i].GetActive())
			m_ModelIndex += m_starModel->GetIndexCount(); //별 폴리곤 갯수
	}
	return (m_ModelIndex / 3);
}

void GraphicsClass::MouseInput(const DIMOUSESTATE mouseState) {
	if (!(m_Camera->GetIsFPS())) return;

	const float moveValue = 0.3f;
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
	m_Camera->SetLookAt(lookat);
}


void GraphicsClass::SetPos(D3DXMATRIX* worldMatrix, D3DXMATRIX* translateMatrix, D3DXVECTOR3 pos) {
	D3DXMatrixTranslation(translateMatrix, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(worldMatrix, worldMatrix, translateMatrix);
	return;
}
void GraphicsClass::SetScale(D3DXMATRIX* worldMatrix, D3DXMATRIX* translateMatrix, D3DXVECTOR3 scale) {
	D3DXMatrixScaling(translateMatrix, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(worldMatrix, worldMatrix, translateMatrix);
	return;
}

void GraphicsClass::SetRotY(D3DXMATRIX* worldMatrix, D3DXVECTOR3 rot) {
	
	D3DXMatrixRotationY(worldMatrix, D3DXToRadian(rot.y));
	return;
}
void GraphicsClass::SetCameraView() {
	m_Camera->SetFPS();
	return;
}

bool GraphicsClass::GetCameraView() {
	return m_Camera->GetIsFPS();
}

void GraphicsClass::playerCollision() {
	
	PlayerClass* player = (PlayerClass*)m_player;
	bool bCheck = true;

	D3DXVECTOR3 playerPos = player->GetColl()->GetPos();
	D3DXVECTOR3 playerPastPos = player->GetPastPos()+player->GetColl()->GetDist();
	D3DXVECTOR3 pos = playerPos;
	
	bool result;

	for (int i = 0; i < wallNum; i++) {
		if (player->GetColl()->Collision(m_wall[i].GetColl())) {
			//result = m_Text->ShowDebug("Collision Detected", m_D3D->GetDeviceContext());
		//	if (!result) return;

			if (D3DXVec3Length(&(playerPos - m_wall[i].GetColl()->GetPos())) <= //플레이어 콜라이더와 오브젝트 콜라이더 간의 거리 계산
				D3DXVec3Length(&(playerPastPos - m_wall[i].GetColl()->GetPos()))) {
				player->SetPos(player->GetPastPos()); //플레이어가 오브젝트와 더이상 가까워지지 않게 한다.
				m_Sound2->play();

			
			}

		}
	}

	return;
}

void GraphicsClass::eatStar() {
	bool result;
	for (int i = 0; i < m_starNum; i++) {
		if (!m_star[i].GetActive()) continue;
		if (m_player->GetColl()->Collision(m_star[i].GetColl())) {
			//result = m_Text->ShowDebug("Star Collision Detected", m_D3D->GetDeviceContext());
			//if (!result) return;
			//result = m_Sound->Initialize_Effect(hwnd);
			m_Sound->play();

			m_star[i].SetActive(false);
			m_getedStarCount++;


		}
	}
}