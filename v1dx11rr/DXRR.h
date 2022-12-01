#ifndef _dxrr
#define _dxrr
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
#include "TerrenoRR.h"
#include "Camara.h"
#include "SkyDome.h"
#include "Billboard.h"
#include "ModeloRR.h"
#include "XACT3Util.h"
#include "Tiempo.h"
#include "GUI.h"
#include "Text.h"

class DXRR{	

private:
	int ancho;
	int alto;
public:	
	HINSTANCE hInstance;
	HWND hWnd;

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* d3dContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferTarget;

	ID3D11Texture2D* depthTexture;
	ID3D11DepthStencilView* depthStencilView;

	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthStencilDisabledState;

	ID3D11BlendState *alphaBlendState, *commonBlendState;
	D3DXVECTOR3 dirluz;
	D3DXVECTOR4 luzAmbiental;
	D3DXVECTOR4 luzDifusa;
	D3DXVECTOR4 luzEspecular;

	#define PI 3.14159265

	float DifAmb[2];
	float luzAmb[4];
	float posY, posX, posZ;
	float PosicionesLuzDinamic[3];
	float fad;
	float fa;
	float fas;

	int frameBillboard;
	int Contador;
	int ContFramesTarde;
	int ContFramesNoche;
	int ContFramesMa�ana;
	int contadorGLSL;
	float angle;
	float luzx = 0.0f;
	float luzy = 0.0f;
	float luzz = 0.0f;

	TerrenoRR *terreno;
	SkyDome *skydome;
	BillboardRR* oasis;

	BillboardRR *billboard;
	BillboardRR* palma;
	BillboardRR* palma2;
	BillboardRR* bush;
	BillboardRR* bush2;
	BillboardRR* cactus;
	BillboardRR* cactus2;

	Camara *camara;
	Tiempo* levelTime;
	GUI* vida, * vida1, * vida2, * gameOver, * ganaste;
	Text* texto;
	Text* texto2;
	bool fueraTotem, fueraTotem2, fueraTotem3, fueraTotem4, fueraTotem5 = true;
	int cantTotems = 0;
	bool haColisionado;

	ModeloRR* prota;
	ModeloRR* nave;
	ModeloRR* hangar;
	ModeloRR* vivienda;
	ModeloRR* vivienda2;
	ModeloRR* cheep;
	ModeloRR* axe;
	ModeloRR* bucket;
	ModeloRR* heart, *heart1, *heart2;
	ModeloRR* waterWell;
	ModeloRR* stone;

	ModeloRR* totem;
	ModeloRR* totem2;
	ModeloRR* totem3;
	ModeloRR* totem4;
	ModeloRR* totem5;
	ModeloRR* sandman;
	ModeloRR* sandman2;
	ModeloRR* sandman3;
	ModeloRR* sandman4;
	ModeloRR* sandman5;
	ModeloRR* skeleton;
	ModeloRR* skeleton2;
	ModeloRR* skeleton3;
	ModeloRR* skeleton4;
	ModeloRR* skeleton5;
	
	float izqder;
	float arriaba;
	float vel;
	bool breakpoint;
	vector2 uv1[32];
	vector2 uv2[32];
	vector2 uv3[32];
	vector2 uv4[32];

	XACTINDEX cueIndex;
	CXACT3Util m_XACT3;

	bool camaraTipo;
	float rotCam;

	int vidas = 3;
	//bool effectDone;
	float segundos;
	bool entra = true, temporal = false;
	bool entra2 = true, temporal2 = false;
	bool SandmanV[5], SandmanVTemporal[5], SkeletonV[5], SkeletonVTemporal[5], SkeletonLive[5], SandmanLive[5];
	float posicionSandmanVX;
	bool tenemosHacha = false;
	bool tenemosCubeta = false;
	bool mostrarCubeta = false;
	bool cubetaLlena = false;
	bool mostrarPiedra = false;
	bool mostarTotems = true;
	bool mostrarSkeletons = false;
	bool mostrarSandmans = false;
	bool corazonActivado[3];
	bool jugadorGano = false;
	bool jugadorPerdio = false;
	int tiemTardado = 0;

	ModeloRR* stone;
	/*int skeletonMuertos = 0;
	int sandmanMuertos = 0;*/
	
