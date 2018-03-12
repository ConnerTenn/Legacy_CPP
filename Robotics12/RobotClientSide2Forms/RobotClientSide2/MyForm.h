#pragma once

#include <msclr\marshal_cppstd.h>
#include "Engine.h"

namespace RobotClientSide2 
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Desktop;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1184, 561);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(884, 561);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"RobotClientSide2";
			this->ResumeLayout(false);

			this->Controls->Add(this->pictureBox1);
			this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::MyForm_Unload);
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Shown += gcnew System::EventHandler(this, &MyForm::MyForm_Shown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		Engine* engine = new Engine();

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
			Console::WriteLine("Load\n");
		}

		private: System::Void MyForm_Unload(Object^ sender, System::ComponentModel::CancelEventArgs^ e)
		{
			Console::WriteLine("Unloading\n");
			engine->Run = false;
			delete(engine);
			engine = 0;
		}

		private: System::Void MyForm_Idle(Object^ sender, System::EventArgs^ e)
		{
			Console::WriteLine("Idle\n");

			//engine->Update();

			//Refresh();
		}

		private: System::Void MyForm_Shown(Object^ sender, System::EventArgs^ e)
		{
			clock_t Time1;
			clock_t Time2;
			double DeltaTime;

			System::Windows::Forms::Application::DoEvents();
			while (this->Created && engine->Run)
			{
				Time1 = clock();
				//Console::WriteLine("Update\n");
				engine->Update();
				Refresh();
				//Sleep(10);
				System::Windows::Forms::Application::DoEvents();
				Time2 = clock();

				DeltaTime = (Time2 - Time1);

				//Run at a constant maximum speed
				double Delay = DeltaTime < 1000.0 / FrameRate ? 1000.0 / FrameRate - DeltaTime : 0;
				Sleep(static_cast<DWORD>(Delay));
				//Sleep(Delay);

				Console::WriteLine("Delta Time: {0}ms \tDeltaTime Raw: {1}ms \tDelay: {2}ms", DeltaTime + Delay, DeltaTime, Delay);
				//Console::WriteLine("Delay: {0}ms", (DeltaTime < 1000.0 / FrameRate ? 1000.0 / FrameRate - DeltaTime : 0));
				//Console::WriteLine("Delta Time: {0}ms", DeltaTime);
			}
		}

		private: System::Void MyForm_Paint(Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
		{
			//Console::WriteLine("Begin Draw\n");

			this->pictureBox1->Size = this->ClientSize;
			engine->Render(e, this->pictureBox1->Size.Width, this->pictureBox1->Size.Height);

			/*Console::WriteLine("Begin Draw\n");
			Graphics^ g = e->Graphics;

			Drawing::SolidBrush^ myBrush =
			gcnew System::Drawing::SolidBrush(Drawing::Color::FromArgb(0, 0, 255));
			//g->FillRectangle(myBrush, LearnToDrive::Rectangle(1, 1, 10, 10));
			g->FillRectangle(myBrush, Drawing::Rectangle::Rectangle(1, 1, 10, 10));*/
		}

	};
}
