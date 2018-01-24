// MultiTypeList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>


class Property
{
public:
	Property(const std::string& name) //note: we don't lightly copy strings in C++
		: m_name(name)
	{
	}
	virtual ~Property() {}
private:
	std::string m_name;
};

template< typename T >
class TypedProperty : public Property
{
public:
	TypedProperty(const std::string& name, const T& data)
		: Property(name), m_data(data)
	{
	};
private:
	T m_data;
};

//typedef std::vector< std::shared_ptr<Property> > property_list_type;
//typedef std::vector<Property *> property_list_type;
typedef std::vector<Property *> property_list_type;


/*struct VariableType
{
	void *Value;
	
};*/

void main()
{
	/*VariableType val;
	std::vector<VariableType> list;
	val.Value = (void *)(new int(6));
	list.push_back(val);
	val.Value = (void *)(new float(9.2f));
	list.push_back(val);

	std::cout << "0: " << *((int *)list[0].Value) << "\n";
	std::cout << "1: " << *((float *)list[1].Value) << "\n";

	std::cout << "\n\n\n";*/

	property_list_type list;
	int a = 6;
	double b = 5.7;
	//list.push_back(std::make_shared<TypedProperty<int>>("unsigned int", a));
	list.push_back(new TypedProperty<int>("int",a));

	//list.push_back(std::make_shared<TypedProperty<double>>("double", b));
	list.push_back(new TypedProperty<double>("double", b));

	//std::cout << "0: " << list[0]. << "\n";
	//std::cout << "1: " << list[1] << "\n";

	std::string Out;
	std::getline(std::cin, Out);
}

