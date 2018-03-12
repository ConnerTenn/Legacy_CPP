// XMLTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <rapidxml-1.13\rapidxml.hpp>
#include <rapidxml-1.13\rapidxml_print.hpp>

//#include <xercesc\util\PlatformUtils.hpp>

using namespace std;
using namespace rapidxml;

void Test1()
{
	xml_document<> doc;
	xml_node<> * root_node;
	ifstream TheFile("Data.xml");
	vector<char> buffer((istreambuf_iterator<char>(TheFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	print(std::cout, doc, 0);

	root_node = doc.first_node("GameData");
	xml_node<> * node = doc.allocate_node(node_element, "A", "B");
	//doc.first_node("GameData")->append_node(node);
	root_node->append_node(node);
	xml_attribute<> *attr = doc.allocate_attribute("href", "google.com");
	//node->append_attribute(attr);



	cout << "Parsing GameData" << endl;
	xml_document<> doc2;
	xml_node<> * root_node2;
	// Read the xml file into a vector
	ifstream theFile("Data.xml");
	vector<char> buffer2((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer2.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc2.parse<0>(&buffer2[0]);
	// Find our root node
	root_node2 = doc2.first_node("GameData");

	xml_node<> * Position = root_node2->first_node("Position");
	cout << "Pos: X:" << Position->first_attribute("X")->value()
		<< " Y:" << Position->first_attribute("Y")->value() << "\n";
}

void Test2()
{
	// Write xml file =================================
	xml_document<> doc;
	xml_node<>* decl = doc.allocate_node(node_declaration);
	decl->append_attribute(doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
	doc.append_node(decl);

	xml_node<>* root = doc.allocate_node(node_element, "GameData");
	doc.append_node(root);

	xml_node<>* Position = doc.allocate_node(node_element, "Position");
	Position->append_attribute(doc.allocate_attribute("X", "5"));
	Position->append_attribute(doc.allocate_attribute("Y", "9"));
	root->append_node(Position);

	xml_node<>* Stats = doc.allocate_node(node_element, "Stats");
	root->append_node(Stats);

	xml_node<>* Distance = doc.allocate_node(node_element, "Distance");
	Distance->append_attribute(doc.allocate_attribute("Distance", "0"));
	Stats->append_node(Distance);

	// Convert doc to string if needed
	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), doc);

	// Save to file
	std::ofstream file_stored;
	file_stored.open("file_stored.xml");
	file_stored << doc;
	file_stored.close();
	doc.clear();

	// Read xml file =================================
	//xml_document<> doc;
	std::ifstream file("file_stored.xml");

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	print(cout, doc);
}

void Test3()
{
	string filename = "file_stored.xml";
	ifstream input_xml(filename);
	vector<char> xml_copy((istreambuf_iterator<char>(input_xml)), istreambuf_iterator<char>());
	xml_copy.push_back('\0');

	xml_document<> doc;

	doc.parse<rapidxml::parse_no_data_nodes>(&xml_copy[0]);

	xml_node<> * root_node;
	root_node = doc.first_node("GameData");

	// Write xml file =================================
	string Value = "The Distance Travelled";
	root_node->first_node("Stats")->first_node("Distance")->value(doc.allocate_string(Value.c_str(), Value.length()));

	// Convert doc to string if needed
	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), doc);

	// Save to file
	std::ofstream file_stored;
	file_stored.open(filename.c_str());
	file_stored << xml_as_string;
	file_stored.close();
	doc.clear();

	// Read xml file =================================
	//xml_document<> doc;
	std::ifstream file("file_stored.xml");

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	print(cout, doc);
}


void main()
{
	//Test1();
	//Test2();
	Test3();
	
	int a;
	cin >> a;
}

