#pragma once

#include "Complex.h"
#include <msclr\marshal_cppstd.h>
#include <Windows.h>

//std::vector<std::vector<int>> DrawArray;
int DrawArray[800][450];
int DrawArrayC[800][450][3];

long double Pwidth = 800, Pheight = 450;
const int NumThreads = 4;

long double Zoom = 1;
long double Position[2] = { -0.5, 0 };

long double ViewX[2] = { -2, 1 };
long double ViewY[2] = { 1, -1 };
long double StepSize[2] = { ((ViewX[1] - ViewX[0]) / Pwidth), ((ViewY[0] - ViewY[1]) / Pheight) };

//bool Thread1LineComplete = false, Thread2LineComplete = false, Thread3LineComplete = false, Thread4LineComplete = false;
//bool Thread1Complete = false, Thread2Complete = false, Thread3Complete = false, Thread4Complete = false;
//bool Complete = false;
int CompleteCount = 0;
long double NextY = ViewY[0];
//#pragma managed

//void(*RefreshFunc)();

/*class ThreadClass
{
public:
	/*static void Thread()
	{
	int X, Y, Colour = 240;
	for (double y = ViewY[0] - StepSize[1] * 0; y >= ViewY[1]; y -= StepSize[1] * 4)
	{
	//for (float x = ViewX[0]; x <= ViewX[1]; x += (2) / Pwidth)
	for (double x = ViewX[0]; x <= ViewX[1]; x += StepSize[0])
	{
	System::Console::WriteLine("X:{0}  Y:{1}", x, y);
	//X = (x * Pwidth)/2.0 + Pwidth / 2.0;
	X = Map({ ViewX[0],ViewX[1] }, { 0, Pwidth }, x);
	//Y = Pheight - (y * Pheight)/2.0 + Pheight / 2.0;
	Y = Map({ ViewY[0],ViewY[1] }, { 0, Pheight }, y);
	if (TendsToInfinity(Complex(x, y)))
	{
	Colour = 0;
	}
	else
	{
	Colour = 255;
	}
	DrawArray[X][Y] = Colour;
	}
	Thread1LineComplete = true;
	}
	}/
	/static void Thread()
	{
	int X, Y, Colour = 240;
	std::vector<int> ColourC = { 240, 240, 240 };
	while (!Complete)
	{
	if (!(NextY >= ViewY[1])) { Complete = true; }
	else
	{
	double y = NextY;
	NextY -= StepSize[1];
	for (double x = ViewX[0]; x <= ViewX[1]; x += StepSize[0])
	{
	System::Console::WriteLine("X:{0}  Y:{1}", x, y);
	//X = (x * Pwidth)/2.0 + Pwidth / 2.0;
	X = Map({ ViewX[0],ViewX[1] }, { 0, Pwidth }, x);
	//Y = Pheight - (y * Pheight)/2.0 + Pheight / 2.0;
	Y = Map({ ViewY[0],ViewY[1] }, { 0, Pheight }, y);
	if (TendsToInfinity(Complex(x, y)))
	{
	Colour = 0;
	}
	else
	{
	Colour = 255;
	}
	ColourC = TendsToInfinityColour(Complex(x, y));
	//DrawArray[X][Y] = Colour;
	DrawArrayC[X][Y][0] = ColourC[0];
	DrawArrayC[X][Y][1] = ColourC[1];
	DrawArrayC[X][Y][2] = ColourC[2];
	}
	}
	}
	CompleteCount++;
	}/
	static void Thread()
	{
		int X, Y, Colour = 240;
		std::vector<int> ColourC = { 240, 240, 240 };
		while ((NextY >= ViewY[1]))
		{
			double y = NextY;
			NextY -= StepSize[1];
			for (double x = ViewX[0]; x <= ViewX[1]; x += StepSize[0])
			{
				//System::Console::WriteLine("X:{0}  Y:{1}", x, y);
				//X = (x * Pwidth)/2.0 + Pwidth / 2.0;
				X = Map({ ViewX[0],ViewX[1] }, { 0, Pwidth }, x);
				//Y = Pheight - (y * Pheight)/2.0 + Pheight / 2.0;
				Y = Map({ ViewY[0],ViewY[1] }, { 0, Pheight }, y);
				/*if (TendsToInfinity(Complex(x, y)))
				{
				Colour = 0;
				}
				else
				{
				Colour = 255;
				}/
				ColourC = TendsToInfinityColour(Complex(x, y));
				//DrawArray[X][Y] = Colour;
				DrawArrayC[X][Y][0] = ColourC[0];
				DrawArrayC[X][Y][1] = ColourC[1];
				DrawArrayC[X][Y][2] = ColourC[2];
			}
		}
		CompleteCount++;
	}
};*/

