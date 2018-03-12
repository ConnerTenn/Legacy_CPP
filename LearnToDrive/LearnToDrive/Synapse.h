
class Synapse;

#ifndef _SYNAPSE_
#define _SYNAPSE_

//using namespace std;
#include "Globals.h"
#include "Neuron.h"

class Synapse
{
public:

	double Weight;
	double Value;

	Neuron *Start = 0;
	Neuron *End = 0;
	//std::vector<Neuron*> InputNodes;

public:
	Synapse(Neuron *start, Neuron *end, double weight);
	~Synapse();
	void Update();
	void Draw(System::Windows::Forms::PaintEventArgs^ e);
};

#endif
