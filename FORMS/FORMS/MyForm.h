
#pragma once
#include <string>
#include <msclr\marshal_cppstd.h>
#include <math.h>

namespace FORMS 
{
	using namespace std;

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
	private: System::Windows::Forms::TextBox^  InputTextBox;
	protected:

	private: System::Windows::Forms::TextBox^  OutputTextBox;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->InputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->OutputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// InputTextBox
			// 
			this->InputTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->InputTextBox->Location = System::Drawing::Point(12, 12);
			this->InputTextBox->Name = L"InputTextBox";
			this->InputTextBox->Size = System::Drawing::Size(287, 20);
			this->InputTextBox->TabIndex = 0;
			this->InputTextBox->TextChanged += gcnew System::EventHandler(this, &MyForm::InputTextBox_TextChanged);
			// 
			// OutputTextBox
			// 
			this->OutputTextBox->BackColor = System::Drawing::SystemColors::Window;
			this->OutputTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->OutputTextBox->Location = System::Drawing::Point(12, 38);
			this->OutputTextBox->Multiline = true;
			this->OutputTextBox->Name = L"OutputTextBox";
			this->OutputTextBox->ReadOnly = true;
			this->OutputTextBox->Size = System::Drawing::Size(287, 35);
			this->OutputTextBox->TabIndex = 1;
			this->OutputTextBox->Text = L"Tax:    $0.0000\r\nTotal:  $0.0000";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(311, 86);
			this->Controls->Add(this->OutputTextBox);
			this->Controls->Add(this->InputTextBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"Tax Calc";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void InputTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		msclr::interop::marshal_context Context;
		string Input = Context.marshal_as<string>(InputTextBox->Text);

		if (Input == "")
		{
			Input = "0";
		}
		
		float InputFloat = stof(Input);
		float TaxFloat = InputFloat * 0.13;
		float TotalFloat = InputFloat + TaxFloat;
		String^ TaxString = Context.marshal_as<String^>(to_string(Math::Round(TaxFloat,2)));
		String^ TotalString = Context.marshal_as<String^>(to_string(Math::Round(TotalFloat,2)));
		String^ OutputString = String::Concat("Tax:    $", TaxString, Environment::NewLine, "Total:  $", TotalString);
		OutputTextBox->Text = OutputString;
	}
	};
}