DWORD WINAPI CalculateThread(LPVOID lpParameter)
{
	int X, Y, Colour = 240;
	std::vector<int> ColourC = { 240, 240, 240 };
	while ((NextY >= ViewY[1]))
	{
		long double y = NextY;
		NextY -= StepSize[1];
		for (long double x = ViewX[0]; x <= ViewX[1]; x += StepSize[0])
		{
			//System::Console::WriteLine("StepSizeX:{0}\t\tStepSizeY:{1}", StepSize[0], StepSize[1]);
			//System::Console::WriteLine("x:{0}\t\ty:{1}", x, y);
			//X = (x * Pwidth)/2.0 + Pwidth / 2.0;
			X = Map({ ViewX[0],ViewX[1] }, { 0, Pwidth }, x);
			Y = Map({ ViewY[0],ViewY[1] }, { 0, Pheight }, y);

			ColourC = TendsToInfinityColourComplex(std::complex<double>(x, y));
			//DrawArray[X][Y] = Colour;
			DrawArrayC[X][Y][0] = ColourC[0];
			DrawArrayC[X][Y][1] = ColourC[1];
			DrawArrayC[X][Y][2] = ColourC[2];
		}
	}
	CompleteCount++;
	return 0;
}
///*
typedef void(*UnmanagedSummer)();

