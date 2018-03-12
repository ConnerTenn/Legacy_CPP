
// include the basic windows header files and the Direct3D header files
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
//#include <d3dx11.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>
#include <stdio.h>
#include <d3dcompiler.h>
#include <fstream>
#include <thread>

using namespace DirectX;

// define the screen resolution
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define PI 3.14159265358979323
#define TAU (2 * PI)

bool Run = true;

// global declarations
IDXGISwapChain *SwapChain;             // the pointer to the swap chain interface
ID3D11Device *Device;                     // the pointer to our Direct3D device interface
ID3D11DeviceContext *DeviceContext;           // the pointer to our Direct3D device context
ID3D11RenderTargetView *RenderTarget;    // the pointer to our back buffer
ID3D11InputLayout *InputLayout;            // the pointer to the input layout
ID3D11VertexShader *VertexShader;               // the pointer to the vertex shader
ID3D11PixelShader *PixelShader;                // the pointer to the pixel shader
ID3D11Buffer *VertexBuffer;                // the pointer to the vertex buffer
ID3D11Buffer *IndexBuffer;                // the pointer to the index buffer
ID3D11Buffer *MatrixBuffer;
ID3D11Buffer *ShaderValues;
ID3D11Texture2D *DepthStencilBuffer;
//ID3D11DepthStencilState *DepthStencilState;
ID3D11DepthStencilView *DepthStencilView;
//ID3D11RasterizerState *RasterState;

XMMATRIX WorldMatrix;
XMMATRIX ViewMatrix;
XMMATRIX ProjectionMatrix;

									   // a struct to define a single vertex
struct COLOR { float Color[4]; COLOR(float r, float g, float b, float a) { Color[0] = r; Color[1] = g; Color[2] = b; Color[3] = a; } };
//struct VERTEX { FLOAT X, Y, Z; COLOR Color; };
struct Vertex
{
	XMFLOAT3 Position;
	XMFLOAT4 Color;
};

struct MatrixBufferType
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
};

struct ShaderValuesType
{
	XMFLOAT4 Value;
};



// function prototypes
void InitD3D(HWND hWnd);	// sets up and initializes Direct3D
void RenderFrame();			// renders a single frame
void RenderFrame2();			// renders a single frame
void CleanD3D();			// closes Direct3D and releases memory
void InitGraphics();	// creates the shape to render
void InitPipeline();	// loads and prepares the shaders

							// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);






// this function loads and prepares the shaders
void InitPipeline()
{
	// load and compile the two shaders
	ID3DBlob *vertexShader, *pixelShader;
	ID3DBlob *errorMessage;
	D3DCompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_5_0", 0, 0, &vertexShader, &errorMessage);
	D3DCompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_5_0", 0, 0, &pixelShader, &errorMessage);
	if (errorMessage)
	{
		char* compileErrors; unsigned long long bufferSize;	std::ofstream fout;
		compileErrors = (char*)(errorMessage->GetBufferPointer()); bufferSize = errorMessage->GetBufferSize();
		fout.open("shader-error.txt"); for (int i = 0; i<bufferSize; i++) { fout << compileErrors[i]; }	fout.close();
		errorMessage->Release();
	}

	// encapsulate both shaders into shader objects
	Device->CreateVertexShader(vertexShader->GetBufferPointer(), vertexShader->GetBufferSize(), NULL, &VertexShader);
	Device->CreatePixelShader(pixelShader->GetBufferPointer(), pixelShader->GetBufferSize(), NULL, &PixelShader);

	// set the shader objects
	DeviceContext->VSSetShader(VertexShader, 0, 0);
	DeviceContext->PSSetShader(PixelShader, 0, 0);

	// create the input layout object
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	Device->CreateInputLayout(inputElementDesc, 2, vertexShader->GetBufferPointer(), vertexShader->GetBufferSize(), &InputLayout);
	DeviceContext->IASetInputLayout(InputLayout);

	vertexShader->Release();
	pixelShader->Release();
}

