/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

Levels - levelsnstrates rendering a 3D object (cube).
*/

#include"Levels.h"

Levels::Levels() : solidColorVS_(0), solidColorPS_(0),
inputLayout_(0), colorMapSampler_(0), mvpCB_(0), alphaBlendState_(0)
{

}

void Levels::Level1Loop(MSG msg, double Delta, clock_t t1)
{
	while (msg.message != WM_QUIT)
	{
		t1 = clock();
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//Old = Delta;
		//Delta = clock() - Old;

		// Update and Draw
		UpdateLevel1(Delta);
		RenderLevel1();
		double Delay = 0.0;
		double ObjectiveTime = 0.02;
		if (Delta <= ObjectiveTime)
		{
			Delay = (ObjectiveTime - Delta);
		}
		//DBOUT("Delay:" << Delay << " Delta Time:" << Delta << "\n");
		//Old = Elapsed;

		//t2 = clock();
		//((float)t) / CLOCKS_PER_SEC)
		Delta = static_cast<double>(clock() - t1) / CLOCKS_PER_SEC;
		Sleep(static_cast<DWORD>(Delay));

		if (GetAsyncKeyState(0xDD) < 0)
		{
			UnloadLevel1Content();
			LoadLevel2Content(msg, Delta, t1);
		}
	}

	UnloadLevelsContent();
	Shutdown();
	exit(0);
}

void Levels::Level2Loop(MSG msg, double Delta, clock_t t1)
{
	while (msg.message != WM_QUIT)
	{
		t1 = clock();
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//Old = Delta;
		//Delta = clock() - Old;

		// Update and Draw
		UpdateLevel2(Delta);
		RenderLevel2();
		double Delay = 0.0;
		double ObjectiveTime = 0.02;
		if (Delta <= ObjectiveTime)
		{
			Delay = (ObjectiveTime - Delta);
		}
		//DBOUT("Delay:" << Delay << " Delta Time:" << Delta << "\n");
		//Old = Elapsed;

		//t2 = clock();
		//((float)t) / CLOCKS_PER_SEC)
		Delta = static_cast<double>(clock() - t1) / CLOCKS_PER_SEC;
		Sleep(static_cast<DWORD>(Delay));

		if (GetAsyncKeyState(0xDB) < 0)
		{
			UnloadLevel2Content();
			LoadLevel1Content(msg, Delta, t1);
		}
	}

	UnloadLevelsContent();
	Shutdown();
	exit(0);
}