    DXRR(HWND hWnd, int Ancho, int Alto)
	{
		ContFramesMa�ana = 80;
		ContFramesNoche = 40;
		ContFramesTarde = 80;
		contadorGLSL = 0;
		segundos = 601;
		fad = 0.8f;
		fa = 0.8f;
		fas = 0.5f;
		angle = 0.0f;
		float luzx = 0.0f;
		float luzy = 0.0f;
		float luzz = 0.0f;

		luzAmbiental = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
		luzDifusa = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
		luzEspecular = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

		breakpoint = false;
		frameBillboard = 0;
		ancho = Ancho;
		alto = Alto;
		driverType = D3D_DRIVER_TYPE_NULL;
		featureLevel = D3D_FEATURE_LEVEL_11_0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
		IniciaD3D(hWnd);
		izqder = 0;
		arriaba = 0;

		for (int i = 0; i < sizeof(SandmanV); i++) {
			SandmanV[i] = true;
		}

		for (int i = 0; i < sizeof(SkeletonV); i++) {
			SkeletonV[i] = true;
		}

		for (int i = 0; i < sizeof(SandmanVTemporal); i++) {
			SandmanVTemporal[i] = false;
		}

		for (int i = 0; i < sizeof(SkeletonVTemporal); i++) {
			SkeletonVTemporal[i] = false;
		}

		for (int i = 0; i < sizeof(SkeletonLive); i++) {
			SkeletonLive[i] = true;
		}

		for (int i = 0; i < sizeof(SandmanLive); i++) {
			SandmanLive[i] = true;
		}

		for (int i = 0; i < sizeof(corazonActivado); i++) {
			corazonActivado[i] = false;
		}
		corazonActivado[0] = true;

		posicionSandmanVX = -125;

		camara = new Camara(D3DXVECTOR3(0,80,10), D3DXVECTOR3(0,80,0), D3DXVECTOR3(0,1,0), Ancho, Alto);
		//terreno = new TerrenoRR(500, 500, d3dDevice, d3dContext);  //Dos primeros n�meros son la escala del terreno
		terreno = new TerrenoRR(L"ArenaB4.jpg", L"ArenaB4_spec.jpg", L"ArenaB4_normal.jpg",
			L"ArenaB1.jpg", L"ArenaB1_spec.jpg", L"ArenaB1_norm.jpg",
			L"ArenaB3.jpg", L"ArenaB3_spec.jpg", L"ArenaB3_normal.jpg",
			L"CraterWater1.jpg", 500, 500, d3dDevice, d3dContext);
		skydome = new SkyDome(32, 32, 100.0f, &d3dDevice, &d3dContext, L"SkyDome12.png", L"SkyDome8.png", L"SkyDome.png");  // skydome cambiado
		oasis = new BillboardRR(L"Assets/Billboards/water.jpg", L"Assets/Billboards/waterDUDV.png", d3dDevice, d3dContext, 200, true);

		billCargaFuego();
		billboard = new BillboardRR(L"Assets/Billboards/fuego-anim.png", L"Assets/Billboards/fuego-anim-normal.png", d3dDevice, d3dContext, 5);
		palma = new BillboardRR(L"Assets/Billboards/Palma.png", L"Assets/Billboards/PalmaNormal.png", d3dDevice, d3dContext, 50);
		palma2 = new BillboardRR(L"Assets/Billboards/Palma.png", L"Assets/Billboards/PalmaNormal.png", d3dDevice, d3dContext, 35);
		bush = new BillboardRR(L"Assets/Billboards/bush.png", L"Assets/Billboards/bushNormal.png", d3dDevice, d3dContext, 8);
		bush2 = new BillboardRR(L"Assets/Billboards/bush.png", L"Assets/Billboards/bushNormal.png", d3dDevice, d3dContext, 12);
		cactus = new BillboardRR(L"Assets/Billboards/cactus.png", L"Assets/Billboards/cactusNormal.png", d3dDevice, d3dContext, 15);
		cactus2 = new BillboardRR(L"Assets/Billboards/cactus.png", L"Assets/Billboards/cactusNormal.png", d3dDevice, d3dContext, 15);
		
		prota = new ModeloRR(d3dDevice, d3dContext, "Assets/CorotSnake/Corot.obj", L"Assets/CorotSnake/AlbedoCorot.jpg", L"Assets/CorotSnake/MetallicCorot.jpg", L"Assets/CorotSnake/NormalCorot.jpg", 10, 0);
		nave = new ModeloRR(d3dDevice, d3dContext, "Assets/Nave/Nave.obj", L"Assets/Nave/ColorNave.png", L"Assets/Nave/MetallicNave.png", L"Assets/Nave/NormalNave.png", 15, 0);
		hangar = new ModeloRR(d3dDevice, d3dContext, "Assets/Hangar/nuevoHangar.obj", L"Assets/Hangar/HangarColor.jpg", L"Assets/Hangar/HangarRough.jpg", L"Assets/Hangar/HangarNormal.jpg", 75, -140); //Metallic o Rough se ven bien
		vivienda = new ModeloRR(d3dDevice, d3dContext, "Assets/NewVivienda/Vivienda4.obj", L"Assets/NewVivienda/lambert12_Base_Color.png", L"Assets/NewVivienda/lambert12_Roughness.png", L"Assets/NewVivienda/lambert12_Normal.png", 140, 150);
		vivienda2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Vivienda/Laberinto2.obj", L"Assets/Vivienda/Laberinto2_Color.png", L"Assets/Vivienda/Laberinto2_Specular.png", L"Assets/Vivienda/lambert1_Normal.png", -125, -75);
		//cheep = new ModeloRR(d3dDevice, d3dContext, "Assets/Auto/Cheep.obj", L"Assets/Auto/Cheep.jpg", L"Assets/Auto/Imagen1.jpg", 0, -30);
		axe = new ModeloRR(d3dDevice, d3dContext, "Assets/Axe/Axe.obj", L"Assets/Axe/Axe_Color.png", L"Assets/Axe/Axe_Rough.png", L"Assets/Axe/Axe_Normal.png", 175, 115);
		bucket = new ModeloRR(d3dDevice, d3dContext, "Assets/Bucket/Bucket.obj", L"Assets/Bucket/Kova_A.png", L"Assets/Bucket/Kova_R.png", L"Assets/Bucket/Kova_N.png", -25, -150);
		heart = new ModeloRR(d3dDevice, d3dContext, "Assets/Heart/nuevoHeart.obj", L"Assets/Heart/heartColor.png", L"Assets/Heart/heartMetallic.png", L"Assets/Heart/heartNormal.png", -25, -75);
		heart1 = new ModeloRR(d3dDevice, d3dContext, "Assets/Heart/nuevoHeart.obj", L"Assets/Heart/heartColor.png", L"Assets/Heart/heartMetallic.png", L"Assets/Heart/heartNormal.png", 25, -75);
		heart2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Heart/nuevoHeart.obj", L"Assets/Heart/heartColor.png", L"Assets/Heart/heartMetallic.png", L"Assets/Heart/heartNormal.png", -25, 75);
		waterWell = new ModeloRR(d3dDevice, d3dContext, "Assets/WaterWell/WaterWell.obj", L"Assets/WaterWell/Well_Base_Color.png", L"Assets/WaterWell/Well_Roughness.png", L"Assets/WaterWell/Well_Normal_DirectX.png", -125, 125);
		stone = new ModeloRR(d3dDevice, d3dContext, "Assets/Stone/Stone.obj", L"Assets/Stone/StoneColor.jpg", L"Assets/Stone/StoneRough.jpg", L"Assets/Stone/StoneNormal.jpg", 125, -150);

		totem = new ModeloRR(d3dDevice, d3dContext, "Assets/SkeletonCubeModel/SkeletonCube.obj", L"Assets/SkeletonCubeModel/Cube.jpg", L"Assets/SkeletonCubeModel/CubeRough.jpg", L"Assets/SkeletonCubeModel/CubeNormal.jpg", 150, -90);
		totem2 = new ModeloRR(d3dDevice, d3dContext, "Assets/SkeletonCubeModel/SkeletonCube.obj", L"Assets/SkeletonCubeModel/Cube.jpg", L"Assets/SkeletonCubeModel/CubeRough.jpg", L"Assets/SkeletonCubeModel/CubeNormal.jpg", 90, -35);
		totem3 = new ModeloRR(d3dDevice, d3dContext, "Assets/SkeletonCubeModel/SkeletonCube.obj", L"Assets/SkeletonCubeModel/Cube.jpg", L"Assets/SkeletonCubeModel/CubeRough.jpg", L"Assets/SkeletonCubeModel/CubeNormal.jpg", 0, -150);
		totem4 = new ModeloRR(d3dDevice, d3dContext, "Assets/SkeletonCubeModel/SkeletonCube.obj", L"Assets/SkeletonCubeModel/Cube.jpg", L"Assets/SkeletonCubeModel/CubeRough.jpg", L"Assets/SkeletonCubeModel/CubeNormal.jpg", 0, 125);
		totem5 = new ModeloRR(d3dDevice, d3dContext, "Assets/SkeletonCubeModel/SkeletonCube.obj", L"Assets/SkeletonCubeModel/Cube.jpg", L"Assets/SkeletonCubeModel/CubeRough.jpg", L"Assets/SkeletonCubeModel/CubeNormal.jpg", 200, 100);

		sandman = new ModeloRR(d3dDevice, d3dContext, "Assets/SandMan/SandMan.obj", L"Assets/SandMan/SandManColor.png", L"Assets/SandMan/SandManSpecular2.png", L"Assets/SandMan/SandManNormal.png", 90, -90);
		sandman2 = new ModeloRR(d3dDevice, d3dContext, "Assets/SandMan/SandMan.obj", L"Assets/SandMan/SandManColor.png", L"Assets/SandMan/SandManSpecular2.png", L"Assets/SandMan/SandManNormal.png", 50, 100);
		sandman3 = new ModeloRR(d3dDevice, d3dContext, "Assets/SandMan/SandMan.obj", L"Assets/SandMan/SandManColor.png", L"Assets/SandMan/SandManSpecular2.png", L"Assets/SandMan/SandManNormal.png", 175, 50);
		sandman4 = new ModeloRR(d3dDevice, d3dContext, "Assets/SandMan/SandMan.obj", L"Assets/SandMan/SandManColor.png", L"Assets/SandMan/SandManSpecular2.png", L"Assets/SandMan/SandManNormal.png", -125, 50);
		sandman5 = new ModeloRR(d3dDevice, d3dContext, "Assets/SandMan/SandMan.obj", L"Assets/SandMan/SandManColor.png", L"Assets/SandMan/SandManSpecular2.png", L"Assets/SandMan/SandManNormal.png", 50, 0);
		
		skeleton = new ModeloRR(d3dDevice, d3dContext, "Assets/Skeleton/Skeleton.obj", L"Assets/Skeleton/SkeletonColor.png", L"Assets/Skeleton/lambert2_Height.png", L"Assets/Skeleton/SkeletonNormal.png", 140, 115);
		skeleton2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Skeleton/Skeleton.obj", L"Assets/Skeleton/SkeletonColor.png", L"Assets/Skeleton/lambert2_Height.png", L"Assets/Skeleton/SkeletonNormal.png", 175, -25);
		skeleton3 = new ModeloRR(d3dDevice, d3dContext, "Assets/Skeleton/Skeleton.obj", L"Assets/Skeleton/SkeletonColor.png", L"Assets/Skeleton/lambert2_Height.png", L"Assets/Skeleton/SkeletonNormal.png", -25, 150);
		skeleton4 = new ModeloRR(d3dDevice, d3dContext, "Assets/Skeleton/Skeleton.obj", L"Assets/Skeleton/SkeletonColor.png", L"Assets/Skeleton/lambert2_Height.png", L"Assets/Skeleton/SkeletonNormal.png", 100, 35);
		skeleton5 = new ModeloRR(d3dDevice, d3dContext, "Assets/Skeleton/Skeleton.obj", L"Assets/Skeleton/SkeletonColor.png", L"Assets/Skeleton/lambert2_Height.png", L"Assets/Skeleton/SkeletonNormal.png", -25, -100);

		stone = new ModeloRR(d3dDevice, d3dContext, "Assets/Stone/Stone.obj", L"Assets/Stone/StoneColor.jpg", L"Assets/Stone/StoneRough.jpg", L"Assets/Stone/StoneNormal.jpg", 50, 25);

		camaraTipo = true;
		rotCam = 0.0;

		//vida
		vida = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/UI/health_full.png");
		vida1 = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/UI/health_1.png");
		vida2 = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/UI/health_2.png");

		//texto
		texto = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/UI/font.jpg", XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		texto2 = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/UI/font.jpg", XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		gameOver = new GUI(d3dDevice, d3dContext, 1.00, 1.80, L"Assets/UI/game_overJan.png");
		ganaste = new GUI(d3dDevice, d3dContext, 1.00, 1.80, L"Assets/UI/you_win.png");
		
	}

