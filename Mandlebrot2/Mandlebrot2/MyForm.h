#pragma once

#include "Complex.h"
#include <Windows.h>

//std::vector<std::vector<int>> DrawArray;
int DrawArray[800][450];
int DrawArrayC[800][450][3];

float Pwidth = 800; float Pheight = 450;

double ViewX[2] = { -2, 1 };
double ViewY[2] = { 1, -1 };
double StepSize[2] = { ((ViewX[1] - ViewX[0]) / Pwidth), ((ViewY[0] - ViewY[1]) / Pheight) };

//bool Thread1LineComplete = false, Thread2LineComplete = false, Thread3LineComplete = false, Thread4LineComplete = false;
//bool Thread1Complete = false, Thread2Complete = false, Thread3Complete = false, Thread4Complete = false;
//bool Complete = false;
int CompleteCount = 0;
double NextY = ViewY[0];
//#pragma managed

//void(*RefreshFunc)();

class ThreadClass
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
	}*/
	/*static void Thread()
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
	}*/
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
				}*/
				ColourC = TendsToInfinityColour(Complex(x, y));
				//DrawArray[X][Y] = Colour;
				DrawArrayC[X][Y][0] = ColourC[0];
				DrawArrayC[X][Y][1] = ColourC[1];
				DrawArrayC[X][Y][2] = ColourC[2];
			}
		}
		CompleteCount++;
	}
};

namespace Mandlebrot2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(900, 476);
			this->Controls->Add(this->DrawButton);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	Thread^ Thread1Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread2Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread3Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread4Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread5Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread6Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread7Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread8Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));

	Thread^ Thread9Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread10Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread11Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread12Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread13Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread14Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread15Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	Thread^ Thread16Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread));
	//Thread^ Thread2Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread2));
	//Thread^ Thread3Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread3));
	//Thread^ Thread4Ref = gcnew Thread(gcnew ThreadStart(&ThreadClass::Thread4));

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

				g->FillRectangle(myBrush, Mandlebrot2::Rectangle(x, y, 1, 1));
				delete myBrush;
			}
		}
	}
	private: System::Void DrawButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		CompleteCount = 0;
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
		Thread1Ref->Start(); Thread2Ref->Start(); Thread3Ref->Start(); Thread4Ref->Start();
		Thread5Ref->Start(); Thread6Ref->Start(); Thread7Ref->Start(); Thread8Ref->Start();

		Thread9Ref->Start(); Thread10Ref->Start(); Thread11Ref->Start(); Thread12Ref->Start();
		Thread13Ref->Start(); Thread14Ref->Start(); Thread15Ref->Start(); Thread16Ref->Start();

		while (CompleteCount < 16)
		{
			Refresh();
			//Sleep(5000);
		}
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

		Thread1Ref->Abort(); Thread2Ref->Abort(); Thread3Ref->Abort(); Thread4Ref->Abort();
		Thread5Ref->Abort(); Thread6Ref->Abort(); Thread7Ref->Abort(); Thread8Ref->Abort();

		Thread9Ref->Abort(); Thread10Ref->Abort(); Thread11Ref->Abort(); Thread12Ref->Abort();
		Thread13Ref->Abort(); Thread14Ref->Abort(); Thread15Ref->Abort(); Thread16Ref->Abort();
	}
	};
}