void Levels::LoadLevelsContent()
{
	ID3DBlob* vsBuffer = 0;

	bool compileResult = CompileD3DShader("TextureMap.fx", "VS_Main", "vs_4_0", &vsBuffer);
	{
		if (compileResult == false)
		{
			DXTRACE_MSG("Error compiling the vertex shader!");
		}
	}

	{/*Set d3dResult*/}
	{
		d3dResult = d3dDevice_->CreateVertexShader(vsBuffer->GetBufferPointer(),
			vsBuffer->GetBufferSize(), 0, &solidColorVS_);

		if (FAILED(d3dResult))
		{
			DXTRACE_MSG("Error creating the vertex shader!");

			if (vsBuffer)
				vsBuffer->Release();
		}
	}

	D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }//,
		//{ "ALPHA", 0, DXGI_FORMAT_R32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	{

		unsigned int totalLayoutElements = ARRAYSIZE(solidColorLayout);

		d3dResult = d3dDevice_->CreateInputLayout(solidColorLayout, totalLayoutElements,
			vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), &inputLayout_);

		vsBuffer->Release();

		if (FAILED(d3dResult))
		{
			DXTRACE_MSG("Error creating the input layout!");
		}

		ID3DBlob* psBuffer = 0;


		compileResult = CompileD3DShader("TextureMap.fx", "PS_Main", "ps_4_0", &psBuffer);
		if (compileResult == false)
		{
			DXTRACE_MSG("Error compiling pixel shader!");
		}

		d3dResult = d3dDevice_->CreatePixelShader(psBuffer->GetBufferPointer(),
			psBuffer->GetBufferSize(), 0, &solidColorPS_);

		psBuffer->Release();

		if (FAILED(d3dResult))
		{
			DXTRACE_MSG("Error creating pixel shader!");
		}
	}

	D3D11_SAMPLER_DESC colorMapDesc;
	{
		ZeroMemory(&colorMapDesc, sizeof(colorMapDesc));
		colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		//colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;//          ------------------------------
		colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

		d3dResult = d3dDevice_->CreateSamplerState(&colorMapDesc, &colorMapSampler_);

		if (FAILED(d3dResult))
		{
			DXTRACE_MSG("Failed to create color map sampler state!");
		}
	}

	D3D11_BUFFER_DESC constDesc;
	{
		ZeroMemory(&constDesc, sizeof(constDesc));
		constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constDesc.ByteWidth = sizeof(XMMATRIX);
		constDesc.Usage = D3D11_USAGE_DEFAULT;

		d3dResult = d3dDevice_->CreateBuffer(&constDesc, 0, &viewCB_);

		if (FAILED(d3dResult))
		{
		}

		d3dResult = d3dDevice_->CreateBuffer(&constDesc, 0, &projCB_);

		if (FAILED(d3dResult))
		{
		}

		d3dResult = d3dDevice_->CreateBuffer(&constDesc, 0, &worldCB_);

		if (FAILED(d3dResult))
		{
		}
	}

	{/*Define IndexBuffer*/}
	{
		WORD indices[] =
		{
			//Front
			3, 1, 0,
			2, 1, 3,
			//Back
			2, 0, 1,
			3, 0, 2,
		};
		D3D11_BUFFER_DESC indexDesc;
		ZeroMemory(&indexDesc, sizeof(indexDesc));
		indexDesc.Usage = D3D11_USAGE_DEFAULT;
		indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexDesc.ByteWidth = sizeof(WORD)* 36;
		indexDesc.CPUAccessFlags = 0;
		resourceData.pSysMem = indices;

		d3dResult = d3dDevice_->CreateBuffer(&indexDesc, &resourceData, &indexBuffer_);

		if (FAILED(d3dResult))
		{
			DXTRACE_MSG("Failed to create index buffer!");
		}
	}

	{/*Define IndexBufferText*/}
	{
		WORD indicesText[6 * MaxCharacters];

		for (int i = 0; i < MaxCharacters; i++)
		{
			indicesText[i * 6 + 0] = i * 4 + 3;
			indicesText[i * 6 + 1] = i * 4 + 1;
			indicesText[i * 6 + 2] = i * 4 + 0;

			indicesText[i * 6 + 3] = i * 4 + 2;
			indicesText[i * 6 + 4] = i * 4 + 1;
			indicesText[i * 6 + 5] = i * 4 + 3;
		}
		D3D11_BUFFER_DESC indexDesc;
		ZeroMemory(&indexDesc, sizeof(indexDesc));
		indexDesc.Usage = D3D11_USAGE_DEFAULT;
		indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexDesc.ByteWidth = sizeof(WORD)* 20 * MaxCharacters;
		indexDesc.CPUAccessFlags = 0;
		resourceData.pSysMem = indicesText;

		d3dResult = d3dDevice_->CreateBuffer(&indexDesc, &resourceData, &indexBufferText_);

		if (FAILED(d3dResult))
		{
			DXTRACE_MSG("Failed to create index buffer!");
		}
	}

	//viewMatrix_ = XMMatrixIdentity();
	//projMatrix_ = XMMatrixOrthographicOffCenterLH(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	//projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.01f, 100.0f);
	projMatrix_ = XMMatrixOrthographicLH(Width, Height, 0.1f, 2000.0f);

	//viewMatrix_ = XMMatrixTranspose(viewMatrix_);
	projMatrix_ = XMMatrixTranspose(projMatrix_);

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.RenderTarget[0].BlendEnable = TRUE;

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	//blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_BLEND_FACTOR;

	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	d3dDevice_->CreateBlendState(&blendDesc, &alphaBlendState_);
	d3dContext_->OMSetBlendState(alphaBlendState_, blendFactor, 0xFFFFFFFF);
}

void Levels::UnloadLevelsContent()
{
	if (colorMapSampler_) colorMapSampler_->Release();
	if (solidColorVS_) solidColorVS_->Release();
	if (solidColorPS_) solidColorPS_->Release();
	if (inputLayout_) inputLayout_->Release();
	if (indexBuffer_) indexBuffer_->Release();
	if (indexBufferText_) indexBufferText_->Release();
	if (viewCB_) viewCB_->Release();
	if (projCB_) projCB_->Release();
	if (worldCB_) worldCB_->Release();

	colorMapSampler_ = 0;
	solidColorVS_ = 0;
	solidColorPS_ = 0;
	inputLayout_ = 0;
	indexBuffer_ = 0;
	indexBufferText_ = 0;
	viewCB_ = 0;
	projCB_ = 0;
	worldCB_ = 0;
}