	~DXRR()
	{
		LiberaD3D();
		m_XACT3.Terminate();
	}
	
	bool IniciaD3D(HWND hWnd)
	{
		this->hInstance = hInstance;
		this->hWnd = hWnd;

		//obtiene el ancho y alto de la ventana donde se dibuja
		RECT dimensions;
		GetClientRect(hWnd, &dimensions);
		unsigned int width = dimensions.right - dimensions.left;
		unsigned int heigth = dimensions.bottom - dimensions.top;

		//Las formas en como la pc puede ejecutar el DX11, la mas rapida es D3D_DRIVER_TYPE_HARDWARE pero solo se puede usar cuando lo soporte el hardware
		//otra opcion es D3D_DRIVER_TYPE_WARP que emula el DX11 en los equipos que no lo soportan
		//la opcion menos recomendada es D3D_DRIVER_TYPE_SOFTWARE, es la mas lenta y solo es util cuando se libera una version de DX que no sea soportada por hardware
		D3D_DRIVER_TYPE driverTypes[]=
		{
			D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
		};
		unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

		//La version de DX que utilizara, en este caso el DX11
		D3D_FEATURE_LEVEL featureLevels[]=
		{
			D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
		};
		unsigned int totalFeaturesLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = heigth;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		HRESULT result;
		unsigned int driver = 0, creationFlags = 0;
		for(driver = 0; driver<totalDriverTypes; driver++)
		{
			result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0,
				creationFlags, featureLevels, totalFeaturesLevels, 
				D3D11_SDK_VERSION, &swapChainDesc, &swapChain,
				&d3dDevice, &featureLevel, &d3dContext);

			if(SUCCEEDED(result))
			{
				driverType = driverTypes[driver];
				break;
			}
		}

		if(FAILED(result))
		{

			//Error al crear el Direct3D device
			return false;
		}
		
		ID3D11Texture2D* backBufferTexture;
		result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
		if(FAILED(result))
		{
			//"Error al crear el swapChainBuffer
			return false;
		}

