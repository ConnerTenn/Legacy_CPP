
#include <iostream>
#include <string>


struct Variable
{
	int *Var = 0;

	Variable() {}

	static void New(Variable *var, int val)
	{
		var->Var = new int(val);
		int a = 1;
	}

	static void Delete(Variable *var)
	{
		delete var->Var; var->Var = 0;
	}
};

template<typename T>
class Deleter
{
public:
	T Object;
	void (*Func)(T *);

	Deleter() {}
	Deleter(void (*func)(T *)) 
	{
		Func = func;
	}

	~Deleter()
	{
		Cleanup();
	}

	void Cleanup()
	{
		Func(&Object);
	}

	T * operator &()
	{
		Cleanup();
		return &Object;
	}

	operator T() const
	{
		return Object;
	}
};

void main()
{
	std::cout << "Begin\n";

	for (int i = 0; i < 10000000; i++)
	{
		Deleter<Variable> var{ Variable::Delete };
		//Variable var;
		Variable::New(&var, 6);
		int a = 1;
	}
	//Variable::Delete(Var);

	std::cout << "End\n";
	
	std::string out;
	std::getline(std::cin, out);
}


