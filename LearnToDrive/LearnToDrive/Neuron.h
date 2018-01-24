
class Neuron;

#ifndef _NEURON_
#define _NEURON_

#include "Globals.h"
#include "Synapse.h"

class Neuron
{
public:
	double Value;

	unsigned int ID;
	std::vector<Synapse*> Input;
	std::vector<Synapse*> Output;
	int X;
	int Y;

public:
	Neuron();
	Neuron(int x, int y, unsigned int id);//, Synapse *input = 0, Synapse *output = 0);
	~Neuron();
	void Update();
	void Draw(System::Windows::Forms::PaintEventArgs^ e);
};

#endif