// this is the function that creates the shape to render
void InitGraphics()
{
	{/*Vertex Buffer*/}
	{
		D3D11_SUBRESOURCE_DATA vertexData;

		// create a triangle using the Vertex struct
		Vertex vertices[6] =
		{
			{ { 0.0f, 0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ { 0.45f, -0.5, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			{ { -0.45f, -0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },

			{ { 0.0f, 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ { 0.45f, -0.5, 0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			{ { -0.45f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
		};


		// create the vertex buffer
		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;                // write access access by CPU and GPU
		vertexBufferDesc.ByteWidth = sizeof(Vertex) * 6;             // size is the VERTEX struct * 3
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
																	 //vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

																	 // Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		Device->CreateBuffer(&vertexBufferDesc, &vertexData, &VertexBuffer);       // create the buffer
	}

	{/*Index Buffer*/}
	{
		D3D11_SUBRESOURCE_DATA indexData;
		unsigned long indices[12] =
		{
			0, 1, 2,
			0, 2, 1,

			3, 4, 5,
			3, 5, 4
		};

		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
		// Set up the description of the static index buffer.
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned long) * 12;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		// Give the subresource structure a pointer to the index data.
		indexData.pSysMem = indices;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		// Create the index buffer.
		Device->CreateBuffer(&indexBufferDesc, &indexData, &IndexBuffer);
	}
}

// this function initializes and prepares Direct3D for use
void InitD3D(HWND hWnd)
{
	{/*Swap Chain*/}
	{
		// create a struct to hold information about the swap chain
		DXGI_SWAP_CHAIN_DESC swapChainDesc;

		// clear out the struct for use
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		// fill the swap chain description struct
		swapChainDesc.BufferCount = 1;                                   // one back buffer
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // use 32-bit color
		swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;                   // set the back buffer width
		swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;                 // set the back buffer height
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // how swap chain is to be used
		swapChainDesc.OutputWindow = hWnd;                               // the window to be used
		swapChainDesc.SampleDesc.Count = 1;                              // how many multisamples
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Windowed = TRUE;                                   // windowed/full-screen mode
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // allow full-screen switching

		// create a device, device context and swap chain using the information in the swapChainDesc struct
		D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			NULL,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&SwapChain,
			&Device,
			NULL,
			&DeviceContext);
	}

	{/*Back Buffer*/}
	{
		// get the address of the back buffer
		ID3D11Texture2D *pBackBuffer;
		SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		// use the back buffer address to create the render target
		Device->CreateRenderTargetView(pBackBuffer, NULL, &RenderTarget);
		pBackBuffer->Release();

		// set the render target as the back buffer
		DeviceContext->OMSetRenderTargets(1, &RenderTarget, NULL);
	}

	{/*Depth Buffer*/} 
	{
		D3D11_TEXTURE2D_DESC depthBufferDesc;
		// Initialize the description of the depth buffer.
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

		// Set up the description of the depth buffer.
		depthBufferDesc.Width = SCREEN_WIDTH;
		depthBufferDesc.Height = SCREEN_HEIGHT;
		depthBufferDesc.MipLevels = 1;
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthBufferDesc.CPUAccessFlags = 0;
		depthBufferDesc.MiscFlags = 0;

		// Create the texture for the depth buffer using the filled out description.
		Device->CreateTexture2D(&depthBufferDesc, NULL, &DepthStencilBuffer);

		/*
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		// Initialize the description of the stencil state.
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

		// Set up the description of the stencil state.
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

		depthStencilDesc.StencilEnable = true;
		depthStencilDesc.StencilReadMask = 0xFF;
		depthStencilDesc.StencilWriteMask = 0xFF;

		// Stencil operations if pixel is front-facing.
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// Stencil operations if pixel is back-facing.
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// Create the depth stencil state.
		Device->CreateDepthStencilState(&depthStencilDesc, &DepthStencilState);

		// Set the depth stencil state.
		DeviceContext->OMSetDepthStencilState(DepthStencilState, 1);
		*/

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		// Initialize the depth stencil view.
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

		// Set up the depth stencil view description.
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		// Create the depth stencil view.
		Device->CreateDepthStencilView(DepthStencilBuffer, &depthStencilViewDesc, &DepthStencilView);

		// Bind the render target view and depth stencil buffer to the output render pipeline.
		DeviceContext->OMSetRenderTargets(1, &RenderTarget, DepthStencilView);
	}

	{/*Raster State*/}
	/*
	{
		D3D11_RASTERIZER_DESC rasterDesc;
		// Setup the raster description which will determine how and what polygons will be drawn.
		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable =  true;
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		// Create the rasterizer state from the description we just filled out.
		Device->CreateRasterizerState(&rasterDesc, &RasterState);

		// Now set the rasterizer state.
		DeviceContext->RSSetState(RasterState);
	}
	*/

	{/*viewport*/}
	{
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.Width = SCREEN_WIDTH;
		viewport.Height = SCREEN_HEIGHT;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		DeviceContext->RSSetViewports(1, &viewport);
	}

	{/*Matrices*/}
	{
		float FieldOfView = (float)TAU / 8.0f;
		float ScreenAspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

		// Create the projection matrix for 3D rendering.
		ProjectionMatrix = XMMatrixPerspectiveFovLH(FieldOfView, ScreenAspect, 0.001f, 1000.0f);
		//ProjectionMatrix = XMMatrixOrthographicLH(2.0f, 2.0f, 0.001f, 1000.0f);
		// Initialize the world matrix to the identity matrix.
		WorldMatrix = XMMatrixIdentity();


		D3D11_BUFFER_DESC matrixBufferDesc;
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;

		Device->CreateBuffer(&matrixBufferDesc, NULL, &MatrixBuffer);
	}

	{/*Shader Values*/}
	{
		D3D11_BUFFER_DESC shaderValuesDesc;
		shaderValuesDesc.Usage = D3D11_USAGE_DYNAMIC;
		shaderValuesDesc.ByteWidth = sizeof(ShaderValuesType);
		shaderValuesDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		shaderValuesDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		shaderValuesDesc.MiscFlags = 0;
		shaderValuesDesc.StructureByteStride = 0;

		Device->CreateBuffer(&shaderValuesDesc, NULL, &ShaderValues);
	}

	InitPipeline();
	InitGraphics();
}


// this is the function used to render a single frame
void RenderFrame()
{
	{/*Matrices*/}
	{
		static float Val = 0; Val += 0.001f; if (Val > 1.0) { Val = fmodf(Val, 1.0); }
		float PositionX = 2.0f * sin(Val * (float)TAU);
		float PositionY = 0.0f;
		float PositionZ = 2.0f * -cos(Val * (float)TAU);

		float RotationX = 0.0f;
		float RotationY = -Val;
		float RotationZ = 0.0f;

		XMFLOAT3 up, position, lookAt;
		XMVECTOR upVector, positionVector, lookAtVector;
		float yaw, pitch, roll;
		XMMATRIX rotationMatrix;

		// Setup the vector that points upwards.
		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;
		upVector = XMLoadFloat3(&up);

		// Setup the position of the camera in the world.
		position.x = PositionX;	position.y = PositionY;	position.z = PositionZ;
		//position.x = 0; position.y = 0; position.z = -1;
		positionVector = XMLoadFloat3(&position);

		// Setup where the camera is looking by default.
		lookAt.x = 0.0f; lookAt.y = 0.0f; lookAt.z = 1.0f;
		lookAtVector = XMLoadFloat3(&lookAt);

		// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
		pitch = RotationX * (float)TAU;
		yaw = RotationY * (float)TAU;
		roll = RotationZ * (float)TAU;

		// Create the rotation matrix from the yaw, pitch, and roll values.
		rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

		// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
		lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
		upVector = XMVector3TransformCoord(upVector, rotationMatrix);

		// Translate the rotated camera position to the location of the viewer.
		lookAtVector = XMVectorAdd(positionVector, lookAtVector);

		// Finally create the view matrix from the three updated vectors.
		ViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
		//ViewMatrix = XMMatrixTranslation(-PositionX, -PositionY, -PositionZ) * XMMatrixRotationRollPitchYaw(-pitch, -yaw, -roll) * XMMatrixLookAtLH(positionVector, lookAtVector, upVector);




		XMMATRIX worldMatrix = WorldMatrix, viewMatrix = ViewMatrix, projectionMatrix = ProjectionMatrix;
		worldMatrix = XMMatrixTranspose(worldMatrix);
		viewMatrix = XMMatrixTranspose(viewMatrix);
		projectionMatrix = XMMatrixTranspose(projectionMatrix);

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		MatrixBufferType* dataPtr;
		DeviceContext->Map(MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		// Get a pointer to the data in the constant buffer.
		dataPtr = (MatrixBufferType*)mappedResource.pData;
		// Copy the matrices into the constant buffer.
		dataPtr->world = worldMatrix;
		dataPtr->view = viewMatrix;
		dataPtr->projection = projectionMatrix;
		// Unlock the constant buffer.
		DeviceContext->Unmap(MatrixBuffer, 0);
		//MatrixBuffer->SetPrivateData(0, sizeof(MatrixBufferType), (void *)dataPtr);

		DeviceContext->VSSetConstantBuffers(0, 1, &MatrixBuffer);
	}

	{/*Shader Values*/}
	{
		static float value = 0; value = fmodf(value + 0.007f, 1.0f);

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ShaderValuesType* dataPtr;
		DeviceContext->Map(ShaderValues, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		// Get a pointer to the data in the constant buffer.
		dataPtr = (ShaderValuesType*)mappedResource.pData;
		// Copy the matrices into the constant buffer.
		dataPtr->Value = { value * (float)TAU, value * (float)TAU, value * (float)TAU, value * (float)TAU };
		// Unlock the constant buffer.
		DeviceContext->Unmap(ShaderValues, 0);
		//MatrixBuffer->SetPrivateData(0, sizeof(MatrixBufferType), (void *)dataPtr);

		DeviceContext->VSSetConstantBuffers(1, 1, &ShaderValues);
	}


	// clear the back buffer to a deep blue
	DeviceContext->ClearRenderTargetView(RenderTarget, COLOR(0.0f, 0.2f, 0.4f, 1.0f).Color);
	
	// Clear the depth buffer.
	DeviceContext->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// select which vertex buffer to display
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	DeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// select which primtive type we are using
	DeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	// draw the vertex buffer to the back buffer
	//DeviceContext->Draw(3, 0);
	DeviceContext->DrawIndexed(12, 0, 0);


	RenderFrame2();

	// switch the back buffer and the front buffer
	SwapChain->Present(1, 0);
	//SwapChain->Present(0, 0);
}

void RenderFrame2()
{
	{/*Matrices*/}
	{
		static float Val = 0.25; Val += 0.001f; if (Val > 1.0) { Val = fmodf(Val, 1.0); }
		float PositionX = 2.0f * sin(Val * (float)TAU);
		float PositionY = 0.0f;
		float PositionZ = 2.0f * -cos(Val * (float)TAU);

		float RotationX = 0.0f;
		float RotationY = -Val;
		float RotationZ = 0.0f;

		XMFLOAT3 up, position, lookAt;
		XMVECTOR upVector, positionVector, lookAtVector;
		float yaw, pitch, roll;
		XMMATRIX rotationMatrix;

		// Setup the vector that points upwards.
		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;
		upVector = XMLoadFloat3(&up);

		// Setup the position of the camera in the world.
		position.x = PositionX;	position.y = PositionY;	position.z = PositionZ;
		//position.x = 0; position.y = 0; position.z = -1;
		positionVector = XMLoadFloat3(&position);

		// Setup where the camera is looking by default.
		lookAt.x = 0.0f; lookAt.y = 0.0f; lookAt.z = 1.0f;
		lookAtVector = XMLoadFloat3(&lookAt);

		// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
		pitch = RotationX * (float)TAU;
		yaw = RotationY * (float)TAU;
		roll = RotationZ * (float)TAU;

		// Create the rotation matrix from the yaw, pitch, and roll values.
		rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

		// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
		lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
		upVector = XMVector3TransformCoord(upVector, rotationMatrix);

		// Translate the rotated camera position to the location of the viewer.
		lookAtVector = XMVectorAdd(positionVector, lookAtVector);

		// Finally create the view matrix from the three updated vectors.
		ViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
		//ViewMatrix = XMMatrixTranslation(-PositionX, -PositionY, -PositionZ) * XMMatrixRotationRollPitchYaw(-pitch, -yaw, -roll) * XMMatrixLookAtLH(positionVector, lookAtVector, upVector);




		XMMATRIX worldMatrix = WorldMatrix, viewMatrix = ViewMatrix, projectionMatrix = ProjectionMatrix;
		worldMatrix = XMMatrixTranspose(worldMatrix);
		viewMatrix = XMMatrixTranspose(viewMatrix);
		projectionMatrix = XMMatrixTranspose(projectionMatrix);

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		MatrixBufferType* dataPtr;
		DeviceContext->Map(MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		// Get a pointer to the data in the constant buffer.
		dataPtr = (MatrixBufferType*)mappedResource.pData;
		// Copy the matrices into the constant buffer.
		dataPtr->world = worldMatrix;
		dataPtr->view = viewMatrix;
		dataPtr->projection = projectionMatrix;
		// Unlock the constant buffer.
		DeviceContext->Unmap(MatrixBuffer, 0);
		//MatrixBuffer->SetPrivateData(0, sizeof(MatrixBufferType), (void *)dataPtr);

		DeviceContext->VSSetConstantBuffers(0, 1, &MatrixBuffer);
	}

	{/*Shader Values*/}
	{
		static float value = 0; value = fmodf(value + 0.01f, 1.0f);

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ShaderValuesType* dataPtr;
		DeviceContext->Map(ShaderValues, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		// Get a pointer to the data in the constant buffer.
		dataPtr = (ShaderValuesType*)mappedResource.pData;
		// Copy the matrices into the constant buffer.
		dataPtr->Value = { value * (float)TAU, value * (float)TAU, value * (float)TAU, value * (float)TAU };
		// Unlock the constant buffer.
		DeviceContext->Unmap(ShaderValues, 0);
		//MatrixBuffer->SetPrivateData(0, sizeof(MatrixBufferType), (void *)dataPtr);

		DeviceContext->VSSetConstantBuffers(1, 1, &ShaderValues);
	}

	// select which vertex buffer to display
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	DeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// select which primtive type we are using
	DeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	// draw the vertex buffer to the back buffer
	//DeviceContext->Draw(3, 0);
	DeviceContext->DrawIndexed(12, 0, 0);
}


// this is the function that cleans up Direct3D and COM
void CleanD3D(void)
{
	SwapChain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

												   // close and release all existing COM objects
	InputLayout->Release();
	VertexShader->Release();
	PixelShader->Release();

	VertexBuffer->Release();
	IndexBuffer->Release();
	SwapChain->Release();
	RenderTarget->Release();
	MatrixBuffer->Release();
	ShaderValues->Release();

	DepthStencilBuffer->Release();
	//DepthStencilState->Release();
	DepthStencilView->Release();
	//RasterState->Release();

	Device->Release();
	DeviceContext->Release();
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	{/*Initialize Window*/}
	{
		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = L"WindowClass";

		RegisterClassEx(&wc);

		RECT windowRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
		
		hWnd = CreateWindowEx(NULL,
			L"WindowClass",
			L"Our First Direct3D Program",
			WS_OVERLAPPEDWINDOW,
			GetSystemMetrics(SM_CXSCREEN) / 2 - SCREEN_WIDTH / 2 - 10,
			GetSystemMetrics(SM_CYSCREEN) / 2 - SCREEN_HEIGHT / 2 - 40,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			NULL,
			NULL,
			hInstance,
			NULL);

		ShowWindow(hWnd, nCmdShow);
	}

	// set up and initialize Direct3D
	InitD3D(hWnd);

	// enter the main loop:

	MSG msg;

	while (Run)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				Run = false;
			}
		}

		RenderFrame();
	}

	// clean up DirectX and COM
	CleanD3D();

	return 0;// (int)msg.wParam;
}


