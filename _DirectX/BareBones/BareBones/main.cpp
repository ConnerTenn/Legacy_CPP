

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>
#include <stdio.h>
#include <d3dcompiler.h>
#include <fstream>
using namespace DirectX;

int ScreenWidth, ScreenHeight;

LPCWSTR m_applicationName;
HINSTANCE m_hinstance;
HWND m_hwnd;

bool m_keys[256];

const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

bool m_vsync_enabled;
int m_videoCardMemory;
char m_videoCardDescription[128];
IDXGISwapChain* m_swapChain;
ID3D11Device* m_device;
ID3D11DeviceContext* m_deviceContext;
ID3D11RenderTargetView* m_renderTargetView;
ID3D11Texture2D* m_depthStencilBuffer;
ID3D11DepthStencilState* m_depthStencilState;
ID3D11DepthStencilView* m_depthStencilView;
ID3D11RasterizerState* m_rasterState;
XMMATRIX m_projectionMatrix;
XMMATRIX m_worldMatrix;
XMMATRIX m_orthoMatrix;

float m_positionX, m_positionY, m_positionZ;
float m_rotationX, m_rotationY, m_rotationZ;
XMMATRIX m_viewMatrix;

struct VertexType
{
	XMFLOAT3 position;
	XMFLOAT2 texture;
};

ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
int m_vertexCount, m_indexCount;

struct TargaHeader
{
	unsigned char data1[12];
	unsigned short width;
	unsigned short height;
	unsigned char bpp;
	unsigned char data2;
};

unsigned char* m_targaData;
ID3D11Texture2D* m_texture;
ID3D11ShaderResourceView* m_textureView;

struct MatrixBufferType
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
};

