#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

using namespace System::Threading;

class UpdateClass
{
public:
	static void UpdateFunc()
	{
		while (false)// (true)
		{
			//MyForm::q;
			//q->Graphics->DrawLine(System::Drawing::Pens::Red, 0, 0,
			//	this->Width, this->Height);
			Console::WriteLine("Hello");
			Sleep(100);
		}
	}
};

