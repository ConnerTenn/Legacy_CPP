#pragma once

#include <sstream>
#include <iostream>
#include <string>
#include <msclr\marshal_cppstd.h>
#include <vector>

#include "Update.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

using namespace System::Threading;

///*
#include <Windows.h>
#define DBOUT( s )								\
{												\
	std::wostringstream os_;					\
	os_ << s;									\
	OutputDebugStringW(os_.str().c_str());		\
}
//*/



namespace FormsGraphics 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Threading;

	std::string prompt = "Hello";

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
			this->SuspendLayout();
			// 
			// MyForm
			// 
			//this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(800, 450);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"MyForm";
			this->Text = L"Testing...";
			this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::MyForm_Unload);
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
		}
#pragma endregion
	/*private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		//Graphics::FillRectangle(new SolidBrush(Color.FromArgb(230, 230, 230)), 0, 0, Game.CANVAS_Width, Game.CANVAS_HEIGHT);

		System::Drawing::SolidBrush^ myBrush =
			gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(230, 230, 230));

		System::Drawing::Graphics^ formGraphics;
		formGraphics = this->CreateGraphics();
		//formGraphics->FillRectangle(myBrush, Rectangle(0, 0, 200, 300));

		//drawHandle::DrawImage(frame, 0, 0);
		//formGraphics->DrawImage(frame)

		delete myBrush;
		delete formGraphics;
	}*/

	public:

	Thread^ UpdateThread = gcnew Thread(gcnew ThreadStart(&UpdateClass::UpdateFunc));

	private: System::Void MyForm_Load(Object^ sender, System::EventArgs^ e)
	{
		//pictureBox1 = gcnew PictureBox;

		// Dock the PictureBox to the form and set its background to white.
		//pictureBox1->Dock = DockStyle::Fill;
		//this->pictureBox1->BackColor = Color::Black;

		// Add the PictureBox control to the Form.
		//this->Controls->Add(pictureBox1);
		UpdateThread->Start();

		DBOUT("Load\n");
	}
	private: System::Void MyForm_Unload(Object^ sender, System::ComponentModel::CancelEventArgs^ e)
	{
		UpdateThread->Abort();

		DBOUT("Unload\n");
	}

	private: System::Void MyForm_Paint(Object^ /*sender*/, System::Windows::Forms::PaintEventArgs^ e)
	{
		//q = e;
		// Create a local version of the graphics object for the PictureBox.
		//Graphics^ g = e->Graphics;
		Bitmap^ frame = gcnew Bitmap(this->Width, this->Height);
		Graphics^ g = Graphics::FromImage(frame);

		/*System::Drawing::SolidBrush^ myBrush =
			gcnew System::Drawing::SolidBrush(System::Drawing::Color::Red);

		g->FillRectangle(myBrush, FormsGraphics::Rectangle(0, 0, this->Width, this->Height));
		delete myBrush;

		g->Clear(Color::White);
		// Draw a string on the PictureBox.
		//std::string prompt = "Hello";
		//static std::string prompt = "Hello";
		prompt += ".";
		msclr::interop::marshal_context Context;
		String^ Prompt = Context.marshal_as<String^>(prompt);
		g->DrawString(Prompt,
			gcnew System::Drawing::Font("Arial", 10), System::Drawing::Brushes::Blue, Point(30, 30));

		// Draw a line in the PictureBox.
		g->DrawLine(System::Drawing::Pens::Red, 0, 0,
			this->Width, this->Height);
		g->DrawRectangle(System::Drawing::Pens::Red, 20, 20,
			this->Width - 100 + 20, this->Height - 100 + 20);*/
		g->DrawRectangle(System::Drawing::Pens::Red, 0, 0,
			783, 410);
		
		e->Graphics->DrawImage(frame, 0, 0);
		//DBOUT("Width:" << this->Width << "  Height:" << this->Height << "\n");
		//DBOUT("Width:" << this->ClientSize.Width << "  Height:" << this->ClientSize.Height << "\n\n");
	}
	
	//PaintEventArgs^ q;

	//public:
	//bool UpdateLoopRunning = false;
	//void UpdateLoop()
	//{
	//}
	//Thread^ UpdateThread2 = gcnew Thread(gcnew ThreadStart(this->UpdateLoop));

	protected:
	virtual void OnPaint(PaintEventArgs^ e) override
	{
		//q = e;
		//if (!UpdateLoopRunning) { UpdateThread2->Start(); }
		
		// Create a local version of the graphics object for the PictureBox.
		Graphics^ g = e->Graphics;
		//Bitmap^ frame = gcnew Bitmap(this->Width, this->Height);
		//Graphics^ g = Graphics::FromImage(frame);
		
		for (int y = 10; y < this->ClientSize.Height; y += 20)
		{
			for (int x = 10; x < this->ClientSize.Width; x += 20)
			{
				g->FillRectangle(gcnew SolidBrush(Color::FromArgb(0,0,0)), FormsGraphics::Rectangle(x, y, 5, 5));
				//g->DrawRectangle(System::Drawing::Pens::Blue, x, y, 5, 5);
			}
		}

		int exponent = 0;
		std::vector<std::vector<float>> List;
		float num = 5;
		float i = 1;
		do
		{
			List.push_back({ num, i });
			num *= 2;
			i *= 2;
			List.push_back({ num, i });
			num *= 5;
			i *= 2;
		}
		while (num < this->ClientSize.Width);

		for (int x = 0; x < this->ClientSize.Width; x++)
		{
			for (std::vector<float> i : List)
			{
				if (x / i[0] == int(x / i[0]))
				{
					g->DrawLine(Pens::Green, Point(x, 0), Point(x, i[1] * 4));
				}
			}

		}
		
		// Draw a string on the PictureBox.
		//std::string prompt = "Hello";
		//static std::string prompt = "Hello";
		//prompt += ".";
		//msclr::interop::marshal_context Context;
		//String^ Prompt = Context.marshal_as<String^>(prompt);
		//g->DrawString(Prompt,
		//	gcnew System::Drawing::Font("Arial", 10), System::Drawing::Brushes::Blue, Point(30, 30));

		// Draw a line in the PictureBox.
		//g->DrawLine(System::Drawing::Pens::Red, 0, 0,
		//	this->Width, this->Height);

		//g->DrawRectangle(System::Drawing::Pens::Red, 0, 0,
		//	783, 410);

		//e->Graphics->DrawImage(frame, 0, 0);
		
		//e->Graphics->DrawLine(System::Drawing::Pens::Red, 0, 0,
		//	this->Width, this->Height);

		//DBOUT("Width:" << this->Width << "  Height:" << this->Height << "\n");
		//DBOUT("ClientWidth:" << this->ClientSize.Width << "  ClientHeight:" << this->ClientSize.Height << "\n\n");
	}
};
}