		result = d3dDevice->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget);
		if(backBufferTexture)
			backBufferTexture->Release();

		if(FAILED(result))
		{
			//Error al crear el renderTargetView
			return false;
		}


		D3D11_VIEWPORT viewport;
		viewport.Width = (FLOAT)width;
		viewport.Height = (FLOAT)heigth;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		d3dContext->RSSetViewports(1, &viewport);

		D3D11_TEXTURE2D_DESC depthTexDesc;
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = width;
		depthTexDesc.Height = heigth;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthTexDesc.CPUAccessFlags = 0;
		depthTexDesc.MiscFlags = 0;
		
		result = d3dDevice->CreateTexture2D(&depthTexDesc, NULL, &depthTexture);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear la DepthTexture", MB_OK);
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = depthTexDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		result = d3dDevice->CreateDepthStencilView(depthTexture, &descDSV, &depthStencilView);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el depth stencil target view", MB_OK);
			return false;
		}

		d3dContext->OMSetRenderTargets(1, &backBufferTarget, depthStencilView);

		// Inicializar XACT
		bool res = m_XACT3.Initialize();
		if (!res) return false;
		res = m_XACT3.LoadWaveBank(L"Assets\\Sonido\\WaveBank.xwb");
		if (!res) return false;
		res = m_XACT3.LoadSoundBank(L"Assets\\Sonido\\SoundBank.xsb");
		if (!res) return false;

		// Reproducir m�sica de fondo
		cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("CreepingUpOnYou_Godmode");
		m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);

		// Efecto de sonido
		//cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("Golpe");

		return true;			
		
	}

	void LiberaD3D(void)
	{
		if(depthTexture)
			depthTexture->Release();
		if(depthStencilView)
			depthStencilView->Release();
		if(backBufferTarget)
			backBufferTarget->Release();
		if(swapChain)
			swapChain->Release();
		if(d3dContext)
			d3dContext->Release();
		if(d3dDevice)
			d3dDevice->Release();

		depthTexture = 0;
		depthStencilView = 0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
	}
	
	void Render(void)
	{
		//levelTime->updateTiempo();    checar si crear una nueva funcion update (minuto 1:50)
		pintar();
		rotCam += izqder;
		float sphere[3] = { 0,0,0 };
		float prevPos[3] = { camara->posCam.x, camara->posCam.z, camara->posCam.z };
		static float angle = 0.0f;
		angle += 0.005;
		if (angle >= 360) angle = 0.0f;
		bool collide = false;
		if( d3dContext == 0 )
			return;

		if (camara->posCam.x > 240) {
			camara->posCam = camara->pastCam;
		}
		else if (camara->posCam.x < -240) {
			camara->posCam = camara->pastCam;
		}
		else if (camara->posCam.z < -240) {
			camara->posCam = camara->pastCam;
		}
		else if (camara->posCam.z > 240) {
			camara->posCam = camara->pastCam;
		}

		float clearColor[4] = { 0, 0, 0, 1.0f };
		d3dContext->ClearRenderTargetView( backBufferTarget, clearColor );
		d3dContext->ClearDepthStencilView( depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

		/*if (camaraTipo == true) {
			camara->posCam.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 15;
		}
		else if (camaraTipo == false) {
			camara->posCam3P.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 20;
		}*/

		camara->posCam.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 15;
		camara->posCam3P.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 20; //altura de la camara en tercera persona

		camara->UpdateCam(vel, arriaba, izqder, camaraTipo);

		skydome->Update(camara->vista, camara->proyeccion);

		float camPosXZ[2] = { camara->posCam.x, camara->posCam.z };

		TurnOffDepth();
		skydome->Render(camara->posCam, contadorGLSL);
		TurnOnDepth();
		//terreno->Draw(camara->vista, camara->proyeccion);
		terreno->Draw(camara->vista, camara->proyeccion, luzAmbiental, luzDifusa, luzEspecular, fad, fa, fas, dirluz); 
		//TurnOnAlphaBlending();
		billboard->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-11, -78, 4, 5, uv1, uv2, uv3, uv4, frameBillboard, true);
			
		//TurnOffAlphaBlending();

		static float oleaje = 0;
		oleaje += 0.0001;
		oasis->posx = -130;
		oasis->posz = 175;
		oasis->DrawWater(camara->vista, camara->proyeccion, camara->posCam, terreno->Superficie(oasis->getPosX(), oasis->getPosZ()) - 12, oleaje);

		palma->Draw(camara->vista, camara->proyeccion, camara->posCam, 75, 150, terreno->Superficie(75, 150) -13, 50, uv1, uv2, uv3, uv4, frameBillboard, false);
		palma2->Draw(camara->vista, camara->proyeccion, camara->posCam, 25, 150, terreno->Superficie(25, 150) - 9, 35, uv1, uv2, uv3, uv4, frameBillboard, false);
		bush->Draw(camara->vista, camara->proyeccion, camara->posCam, 70, 150, terreno->Superficie(70, 150) - 2, 8, uv1, uv2, uv3, uv4, frameBillboard, false);
		bush2->Draw(camara->vista, camara->proyeccion, camara->posCam, 40, 150, terreno->Superficie(40, 150) - 2, 12, uv1, uv2, uv3, uv4, frameBillboard, false);
		cactus->Draw(camara->vista, camara->proyeccion, camara->posCam, 150, -150, terreno->Superficie(150, -150) - 4, 15, uv1, uv2, uv3, uv4, frameBillboard, false);
		cactus2->Draw(camara->vista, camara->proyeccion, camara->posCam, -100, -150, terreno->Superficie(-100, -150) - 4, 15, uv1, uv2, uv3, uv4, frameBillboard, false);

		//prota->setPosX(camara->hdveo.x);
		//prota->setPosZ(camara->hdveo.z);                                                                                         //xm_pi
		//prota->Draw(camara->vista, camara->proyeccion, terreno->Superficie(prota->getPosX(), prota->getPosZ()) + 2.5, camara->posCam, 10.0f, rotCam + XM_PI, 'Y', 1, camaraTipo, true);

		nave->setPosX(camara->hdveo.x);
		nave->setPosZ(camara->hdveo.z);
		nave->Draw(camara->vista, camara->proyeccion, 15, terreno->Superficie(nave->getPosX(), nave->getPosZ()), 0, camara->posCam, 10.0f, rotCam + XM_PI, 'Y', 3, camaraTipo, true);
		
		hangar->Draw(camara->vista, camara->proyeccion, 75, terreno->Superficie(75, -140), -140, camara->posCam, 10.0f, 0, 'A', 9.0, camaraTipo, false); //�ltimo valor es la escala
		vivienda->Draw(camara->vista, camara->proyeccion, 140, terreno->Superficie(140, 150), 150, camara->posCam, 10.0f, 0, 'A', 1, camaraTipo, false);
		vivienda2->Draw(camara->vista, camara->proyeccion, -125, terreno->Superficie(-125, -75), -75, camara->posCam, 10.0f, 0, 'A', 1, camaraTipo, false);
		//cheep->Draw(camara->vista, camara->proyeccion, 0, terreno->Superficie(0, -30), -30, camara->posCam, 1.0f, 0, 'A', 5.0, camaraTipo, false);
		
		
		
		waterWell->Draw(camara->vista, camara->proyeccion, -125, terreno->Superficie(-125, 125) - 3, 125, camara->posCam, 1.0f, 0, 'A', 3, camaraTipo, false);
		stone->Draw(camara->vista, camara->proyeccion, 125, terreno->Superficie(125, -150), -150, camara->posCam, 10.0f, 0, 'A', 9.0, camaraTipo, false);

		
		

		
		
		
		
		 
        //specular //cambiar letra //escala

		/*if (posicionSandmanVX <= 0) {
			posicionSandmanVX += 0.1f;
			sandman4->setPosX(posicionSandmanVX);
		}*/

		if (cantTotems < 5 && !tenemosHacha) {
			TurnOnAlphaBlending();
			texto2->DrawTextW(-0.50, 0.80, "Objetivo: Recoge todos los totems.", 0.015); //-0.50, 0.80
			TurnOffAlphaBlending();
			//axe->Draw(camara->vista, camara->proyeccion, 175, terreno->Superficie(175, 115), 115, camara->posCam, 1.0f, 0, 'A', 2, camaraTipo, false);
			//ganaste->Draw(0, 0);

		}

		if (cantTotems == 5 && !tenemosHacha) {
			TurnOnAlphaBlending();
			texto2->DrawTextW(-0.50, 0.80, "Objetivo: Busca y recoge el hacha.", 0.015); //-0.50, 0.80
			TurnOffAlphaBlending();
			axe->Draw(camara->vista, camara->proyeccion, 175, terreno->Superficie(175, 115), 115, camara->posCam, 1.0f, 0, 'A', 2, camaraTipo, false);
			//ganaste->Draw(0, 0);

		}

		int skeletonVivos = 0, sandmansVivos = 0;

		for (int i = 0; i < sizeof(SkeletonLive); i++) {
			if (SkeletonLive[i] == true) {
				skeletonVivos++;
			}
		}

		for (int i = 0; i < sizeof(SandmanLive); i++) {
			if (SandmanLive[i] == true) {
				sandmansVivos++;
			}
		}

		int contadorDeEsqueletosMuertos = 0;
		for (int i = 0; i < sizeof(SkeletonLive); i++) {
			if (SkeletonLive[i] == true) {
				break;
				/*skeletonVivos++;*/
			} 
			
			contadorDeEsqueletosMuertos++;
			if (contadorDeEsqueletosMuertos == 5) {
				mostrarCubeta = true;
			}
		}

		int contadorDeSandmansMuertos = 0;
		for (int i = 0; i < sizeof(SandmanLive); i++) {
			if (SandmanLive[i] == true) {
				break;
				//sandmansVivos++;
			}

			contadorDeSandmansMuertos++;
			if (contadorDeSandmansMuertos == 5) {
				mostrarPiedra = true;
			}
		}


		if (mostrarCubeta && !tenemosCubeta) {
			//tenemosHacha = false;
			texto2->DrawTextW(-0.50, 0.80, "Objetivo: Recoge la cubeta.", 0.015); //-0.50, 0.80
			bucket->Draw(camara->vista, camara->proyeccion, -25, terreno->Superficie(-25, -150), -150, camara->posCam, 1.0f, 0, 'A', 2, camaraTipo, false);
		}

		if (tenemosCubeta && !cubetaLlena && !mostrarPiedra) {
			texto2->DrawTextW(-0.50, 0.80, "Objetivo: Llena la cubeta.", 0.015); //-0.50, 0.80
			texto->DrawTextW(-0.95, 0.70, "Inventario:  Cubeta vacia.", 0.015);
		}

		if (tenemosCubeta && cubetaLlena) {
			texto2->DrawTextW(-0.50, 0.80, "Objetivo: Elimina a los sandmans.", 0.015); //-0.50, 0.80
			texto->DrawTextW(-0.95, 0.70, "Inventario:  Cubeta llena.", 0.015);
		}

		if (mostrarPiedra && !jugadorGano) {
			texto2->DrawTextW(-0.50, 0.80, "Objetivo: Dirigete a la piedra antigua.", 0.015); //-0.50, 0.80
			stone->Draw(camara->vista, camara->proyeccion, stone->getPosX(), terreno->Superficie(stone->getPosX(), stone->getPosZ()) - 20, stone->getPosZ(), camara->posCam, 10.0f, 0, 'A', 9.0, camaraTipo, false);
			mostrarSandmans = false;

		}

		


		//vida->Draw(-0.86, -0.50);  //esquina inferior izq -0.86, -0.50   esquina inferior derecha 0.45, -0.50

		string totems = to_string(cantTotems);
		string skeletonVivosS = to_string(skeletonVivos);
		string sandmansVivosS = to_string(sandmansVivos);

		TurnOnAlphaBlending();

		if (mostarTotems) {
			texto->DrawTextW(-0.95, 0.80, "Totems:   " + totems + ".", 0.015); // esquina sup izq -0.50, 0.80   inf derecha  -0.95, -0.40
		}

		if (mostrarSkeletons) {
			texto->DrawTextW(-0.95, 0.80, "Skeletons:   " + skeletonVivosS + ".", 0.015); // esquina sup izq -0.50, 0.80   inf derecha  -0.95, -0.40
		}

		if (mostrarSandmans) {
			texto->DrawTextW(-0.95, 0.80, "Sandmans:   " + sandmansVivosS + ".", 0.015); // esquina sup izq -0.50, 0.80   inf derecha  -0.95, -0.40
		}

		if (!jugadorPerdio && !jugadorGano) {
			texto->DrawTextW(-0.95, 0.90, "Tiempo:  " + texto->Time(segundos), 0.015);  // esquina sup izq -0.95, 0.90  inf derecha  -0.95, -0.50
		}

		if (tenemosHacha && !mostrarCubeta) {
			texto->DrawTextW(-0.95, 0.70, "Inventario:  Hacha.", 0.015);
			texto2->DrawTextW(-0.50, 0.80, "Objetivo: Elimina a los esqueletos.", 0.015); //-0.50, 0.80
		}

		
		if (!jugadorGano) {
			tiemTardado = 601 - segundos;
		}
		//string tiempoS = to_string(tiemTardado);

		if (jugadorGano) {

			texto2->DrawTextW(-0.50, 0.80, "Tiempo jugado: " + texto->Time(tiemTardado) + ".", 0.015); //-0.50, 0.80
		}


		TurnOffAlphaBlending();

		segundos -= 0.02;

	#pragma region Colisiones
		if (camaraTipo == true) {
			
			float radioPared = 40;

			if (isPointInsideSphere(camara->getPos(), vivienda->getSphere(radioPared, vivienda->getPosX(), vivienda->getPosZ()))) {
				camara->posCam = camara->pastCam;
			}

			float radioPasillo = 70;

			if (isPointInsideSphere(camara->getPos(), vivienda2->getSphere(radioPasillo, vivienda2->getPosX(), vivienda2->getPosZ()))) {
				camara->posCam = camara->pastCam;
			}

			float radioHangar = 60;

			if (isPointInsideSphere(camara->getPos(), hangar->getSphere(radioHangar, hangar->getPosX(), hangar->getPosZ()))) {
				camara->posCam = camara->pastCam;
			}

			int x = 0;

			float radioSandman = 10;

			x = 0;
			if (SandmanLive[x]) {
				sandman->Draw(camara->vista, camara->proyeccion, 90, terreno->Superficie(sandman->getPosX(), sandman->getPosZ()), -90, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), sandman->getSphere(radioSandman, sandman->getPosX(), sandman->getPosZ()))) {
					camara->posCam = camara->pastCam;
					if (!cubetaLlena) {
						if (SandmanV[x] && !SandmanVTemporal[x]) {
							vidas--;
						}
						SandmanVTemporal[x] = SandmanV[x];
					}
					else {
						SandmanLive[x] = false;
						cubetaLlena = false;
					}
				}
				else {
					SandmanVTemporal[x] = false;
				}
			}

			x = 1;
			if (SandmanLive[x]) {
				sandman2->Draw(camara->vista, camara->proyeccion, 50, terreno->Superficie(sandman2->getPosX(), sandman2->getPosZ()), 100, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), sandman2->getSphere(radioSandman, sandman2->getPosX(), sandman2->getPosZ()))) {
					camara->posCam = camara->pastCam;
					if (!cubetaLlena) {
						if (SandmanV[x] && !SandmanVTemporal[x]) {
							vidas--;
						}
						SandmanVTemporal[x] = SandmanV[x];
					}
					else {
						SandmanLive[x] = false;
						cubetaLlena = false;
					}
				}
				else {
					SandmanVTemporal[x] = false;
				}
			}

			x = 2;
			if (SandmanLive[x]) {
				sandman3->Draw(camara->vista, camara->proyeccion, 175, terreno->Superficie(sandman3->getPosX(), sandman3->getPosZ()), 50, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), sandman3->getSphere(radioSandman, sandman3->getPosX(), sandman3->getPosZ()))) {
					camara->posCam = camara->pastCam;
					if (!cubetaLlena) {
						if (SandmanV[x] && !SandmanVTemporal[x]) {
							vidas--;
						}
						SandmanVTemporal[x] = SandmanV[x];
					}
					else {
						SandmanLive[x] = false;
						cubetaLlena = false;
					}
				}
				else {
					SandmanVTemporal[x] = false;
				}
			}

			x = 3;
			if (SandmanLive[x]) {
				sandman4->Draw(camara->vista, camara->proyeccion, sandman4->getPosX(), terreno->Superficie(sandman4->getPosX(), sandman4->getPosZ()), 50, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), sandman4->getSphere(radioSandman, sandman4->getPosX(), sandman4->getPosZ()))) {
					camara->posCam = camara->pastCam;
					if (!cubetaLlena) {
						if (SandmanV[x] && !SandmanVTemporal[x]) {
							vidas--;
						}
						SandmanVTemporal[x] = SandmanV[x];
					}
					else {
						SandmanLive[x] = false;
						cubetaLlena = false;
					}
				}
				else {
					SandmanVTemporal[x] = false;
				}
			}

			x = 4;
			if (SandmanLive[x]) {
				sandman5->Draw(camara->vista, camara->proyeccion, 50, terreno->Superficie(sandman5->getPosX(), sandman5->getPosZ()), 0, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), sandman5->getSphere(radioSandman, sandman5->getPosX(), sandman5->getPosZ()))) {
					camara->posCam = camara->pastCam;
					if (!cubetaLlena) {
						if (SandmanV[x] && !SandmanVTemporal[x]) {
							vidas--;
						}
						SandmanVTemporal[x] = SandmanV[x];
					}
					else {
						SandmanLive[x] = false;
						cubetaLlena = false;
					}
				}
				else {
					SandmanVTemporal[x] = false;
				}
			}

			float radioSkeleton = 10;

			x = 0;
			if (SkeletonLive[x]) {
				skeleton->Draw(camara->vista, camara->proyeccion, 140, terreno->Superficie(skeleton->getPosX(), skeleton->getPosZ()), 115, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), skeleton->getSphere(radioSkeleton, skeleton->getPosX(), skeleton->getPosZ()))) {
					camara->posCam = camara->pastCam;

					if (!tenemosHacha) {
						if (SkeletonV[x] && !SkeletonVTemporal[x]) {
							vidas--;
						}
						SkeletonVTemporal[x] = SkeletonV[x];
					}
					else {
						SkeletonLive[x] = false;
					}
				}
				else {
					SkeletonVTemporal[x] = false;
				}
			}
			x = 1;
			if (SkeletonLive[x]) {
				skeleton2->Draw(camara->vista, camara->proyeccion, 175, terreno->Superficie(skeleton2->getPosX(), skeleton2->getPosZ()), -25, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), skeleton2->getSphere(radioSkeleton, skeleton2->getPosX(), skeleton2->getPosZ()))) {
					camara->posCam = camara->pastCam;
					if (!tenemosHacha) {
						if (SkeletonV[x] && !SkeletonVTemporal[x]) {
							vidas--;
						}
						SkeletonVTemporal[x] = SkeletonV[x];
					}
					else {
						SkeletonLive[x] = false;
					}
				}
				else {
					SkeletonVTemporal[x] = false;
				}
			}

			x = 2;
			if (SkeletonLive[x]) {
				skeleton3->Draw(camara->vista, camara->proyeccion, -25, terreno->Superficie(skeleton3->getPosX(), skeleton3->getPosZ()), 150, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), skeleton3->getSphere(radioSkeleton, skeleton3->getPosX(), skeleton3->getPosZ()))) {
					camara->posCam = camara->pastCam;
					if (!tenemosHacha) {
						if (SkeletonV[x] && !SkeletonVTemporal[x]) {
							vidas--;
						}
						SkeletonVTemporal[x] = SkeletonV[x];
					}
					else {
						SkeletonLive[x] = false;
					}
				}
				else {
					SkeletonVTemporal[x] = false;
				}
			}

			x = 3;
			if (SkeletonLive[x]) {
				skeleton4->Draw(camara->vista, camara->proyeccion, 100, terreno->Superficie(skeleton4->getPosX(), skeleton4->getPosZ()), 35, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), skeleton4->getSphere(radioSkeleton, skeleton4->getPosX(), skeleton4->getPosZ()))) {
					camara->posCam = camara->pastCam;
					if (!tenemosHacha) {
						if (SkeletonV[x] && !SkeletonVTemporal[x]) {
							vidas--;
						}
						SkeletonVTemporal[x] = SkeletonV[x];
					}
					else {
						SkeletonLive[x] = false;
					}
				}
				else {
					SkeletonVTemporal[x] = false;
				}
			}

			x = 4;
			if (SkeletonLive[x]) {
				skeleton5->Draw(camara->vista, camara->proyeccion, -25, terreno->Superficie(skeleton5->getPosX(), skeleton5->getPosZ()), -100, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), skeleton5->getSphere(radioSkeleton, skeleton5->getPosX(), skeleton5->getPosZ()))) {
					camara->posCam = camara->pastCam;
					if (!tenemosHacha) {
						if (SkeletonV[x] && !SkeletonVTemporal[x]) {
							vidas--;
						}
						SkeletonVTemporal[x] = SkeletonV[x];
					}
					else {
						SkeletonLive[x] = false;
					}
				}
				else {
					SkeletonVTemporal[x] = false;
				}
			}


			float radioTotem = 5;
			if (fueraTotem) {
				totem->Draw(camara->vista, camara->proyeccion, 150, terreno->Superficie(150, -90) + 5, -90, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), totem->getSphere(radioTotem, totem->getPosX(), totem->getPosZ()))) {
					camara->posCam = camara->pastCam;
					cantTotems++;
					fueraTotem = false;
				}
			}
			if (fueraTotem2) {
				totem2->Draw(camara->vista, camara->proyeccion, 90, terreno->Superficie(90, -35) + 5, -35, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), totem2->getSphere(radioTotem, totem2->getPosX(), totem2->getPosZ()))) {
					camara->posCam = camara->pastCam;
					cantTotems++;
					fueraTotem2 = false;
				}
			}
			if (fueraTotem3) {
				totem3->Draw(camara->vista, camara->proyeccion, 0, terreno->Superficie(0, -150) + 5, -150, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), totem3->getSphere(radioTotem, totem3->getPosX(), totem3->getPosZ()))) {
					camara->posCam = camara->pastCam;
					cantTotems++;
					fueraTotem3 = false;
				}
			}
			
			if (fueraTotem4) {
				totem4->Draw(camara->vista, camara->proyeccion, 0, terreno->Superficie(0, 125) + 5, 125, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), totem4->getSphere(radioTotem, totem4->getPosX(), totem4->getPosZ()))) {
					camara->posCam = camara->pastCam;
					cantTotems++;
					fueraTotem4 = false;
				}
			}
			
			if (fueraTotem5) {
				totem5->Draw(camara->vista, camara->proyeccion, 200, terreno->Superficie(200, 100) + 5, 100, camara->posCam, 1.0f, 0, 'A', 1, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), totem5->getSphere(radioTotem, totem5->getPosX(), totem5->getPosZ()))) {
					camara->posCam = camara->pastCam;
					cantTotems++;
					fueraTotem5 = false;
				}
			}

			// Colisi�n con hacha
			float radioHacha = 5;
			if (cantTotems == 5 && !tenemosHacha) {
				if (isPointInsideSphere(camara->getPos(), axe->getSphere(radioHacha, axe->getPosX(), axe->getPosZ()))) {
					camara->posCam = camara->pastCam;
					tenemosHacha = true;
					mostarTotems = false;
					mostrarSkeletons = true;
					corazonActivado[1] = true;
				}
			}

			// Colisi�n con cubeta
			float radioCubeta = 5;
			if (!tenemosCubeta && mostrarCubeta) {
				if (isPointInsideSphere(camara->getPos(), bucket->getSphere(radioCubeta, bucket->getPosX(), bucket->getPosZ()))) {
					camara->posCam = camara->pastCam;
					tenemosCubeta = true;
					mostrarCubeta = false;
					mostrarSkeletons = false;
					mostrarSandmans = true;
					corazonActivado[2] = true;
				}
			}

			// Colisi�n con cubeta
			float radioPozo = 18;
			if (tenemosCubeta && !cubetaLlena) {
				if (isPointInsideSphere(camara->getPos(), waterWell->getSphere(radioPozo, waterWell->getPosX(), waterWell->getPosZ()))) {
					camara->posCam = camara->pastCam;
					cubetaLlena = true;
				}
			}

			// Colisi�n con la piedra antigua
			float radioPiedra = 25;
			if (mostrarPiedra) {
				if (isPointInsideSphere(camara->getPos(), stone->getSphere(radioPiedra, stone->getPosX(), stone->getPosZ()))) {
					camara->posCam = camara->pastCam;
					//cubetaLlena = true;
					jugadorGano = true;
				}
			}

			// Colisi�n con el coraz�n
			float radioCorazon = 5;
			x = 0;
			if (corazonActivado[x]) {
				heart->Draw(camara->vista, camara->proyeccion, heart->getPosX(), terreno->Superficie(heart->getPosX(), heart->getPosZ()), heart->getPosZ(), camara->posCam, 1.0f, 0, 'A', 2, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), heart->getSphere(radioCorazon, heart->getPosX(), heart->getPosZ()))) {
					camara->posCam = camara->pastCam;
					//cubetaLlena = true;
					/*ganaste->Draw(0, 0);*/
					if (vidas > 0 && vidas < 3) {
						vidas++;
						corazonActivado[x] = false;
					}
					
				}
			}

			x = 1;
			if (corazonActivado[x]) {
				heart1->Draw(camara->vista, camara->proyeccion, heart1->getPosX(), terreno->Superficie(heart1->getPosX(), heart1->getPosZ()), heart1->getPosZ(), camara->posCam, 1.0f, 0, 'A', 2, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), heart1->getSphere(radioCorazon, heart1->getPosX(), heart1->getPosZ()))) {
					camara->posCam = camara->pastCam;
					//cubetaLlena = true;
					/*ganaste->Draw(0, 0);*/
					if (vidas > 0 && vidas < 3) {
						vidas++;
						corazonActivado[x] = false;
					}

				}
			}

			x = 2;
			if (corazonActivado[x]) {
				heart2->Draw(camara->vista, camara->proyeccion, heart2->getPosX(), terreno->Superficie(heart2->getPosX(), heart2->getPosZ()), heart2->getPosZ(), camara->posCam, 1.0f, 0, 'A', 2, camaraTipo, false);
				if (isPointInsideSphere(camara->getPos(), heart2->getSphere(radioCorazon, heart2->getPosX(), heart2->getPosZ()))) {
					camara->posCam = camara->pastCam;
					//cubetaLlena = true;
					/*ganaste->Draw(0, 0);*/
					if (vidas > 0 && vidas < 3) {
						vidas++;
						corazonActivado[x] = false;
					}

				}
			}


		}
	#pragma endregion

		switch (vidas)
		{
			case 3: {
				vida->Draw(-0.86, -0.50);
			} break;

			case 2: {
				vida2->Draw(-0.86, -0.50);
			} break;

			case 1: {
				vida1->Draw(-0.86, -0.50);
			} break;

			case 0: {
				gameOver->Draw(0, 0);
				jugadorPerdio = true;
			} break;

			default: {
				gameOver->Draw(0, 0);
				jugadorPerdio = true;
			} break;
		}

		if (segundos < 0) {
			gameOver->Draw(0, 0);
			jugadorPerdio = true;
		}

		if (jugadorGano) {
			ganaste->Draw(0, 0);
		}


		swapChain->Present( 1, 0 );
	}

	bool isPointInsideSphere(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2])
			collition = true;

		if (distance > 5) {
			haColisionado = false;
		}
		return collition;
	}

	//Activa el alpha blend para dibujar con transparencias
	void TurnOnAlphaBlending()
	{
		float blendFactor[4];
		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;
		HRESULT result;

		D3D11_BLEND_DESC descABSD;
		ZeroMemory(&descABSD, sizeof(D3D11_BLEND_DESC));
		descABSD.RenderTarget[0].BlendEnable = TRUE;
		descABSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descABSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descABSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		result = d3dDevice->CreateBlendState(&descABSD, &alphaBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
	}

	//Regresa al blend normal(solido)
	void TurnOffAlphaBlending()
	{
		D3D11_BLEND_DESC descCBSD;
		ZeroMemory(&descCBSD, sizeof(D3D11_BLEND_DESC));
		descCBSD.RenderTarget[0].BlendEnable = FALSE;
		descCBSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descCBSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descCBSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;
		HRESULT result;

		result = d3dDevice->CreateBlendState(&descCBSD, &commonBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(commonBlendState, NULL, 0xffffffff);
	}

	void TurnOnDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDSD;
		ZeroMemory(&descDSD, sizeof(descDSD));
		descDSD.DepthEnable = true;
		descDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDSD.StencilEnable=true;
		descDSD.StencilReadMask = 0xFF;
		descDSD.StencilWriteMask = 0xFF;
		descDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDSD, &depthStencilState);
		
		d3dContext->OMSetDepthStencilState(depthStencilState, 1);
	}

	void TurnOffDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDDSD;
		ZeroMemory(&descDDSD, sizeof(descDDSD));
		descDDSD.DepthEnable = false;
		descDDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDDSD.StencilEnable=true;
		descDDSD.StencilReadMask = 0xFF;
		descDDSD.StencilWriteMask = 0xFF;
		descDDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDDSD, &depthStencilDisabledState);
		d3dContext->OMSetDepthStencilState(depthStencilDisabledState, 1);
	}

	void billCargaFuego()
	{
		uv1[0].u = .125;
		uv2[0].u = .125;
		uv3[0].u = 0;
		uv4[0].u = 0;

		uv1[0].v = .25;
		uv2[0].v = 0;
		uv3[0].v = 0;
		uv4[0].v = .25;


		for (int j = 0; j < 8; j++) {
			uv1[j].u = uv1[0].u + (j * .125);
			uv2[j].u = uv2[0].u + (j * .125);
			uv3[j].u = uv3[0].u + (j * .125);
			uv4[j].u = uv4[0].u + (j * .125);

			uv1[j].v = .25;
			uv2[j].v = 0;
			uv3[j].v = 0;
			uv4[j].v = .25;
		}
		for (int j = 0; j < 8; j++) {
			uv1[j + 8].u = uv1[0].u + (j * .125);
			uv2[j + 8].u = uv2[0].u + (j * .125);
			uv3[j + 8].u = uv3[0].u + (j * .125);
			uv4[j + 8].u = uv4[0].u + (j * .125);

			uv1[j + 8].v = .5;
			uv2[j + 8].v = .25;
			uv3[j + 8].v = .25;
			uv4[j + 8].v = .5;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 16].u = uv1[0].u + (j * .125);
			uv2[j + 16].u = uv2[0].u + (j * .125);
			uv3[j + 16].u = uv3[0].u + (j * .125);
			uv4[j + 16].u = uv4[0].u + (j * .125);

			uv1[j + 16].v = .75;
			uv2[j + 16].v = .5;
			uv3[j + 16].v = .5;
			uv4[j + 16].v = .75;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 24].u = uv1[0].u + (j * .125);
			uv2[j + 24].u = uv2[0].u + (j * .125);
			uv3[j + 24].u = uv3[0].u + (j * .125);
			uv4[j + 24].u = uv4[0].u + (j * .125);

			uv1[j + 24].v = 1;
			uv2[j + 24].v = .75;
			uv3[j + 24].v = .75;
			uv4[j + 24].v = 1;
		}
	}

	void pintar() {

		Contador++;

		if (Contador % 20 == 0)
		{

			if (ContFramesMa�ana != 0 && ContFramesTarde != 0 && ContFramesNoche != 0) //cuenta cuantas horas para que sea tarde
			{
				ContFramesMa�ana--;
				contadorGLSL++;
			}

			if (ContFramesTarde != 0 && ContFramesMa�ana == 0 && ContFramesNoche != 0)//cuenta cuantas horas para que sea noche
			{
				ContFramesTarde--;
				contadorGLSL++;
			}

			if (ContFramesMa�ana == 0 && ContFramesTarde == 0 && ContFramesNoche != 0)//cuenta cuantas horas para que sea dia
			{
				ContFramesNoche--;
				contadorGLSL++;
			}

			if (ContFramesNoche == 0)
			{
				ContFramesMa�ana = 80;
				ContFramesNoche = 40;
				ContFramesTarde = 80;
				contadorGLSL = 0;
			}
		}

		if (angle < 180.0f)
		{
			if (angle > 40.0f && angle < 140.0f)
				angle += 0.005f;
			else
			{
				angle += 0.010f;
			}
		}

		if (angle >= 180.0f)
			angle += 0.030f;


		if (angle >= 360.0f)
			angle = 0.0f;

		//angulos de iluminacion
		luzy = sin((angle * 41.2723) * PI / 180) * 350;
		luzx = 0;
		luzz = cos((angle * 41.2723) * PI / 180) * 350;

		dirluz.x = luzx;
		dirluz.y = luzy;
		dirluz.z = luzz;

		skydome->Update(camara->vista, camara->proyeccion);
		TurnOffDepth();
		skydome->Render(camara->posCam, contadorGLSL);
		TurnOnDepth();
	}
		
			
};
#endif