DWORD WINAPI UpdateThread(LPVOID lpParameter);/*
{
	void(*Func)(void);
	//Func = void(lpParameter)(void*);
	//Func = reinterpret_cast<(void*)>
	Func = (void(*)(void))lpParameter;
	do
	{
		//Refresh();
		Sleep(5000);
	}
	while (CompleteCount < NumThreads);
	return 0;
}
*/
#pragma managed(pop)
namespace Mandlebrot3
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  DrawButton;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBoxXPos;
	private: System::Windows::Forms::TextBox^  textBoxYPos;




	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxScale;





	private: System::Windows::Forms::Label^  label4;

	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->DrawButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxXPos = (gcnew System::Windows::Forms::TextBox());
			this->textBoxYPos = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBoxScale = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(800, 450);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			// 
			// DrawButton
			// 
			this->DrawButton->Location = System::Drawing::Point(818, 12);
			this->DrawButton->Name = L"DrawButton";
			this->DrawButton->Size = System::Drawing::Size(75, 75);
			this->DrawButton->TabIndex = 1;
			this->DrawButton->Text = L"Draw!";
			this->DrawButton->UseVisualStyleBackColor = true;
			this->DrawButton->Click += gcnew System::EventHandler(this, &MyForm::DrawButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(819, 94);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"X Pos";
			// 
			// textBoxXPos
			// 
			this->textBoxXPos->Location = System::Drawing::Point(818, 110);
			this->textBoxXPos->Name = L"textBoxXPos";
			this->textBoxXPos->Size = System::Drawing::Size(70, 20);
			this->textBoxXPos->TabIndex = 3;
			this->textBoxXPos->Text = L"-0.5";
			this->textBoxXPos->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxXPos_TextChanged);
			// 
			// textBoxYPos
			// 
			this->textBoxYPos->Location = System::Drawing::Point(817, 149);
			this->textBoxYPos->Name = L"textBoxYPos";
			this->textBoxYPos->Size = System::Drawing::Size(70, 20);
			this->textBoxYPos->TabIndex = 5;
			this->textBoxYPos->Text = L"0.0";
			this->textBoxYPos->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxYPos_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(818, 133);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Y Pos";
			// 
			// textBoxScale
			// 
			this->textBoxScale->Location = System::Drawing::Point(817, 210);
			this->textBoxScale->Name = L"textBoxScale";
			this->textBoxScale->Size = System::Drawing::Size(70, 20);
			this->textBoxScale->TabIndex = 7;
			this->textBoxScale->Text = L"1.0";
			this->textBoxScale->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxScale_TextChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(818, 194);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(34, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Scale";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(900, 476);
			this->Controls->Add(this->textBoxScale);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBoxYPos);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBoxXPos);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->DrawButton);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	std::string ToSTDString(System::String^ In)
	{
		msclr::interop::marshal_context Context;
		return Context.marshal_as<std::string>(In);
	}
	String^ ToSYSString(std::string In)
	{
		msclr::interop::marshal_context Context;
		return Context.marshal_as<String^>(In);
	}

	private: System::Void MyForm_Load(Object^ sender, System::EventArgs^ e)
	{
		//RefreshFunc = &Refresh;
		for (int x = 0; x < Pwidth; x++)
		{
			//DrawArray.push_back({});
			for (int y = 0; y < Pheight; y++)
			{
				//DrawArray[x].push_back(230);
				DrawArray[x][y] = 240;
				DrawArrayC[x][y][0] = 240;
				DrawArrayC[x][y][1] = 240;
				DrawArrayC[x][y][2] = 240;
			}
		}
	}

	private: System::Void MyForm_Paint(Object^ /*sender*/, System::Windows::Forms::PaintEventArgs^ e)
	{
		Console::WriteLine("Begin Draw\n");
		for (int y = 0; y < Pheight; y++)
		{
			for (int x = 0; x < Pwidth; x++)
			{
				Graphics^ g = e->Graphics;
				System::Drawing::SolidBrush^ myBrush =
					//gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(DrawArray[x][y], DrawArray[x][y], DrawArray[x][y]));
					gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(DrawArrayC[x][y][0], DrawArrayC[x][y][1], DrawArrayC[x][y][2]));

				g->FillRectangle(myBrush, Mandlebrot3::Rectangle(x, y, 1, 1));
				delete myBrush;
			}
		}
		int a = 1;
	}

	public:
	void CallRefresh()
	{
		Refresh();
		int a = 1;
	}

	delegate void ManagedSummer();

	static void Foo(MyForm^ p)
	{
		//int Params = 0;
		//MyForm^ t = gcnew MyForm();
		ManagedSummer^ Managed = gcnew ManagedSummer(p, &CallRefresh);
		IntPtr RefreshPointer = Marshal::GetFunctionPointerForDelegate(Managed);
		UnmanagedSummer FunctionPointer = static_cast<UnmanagedSummer>(RefreshPointer.ToPointer());
		//void(*FuncParam)(void) = Refresh;
		DWORD UpdateThreadIDT;
		HANDLE UpdateThreadHandleT = CreateThread(0, 0, UpdateThread, FunctionPointer, 0, &UpdateThreadIDT);

		//p->Refresh();
	}
	
	private: System::Void DrawButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		CompleteCount = 0;

		ViewX[0] = Round(Position[0] - 16.0 / 9.0 * 1.0 / Zoom, 3);
		Console::WriteLine("Val: {0}", ViewX[0]);
		ViewX[1] = Round(Position[0] + 16.0 / 9.0 * 1.0 / Zoom, 4);
		ViewY[0] = Position[1] + 1 * 1.0 / Zoom;
		ViewY[1] = Position[1] - 1 * 1.0 / Zoom;
		
		NextY = ViewY[0];
		StepSize[0] = ((ViewX[1] - ViewX[0]) / Pwidth);
		StepSize[1] = ((ViewY[0] - ViewY[1]) / Pheight);

		/*for (float y = 1; y >= -1; y -= 2/Pheight)
		{
		for (float x = -2; x <= 1; x += 2/Pwidth)
		{*/

		//for (float y = ViewY[0]; y >= ViewY[1]; y -= (2) / Pheight)

		/*
		for (double y = ViewY[0]; y >= ViewY[1]; y -= (ViewY[0] - ViewY[1]) / Pheight)
		{
		//for (float x = ViewX[0]; x <= ViewX[1]; x += (2) / Pwidth)
		for (double x = ViewX[0]; x <= ViewX[1]; x += (ViewX[1] - ViewX[0]) / Pwidth)
		{
		Console::WriteLine("X:{0}  Y:{1}", x, y);
		//X = (x * Pwidth)/2.0 + Pwidth / 2.0;
		X = Map({ ViewX[0],ViewX[1] }, { 0, Pwidth }, x);
		//Y = Pheight - (y * Pheight)/2.0 + Pheight / 2.0;
		Y = Map({ ViewY[0],ViewY[1] }, { 0, Pheight }, y);
		if (TendsToInfinity(Complex(x, y)))
		{
		Colour = 0;
		}
		else
		{
		Colour = 255;
		}
		DrawArray[X][Y] = Colour;
		}
		Refresh();
		}*/

		//Thread1LineComplete = false; Thread2LineComplete = false; Thread3LineComplete = false; Thread4LineComplete = false;
		//Thread1Complete = false; Thread2Complete = false; Thread3Complete = false; Thread4Complete = false;
		//Thread1Ref->Start(); Thread2Ref->Start(); Thread3Ref->Start(); Thread4Ref->Start();
		//Thread5Ref->Start(); Thread6Ref->Start(); Thread7Ref->Start(); Thread8Ref->Start();

		//Thread9Ref->Start(); Thread10Ref->Start(); Thread11Ref->Start(); Thread12Ref->Start();
		//Thread13Ref->Start(); Thread14Ref->Start(); Thread15Ref->Start(); Thread16Ref->Start();

		//Foo(this);


		int Param = 0;
		DWORD CalculateThreadID[NumThreads];
		HANDLE CalculateThreadHandle[NumThreads];
		for (int i = 0; i < NumThreads; i++){ CalculateThreadHandle[i] = CreateThread(0, 0, CalculateThread, &Param, 0, &CalculateThreadID[i]); }
		//HANDLE myHandle = CreateThread(0, 0, myThread, &Param, 0, &myThreadID);
		//CloseHandle(myHandle);

		do
		{

			Refresh();
		}
		while (CompleteCount < NumThreads);
		//Refresh();

		for (int i = 0; i < NumThreads; i++) { CloseHandle(CalculateThreadHandle[i]); }
		//while (!(Thread1Complete  && Thread2Complete && Thread3Complete && Thread4Complete))
		//{
		//	if ( (Thread1LineComplete || Thread1Complete) && (Thread2LineComplete || Thread2Complete) && (Thread3LineComplete || Thread3Complete) && (Thread4LineComplete || Thread4Complete) )
		//	{
		//		Thread1LineComplete = false;
		//		Thread2LineComplete = false;
		//		Thread3LineComplete = false;
		//		Thread4LineComplete = false;
		//		Refresh(); 
		//	}
		//if (Thread2LineComplete) { Thread2LineComplete = false; Refresh(); }
		//if (Thread3LineComplete) { Thread3LineComplete = false; Refresh(); }
		//if (Thread4LineComplete) { Thread4LineComplete = false; Refresh(); }
		//}

	}

	bool LegalNumber(std::string Input)
	{
		bool Legal = true;
		bool ContainString = false;
		bool MultiDecimal = false;
		for each (char Test in Input)
		{
			if (!ContainString && !((Test >= '0' && Test <= '9') || Test == '.' || Test == '-')) { ContainString = true; Legal = false; }
		}

		if (Input.find_first_of(".") != Input.find_last_of(".")) { MultiDecimal = true; Legal = false; }

		try
		{
			long double a = std::stod(Input);
			a;
		}
		catch (...)
		{
			return false;
		}
		return Legal;	
	}

	private: System::Void textBoxXPos_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		std::string Input = ToSTDString(textBoxXPos->Text);

		if (Input == "") { Input = "0"; }
		if (Input == ".") { Input = "0."; }
		if (Input == "-") { Input = "-0"; }

		if (LegalNumber(Input))
		{
			Position[0] = std::stod(Input);
			//ViewX[0] = std::stod(Input) + 16.0 / 9.0 * Zoom;
			//ViewX[1] = std::stod(Input) - 16.0 / 9.0 * Zoom;
		}
		else
		{
			textBoxXPos->Text = ToSYSString(std::to_string(ViewX[0]));
		}
	}
	private: System::Void textBoxYPos_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		std::string Input = ToSTDString(textBoxYPos->Text);

		if (Input == "") { Input = "0"; }
		if (Input == ".") { Input = "0."; }
		if (Input == "-") { Input = "-0"; }

		if (LegalNumber(Input))
		{
			Position[1] = std::stod(Input);
			//ViewY[0] = std::stod(Input) + 1 * Zoom;
			//ViewY[1] = std::stod(Input) - 1 * Zoom;
		}
		else
		{
			textBoxYPos->Text = ToSYSString(std::to_string(ViewX[1]));
		}
	}
	private: System::Void textBoxScale_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		std::string Input = ToSTDString(textBoxScale->Text);

		if (Input == "") { Input = "0"; }
		if (Input == ".") { Input = "0."; }
		if (Input == "-") { Input = "-0"; }

		if (LegalNumber(Input))
		{
			Zoom = std::stod(Input);
		}
		else
		{
			textBoxScale->Text = ToSYSString(std::to_string(ViewY[1]));
		}
	}
};
}



///*
DWORD WINAPI UpdateThread(LPVOID lpParameter)
{
	//void(*Func)(void);
	//Func = (void(*)(void))lpParameter;
	UnmanagedSummer Func = UnmanagedSummer(lpParameter);
	do
	{
		//Refresh();
		Func();
		int a = 1;
		//Sleep(5000);
	}
	while (CompleteCount < NumThreads);
	return 0;
}
//*/