ID3D11VertexShader* m_vertexShader;
ID3D11PixelShader* m_pixelShader;
ID3D11InputLayout* m_layout;
ID3D11Buffer* m_matrixBuffer;
ID3D11SamplerState* m_sampleState;


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		switch (umessage)
		{
			// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			//m_Input->KeyDown((unsigned int)wparam);
			m_keys[(unsigned int)wparam] = true;
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			//m_Input->KeyUp((unsigned int)wparam);
			m_keys[(unsigned int)wparam] = false;
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umessage, wparam, lparam);
		}
		}
	}
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	{/*Initilize Window*/}
	{
		WNDCLASSEX wc;
		DEVMODE dmScreenSettings;
		int posX, posY;

		// Get the instance of this application.
		m_hinstance = GetModuleHandle(NULL);

		// Give the application a name.
		m_applicationName = L"DirectX Example";

		// Setup the windows class with default settings.
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_hinstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = m_applicationName;
		wc.cbSize = sizeof(WNDCLASSEX);

		// Register the window class.
		RegisterClassEx(&wc);
		
		// If windowed then set it to 800x600 resolution.
		ScreenWidth = 800;
		ScreenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - ScreenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - ScreenHeight) / 2;

		// Create the window with the screen settings and get the handle to it.
		//m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		//	WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		//	posX, posY, ScreenWidth, ScreenHeight, NULL, NULL, m_hinstance, NULL);
		m_hwnd = CreateWindow(
			m_applicationName,											// window class name
			m_applicationName,											// window caption
			wc.style,														// window style
			CW_USEDEFAULT,												// initial x position
			CW_USEDEFAULT,												// initial y position
			ScreenWidth,													// initial x size
			ScreenHeight,												// initial y size
			NULL,														// parent window handle
			NULL,														// window menu handle
			m_hinstance,													// program instance handle
			NULL);														// creation parameters


		// Bring the window up on the screen and set it as main focus.
		ShowWindow(m_hwnd, SW_SHOW);
		SetForegroundWindow(m_hwnd);
		SetFocus(m_hwnd);

		// Hide the mouse cursor.
		ShowCursor(false);
	}

	{/*Initialize Key Input*/}
	{
		for (int i = 0; i<256; i++)
		{
			m_keys[i] = false;
		}
	}

	{/*Initialize Graphics*/}
	{
		{/*Initialize Direct X*/}
		{
			m_swapChain = 0;
			m_device = 0;
			m_deviceContext = 0;
			m_renderTargetView = 0;
			m_depthStencilBuffer = 0;
			m_depthStencilState = 0;
			m_depthStencilView = 0;
			m_rasterState = 0;

			IDXGIFactory* factory;
			IDXGIAdapter* adapter;
			IDXGIOutput* adapterOutput;
			unsigned int numModes, i, numerator, denominator;
			unsigned long long stringLength;
			DXGI_MODE_DESC* displayModeList;
			DXGI_ADAPTER_DESC adapterDesc;
			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			D3D_FEATURE_LEVEL featureLevel;
			ID3D11Texture2D* backBufferPtr;
			D3D11_TEXTURE2D_DESC depthBufferDesc;
			D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
			D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
			D3D11_RASTERIZER_DESC rasterDesc;
			D3D11_VIEWPORT viewport;
			float fieldOfView, screenAspect;

			m_vsync_enabled = VSYNC_ENABLED;

			CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
			factory->EnumAdapters(0, &adapter);
			adapter->EnumOutputs(0, &adapterOutput);
			adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
			displayModeList = new DXGI_MODE_DESC[numModes];
			adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);

			for (i = 0; i < numModes; i++)
			{
				if (displayModeList[i].Width == (unsigned int)ScreenWidth)
				{
					if (displayModeList[i].Height == (unsigned int)ScreenHeight)
					{
						numerator = displayModeList[i].RefreshRate.Numerator;
						denominator = displayModeList[i].RefreshRate.Denominator;
					}
				}
			}

			adapter->GetDesc(&adapterDesc);

			m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

			wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128);


			delete[] displayModeList; displayModeList = 0;

			adapterOutput->Release(); adapterOutput = 0;

			adapter->Release(); adapter = 0;

			factory->Release(); factory = 0;


			ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

			swapChainDesc.BufferCount = 1;

			swapChainDesc.BufferDesc.Width = ScreenWidth;
			swapChainDesc.BufferDesc.Height = ScreenHeight;

			swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

			if (m_vsync_enabled)
			{
				swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
				swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
			}
			else
			{
				swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
				swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
			}

			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

			swapChainDesc.OutputWindow = m_hwnd;

			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;

			swapChainDesc.Windowed = true;

			swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			swapChainDesc.Flags = 0;

			featureLevel = D3D_FEATURE_LEVEL_11_0;

			D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1,
				D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContext);

			m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);

			m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);

			backBufferPtr->Release();
			backBufferPtr = 0;

			ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

			depthBufferDesc.Width = ScreenWidth;
			depthBufferDesc.Height = ScreenHeight;
			depthBufferDesc.MipLevels = 1;
			depthBufferDesc.ArraySize = 1;
			depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthBufferDesc.SampleDesc.Count = 1;
			depthBufferDesc.SampleDesc.Quality = 0;
			depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthBufferDesc.CPUAccessFlags = 0;
			depthBufferDesc.MiscFlags = 0;

			m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);

			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

			depthStencilDesc.DepthEnable = true;
			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

			depthStencilDesc.StencilEnable = true;
			depthStencilDesc.StencilReadMask = 0xFF;
			depthStencilDesc.StencilWriteMask = 0xFF;

			depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);

			m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

			ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

			depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			depthStencilViewDesc.Texture2D.MipSlice = 0;

			m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);

			m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode = D3D11_CULL_BACK;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0.0f;
			rasterDesc.DepthClipEnable = true;
			rasterDesc.FillMode = D3D11_FILL_SOLID;
			rasterDesc.FrontCounterClockwise = false;
			rasterDesc.MultisampleEnable = false;
			rasterDesc.ScissorEnable = false;
			rasterDesc.SlopeScaledDepthBias = 0.0f;

			m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);

			m_deviceContext->RSSetState(m_rasterState);

			viewport.Width = (float)ScreenWidth;
			viewport.Height = (float)ScreenHeight;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			viewport.TopLeftX = 0.0f;
			viewport.TopLeftY = 0.0f;

			m_deviceContext->RSSetViewports(1, &viewport);

			fieldOfView = 3.141592654f / 4.0f;
			screenAspect = (float)ScreenWidth / (float)ScreenHeight;

			m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, SCREEN_NEAR, SCREEN_DEPTH);
			m_worldMatrix = XMMatrixIdentity();
			m_orthoMatrix = XMMatrixOrthographicLH((float)ScreenWidth, (float)ScreenHeight, SCREEN_NEAR, SCREEN_DEPTH);
		}

		{/*Initialize Camera*/}
		{
			m_positionX = 0.0f;
			m_positionY = 0.0f;
			m_positionZ = -0.5f;

			m_rotationX = 0.0f;
			m_rotationY = 0.0f;
			m_rotationZ = 0.0f;
		}

		{/*Initialize Model*/}
		{
			m_vertexBuffer = 0;
			m_indexBuffer = 0;


			{/*Initialize Buffers*/}
			{
				VertexType* vertices;
				unsigned long* indices;
				D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
				D3D11_SUBRESOURCE_DATA vertexData, indexData;


				m_vertexCount = 3;

				m_indexCount = 3;

				vertices = new VertexType[m_vertexCount];

				indices = new unsigned long[m_indexCount];

				vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
				vertices[0].texture = XMFLOAT2(0.0f, 1.0f);

				vertices[1].position = XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top middle.
				vertices[1].texture = XMFLOAT2(0.5f, 0.0f);

				vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
				vertices[2].texture = XMFLOAT2(1.0f, 1.0f);

				indices[0] = 0;  // Bottom left.
				indices[1] = 1;  // Top middle.
				indices[2] = 2;  // Bottom right.

				vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
				vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				vertexBufferDesc.CPUAccessFlags = 0;
				vertexBufferDesc.MiscFlags = 0;
				vertexBufferDesc.StructureByteStride = 0;

				vertexData.pSysMem = vertices;
				vertexData.SysMemPitch = 0;
				vertexData.SysMemSlicePitch = 0;

				m_device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

				indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
				indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				indexBufferDesc.CPUAccessFlags = 0;
				indexBufferDesc.MiscFlags = 0;
				indexBufferDesc.StructureByteStride = 0;

				indexData.pSysMem = indices;
				indexData.SysMemPitch = 0;
				indexData.SysMemSlicePitch = 0;

				m_device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);

				delete[] vertices;
				vertices = 0;

				delete[] indices;
				indices = 0;
			}

			{/*Initialize Texture*/}
			{
				int height, width;
				D3D11_TEXTURE2D_DESC textureDesc;
				HRESULT hResult;
				unsigned int rowPitch;
				D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

				{/*Load Targa*/}
				{
					int bpp, imageSize, index, i, j, k;
					FILE* filePtr;
					//unsigned int count;
					TargaHeader targaFileHeader;
					unsigned char* targaImage;

					fopen_s(&filePtr, "../BareBones/stone01.tga", "rb");

					fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);

					height = (int)targaFileHeader.height;
					width = (int)targaFileHeader.width;
					bpp = (int)targaFileHeader.bpp;

					imageSize = width * height * 4;

					targaImage = new unsigned char[imageSize];

					(unsigned int)fread(targaImage, 1, imageSize, filePtr);

					fclose(filePtr);

					m_targaData = new unsigned char[imageSize];

					index = 0;

					k = (width * height * 4) - (width * 4);

					for (j = 0; j<height; j++)
					{
						for (i = 0; i<width; i++)
						{
							m_targaData[index + 0] = targaImage[k + 2];  // Red.
							m_targaData[index + 1] = targaImage[k + 1];  // Green.
							m_targaData[index + 2] = targaImage[k + 0];  // Blue
							m_targaData[index + 3] = targaImage[k + 3];  // Alpha

							k += 4;
							index += 4;
						}

						k -= (width * 8);
					}

					delete[] targaImage;
					targaImage = 0;
				}

				textureDesc.Height = height;
				textureDesc.Width = width;
				textureDesc.MipLevels = 0;
				textureDesc.ArraySize = 1;
				textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				textureDesc.SampleDesc.Count = 1;
				textureDesc.SampleDesc.Quality = 0;
				textureDesc.Usage = D3D11_USAGE_DEFAULT;
				textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
				textureDesc.CPUAccessFlags = 0;
				textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

				hResult = m_device->CreateTexture2D(&textureDesc, NULL, &m_texture);

				rowPitch = (width * 4) * sizeof(unsigned char);

				m_deviceContext->UpdateSubresource(m_texture, 0, NULL, m_targaData, rowPitch, 0);

				srvDesc.Format = textureDesc.Format;
				srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				srvDesc.Texture2D.MostDetailedMip = 0;
				srvDesc.Texture2D.MipLevels = -1;

				m_device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureView);

				m_deviceContext->GenerateMips(m_textureView);

				delete[] m_targaData;
				m_targaData = 0;
			}
		}

		{/*Initialize Texture*/}
		{
			ID3D10Blob* errorMessage;
			ID3D10Blob* vertexShaderBuffer;
			ID3D10Blob* pixelShaderBuffer;
			D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
			unsigned int numElements;
			D3D11_BUFFER_DESC matrixBufferDesc;
			D3D11_SAMPLER_DESC samplerDesc;


			// Initialize the pointers this function will use to null.
			errorMessage = 0;
			vertexShaderBuffer = 0;
			pixelShaderBuffer = 0;

			// Compile the vertex shader code.
			D3DCompileFromFile(L"../DirectX Example/texture.vs", NULL, NULL, "TextureVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
				&vertexShaderBuffer, &errorMessage);

			D3DCompileFromFile(L"../DirectX Example/texture.ps", NULL, NULL, "TexturePixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
				&pixelShaderBuffer, &errorMessage);

			m_device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
			
			m_device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
			
			polygonLayout[0].SemanticName = "POSITION";
			polygonLayout[0].SemanticIndex = 0;
			polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			polygonLayout[0].InputSlot = 0;
			polygonLayout[0].AlignedByteOffset = 0;
			polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[0].InstanceDataStepRate = 0;

			polygonLayout[1].SemanticName = "TEXCOORD";
			polygonLayout[1].SemanticIndex = 0;
			polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
			polygonLayout[1].InputSlot = 0;
			polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[1].InstanceDataStepRate = 0;

			numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

			m_device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
				vertexShaderBuffer->GetBufferSize(), &m_layout);

			vertexShaderBuffer->Release();
			vertexShaderBuffer = 0;

			pixelShaderBuffer->Release();
			pixelShaderBuffer = 0;

			matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
			matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			matrixBufferDesc.MiscFlags = 0;
			matrixBufferDesc.StructureByteStride = 0;

			m_device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);

			samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 1;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			samplerDesc.BorderColor[0] = 0;
			samplerDesc.BorderColor[1] = 0;
			samplerDesc.BorderColor[2] = 0;
			samplerDesc.BorderColor[3] = 0;
			samplerDesc.MinLOD = 0;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

			m_device->CreateSamplerState(&samplerDesc, &m_sampleState);
		}
	}

	{/*Run*/}
	{
		MSG msg;
		bool done, result;


		// Initialize the message structure.
		ZeroMemory(&msg, sizeof(MSG));

		// Loop until there is a quit message from the window or the user.
		done = false;
		while (!done)
		{
			// Handle the windows messages.
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			// If windows signals to end the application then exit out.
			if (msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				// Otherwise do the frame processing.
				result = Frame();
				if (!result)
				{
					done = true;
				}
			}

		}
	}

	{/*Shutdown*/}
	{

	}
}