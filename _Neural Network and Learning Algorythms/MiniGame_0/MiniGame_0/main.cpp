
#include <iostream>
//#include <time.h>
#include <string>
//#include <sstream>
//#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <rapidxml-1.13\rapidxml.hpp>
#include <rapidxml-1.13\rapidxml_print.hpp>
using namespace rapidxml;

void FormatXmlData();
void ResetXml();

bool Run = true;
xml_document<> XmlDoc;
//std::fstream File("Data.xml", std::fstream::in | std::fstream::out | std::fstream::app);
//std::fstream File;
xml_node<> *RootNode = 0;
xml_node<> *TimeNode = 0;
xml_node<> *InputNode = 0;
xml_node<> *ValuesNode = 0;
xml_node<> *RewardNode = 0;

std::string OutBuffer;

/*
<Time Time="1">
	<Input Input="E"/>
	<Values X="0" Y="0"/>
	<Reward Reward="0"/>
	<GroupReward>
		<Reward>
			<X Value ="0" Count="1"/>
			<Y Value ="0" Count="1"/>
			<?X Value ="0" Count="1"/>
			<?Y Value ="0" Count="1"/>
			<Input Value ="A" Count="1"/>
		</Reward>
	</GroupReward>
</Time>
*/

void Input(std::vector<std::string> &args)
{
	args.clear();
	std::string in;
	size_t pos = 0;

	std::getline(std::cin, in);
	std::transform(in.begin(), in.end(), in.begin(), ::toupper);

	//std::string buffer;
	while ((pos = in.find(" ")) != std::string::npos)
	{
		args.push_back(in.substr(0, pos));
		in.erase(0, pos + 1);
	}
	args.push_back(in.substr(0, in.length()));
}

class GameControl
{
public:
	bool Play = false;
	int X = 0; int Y = 0;
	int Reward = 0;
	int Time = 0;

	void Start()
	{
		std::cout << "Game Beginning\n";
		Play = true;
		X = 0; Y = 0;
		Reward = 0;
		Time = 0;

		ResetXml();

		TimeNode = XmlDoc.allocate_node(node_element, "Time");
		TimeNode->append_attribute(XmlDoc.allocate_attribute("Time", "0"));
		RootNode->append_node(TimeNode);

		InputNode = XmlDoc.allocate_node(node_element, "Input");
		InputNode->append_attribute(XmlDoc.allocate_attribute("Input", "NULL"));
		TimeNode->append_node(InputNode);

		ValuesNode = XmlDoc.allocate_node(node_element, "Values");
		ValuesNode->append_attribute(XmlDoc.allocate_attribute("X", "0"));
		ValuesNode->append_attribute(XmlDoc.allocate_attribute("Y", "0"));
		TimeNode->append_node(ValuesNode);

		RewardNode = XmlDoc.allocate_node(node_element, "Reward");
		RewardNode->append_attribute(XmlDoc.allocate_attribute("Reward", "NULL"));
		TimeNode->append_node(RewardNode);

		GenerateGroupReward(std::string("NULL"));
		GenerateGroupInput(std::string("NULL"));

		std::cout << "Values: " << X  << ", " << Y << " Reward: Null" << "\n";
	}
	void Update(std::string &input)
	{
		Time++;
		if (input == "A") 
		{ 
			Y += 1;
			if (Reward == 2) { Reward = 3; }
			else { Reward = 1; }
		}
		else if (input == "B") 
		{ 
			X += 1;
			if (Reward != 3) { Reward = 2; }
			else if (Reward == 3) { Reward = 4; }
			else { Reward = 1; }
		}
		else if (input == "C") 
		{ 
			Y += -1;
			Reward = 1;
		}
		else if (input == "D") 
		{ 
			X += -1;
			Reward = 1;
		}
		else if (input == "E") 
		{ 
			Reward = 0;
		}

		if (X > 9 || Y > 9)
		{
			Reward = -1;
			if (input == "A" || input == "B" || input == "E")
			{
				Reward = -2;
			}
		}
		if (X < -9 || Y < -9)
		{
			if (input == "C" || input == "D" || input == "E")
			{
				Reward = -2;
			}
		}

		TimeNode = XmlDoc.allocate_node(node_element, "Time");
		TimeNode->append_attribute(XmlDoc.allocate_attribute("Time", XmlDoc.allocate_string(std::to_string(Time).c_str())));
		RootNode->append_node(TimeNode);

		InputNode = XmlDoc.allocate_node(node_element, "Input");
		InputNode->append_attribute(XmlDoc.allocate_attribute("Input", XmlDoc.allocate_string(input.c_str())));
		TimeNode->append_node(InputNode);

		ValuesNode = XmlDoc.allocate_node(node_element, "Values");
		ValuesNode->append_attribute(XmlDoc.allocate_attribute("X", XmlDoc.allocate_string(std::to_string(X).c_str())));
		ValuesNode->append_attribute(XmlDoc.allocate_attribute("Y", XmlDoc.allocate_string(std::to_string(Y).c_str())));
		TimeNode->append_node(ValuesNode);

		RewardNode = XmlDoc.allocate_node(node_element, "Reward");
		RewardNode->append_attribute(XmlDoc.allocate_attribute("Reward", XmlDoc.allocate_string(std::to_string(Reward).c_str())));
		TimeNode->append_node(RewardNode);

		GenerateGroupReward(input);
		GenerateGroupInput(input);

		std::cout << "Values: " << X << ", " << Y << " Reward: " << Reward << "\n";
	}

	void GenerateGroupReward(std::string &input)
	{
		//If Previous Reward Exists
		xml_node<> *previousTimeNode = TimeNode->previous_sibling("Time");
		if (previousTimeNode)
		{
			//get previous node
			xml_node<> *previousGroupRewardNode = previousTimeNode->first_node("GroupReward");

			if (previousGroupRewardNode->first_node("Reward")->first_attribute("Reward")->value() == "NULL") 
			{ 
				//create new GroupReward and initialize elements
				xml_node<> *groupRewardNode = XmlDoc.allocate_node(node_element, "GroupReward");
				TimeNode->append_node(groupRewardNode);

				xml_node<> *rewardNode = XmlDoc.allocate_node(node_element, "Reward");
				rewardNode->append_attribute(XmlDoc.allocate_attribute("Reward", XmlDoc.allocate_string(std::to_string(Reward).c_str())));
				rewardNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
				groupRewardNode->append_node(rewardNode);

				xml_node<> *xNode = XmlDoc.allocate_node(node_element, "X");
				xNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X).c_str())));
				xNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
				rewardNode->append_node(xNode);

				xml_node<> *yNode = XmlDoc.allocate_node(node_element, "Y");
				yNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y).c_str())));
				yNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
				rewardNode->append_node(yNode);

				xml_node<> *deltaXNode = XmlDoc.allocate_node(node_element, "DeltaX");
				int previousX = std::stoi(previousTimeNode->first_node("Values")->first_attribute("X")->value());
				deltaXNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X - previousX).c_str())));
				deltaXNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
				rewardNode->append_node(deltaXNode);

				xml_node<> *deltaYNode = XmlDoc.allocate_node(node_element, "DeltaY");
				int previousY = std::stoi(previousTimeNode->first_node("Values")->first_attribute("Y")->value());
				deltaYNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y - previousY).c_str())));
				deltaYNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
				rewardNode->append_node(deltaYNode);

				xml_node<> *inputNode = XmlDoc.allocate_node(node_element, "Input");
				inputNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(input.c_str())));
				inputNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
				rewardNode->append_node(inputNode);
			}
			else
			{
				//Copy previous GroupReward
				TimeNode->append_node(XmlDoc.clone_node(previousGroupRewardNode));
				//get GroupReward from current TimeNode
				xml_node<> *groupRewardNode = TimeNode->first_node("GroupReward");

				//find if there is a element with the same reward
				xml_node<> *sameRewardNode = groupRewardNode->first_node("Reward");
				while (sameRewardNode && sameRewardNode->first_attribute("Reward")->value() != std::to_string(Reward))
				{
					sameRewardNode = sameRewardNode->next_sibling("Reward");
				}

				if (sameRewardNode)
				{
					//Reward already exists; edit data
					sameRewardNode->first_attribute("Count")->value(XmlDoc.allocate_string(std::to_string(std::stoi(sameRewardNode->first_attribute("Count")->value()) + 1).c_str()));

					{/*Find if X already exists*/}
					{
						xml_node<> *sameXNode = sameRewardNode->first_node("X");
						while (sameXNode && sameXNode->first_attribute("Value")->value() != std::to_string(X))
						{
							sameXNode = sameXNode->next_sibling("X");
						}

						if (sameXNode)
						{
							//edit data
							sameXNode->first_attribute("Count")->value(XmlDoc.allocate_string(std::to_string(std::stoi(sameXNode->first_attribute("Count")->value()) + 1).c_str()));
						}
						else
						{
							xml_node<> *xNode = XmlDoc.allocate_node(node_element, "X");
							xNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X).c_str())));
							xNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
							sameRewardNode->append_node(xNode);
						}
					}

					{/*Find if Y already exists*/ }
					{
						xml_node<> *sameYNode = sameRewardNode->first_node("Y");
						while (sameYNode && sameYNode->first_attribute("Value")->value() != std::to_string(Y))
						{
							sameYNode = sameYNode->next_sibling("Y");
						}

						if (sameYNode)
						{
							//edit data
							sameYNode->first_attribute("Count")->value(XmlDoc.allocate_string(std::to_string(std::stoi(sameYNode->first_attribute("Count")->value()) + 1).c_str()));
						}
						else
						{
							xml_node<> *YNode = XmlDoc.allocate_node(node_element, "Y");
							YNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y).c_str())));
							YNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
							sameRewardNode->append_node(YNode);
						}
					}

					{/*Find if DeltaX already exists*/ }
					{
						int previousX = std::stoi(previousTimeNode->first_node("Values")->first_attribute("X")->value());
						xml_node<> *sameDeltaXNode = sameRewardNode->first_node("DeltaX");
						while (sameDeltaXNode && sameDeltaXNode->first_attribute("Value")->value() != std::to_string(X - previousX))
						{
							sameDeltaXNode = sameDeltaXNode->next_sibling("DeltaX");
						}

						if (sameDeltaXNode)
						{
							//edit data
							sameDeltaXNode->first_attribute("Count")->value(XmlDoc.allocate_string(std::to_string(std::stoi(sameDeltaXNode->first_attribute("Count")->value()) + 1).c_str()));
						}
						else
						{
							xml_node<> *deltaXNode = XmlDoc.allocate_node(node_element, "DeltaX");
							deltaXNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X - previousX).c_str())));
							deltaXNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
							sameRewardNode->append_node(deltaXNode);
						}
					}

					{/*Find if DeltaY already exists*/ }
					{
						int previousY = std::stoi(previousTimeNode->first_node("Values")->first_attribute("Y")->value());
						xml_node<> *sameDeltaYNode = sameRewardNode->first_node("DeltaY");
						while (sameDeltaYNode && sameDeltaYNode->first_attribute("Value")->value() != std::to_string(Y - previousY))
						{
							sameDeltaYNode = sameDeltaYNode->next_sibling("DeltaY");
						}

						if (sameDeltaYNode)
						{
							//edit data
							sameDeltaYNode->first_attribute("Count")->value(XmlDoc.allocate_string(std::to_string(std::stoi(sameDeltaYNode->first_attribute("Count")->value()) + 1).c_str()));
						}
						else
						{
							xml_node<> *deltaYNode = XmlDoc.allocate_node(node_element, "DeltaY");
							deltaYNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y - previousY).c_str())));
							deltaYNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
							sameRewardNode->append_node(deltaYNode);
						}
					}

					{/*Find if Input already exists*/ }
					{
						xml_node<> *sameInputNode = sameRewardNode->first_node("Input");
						while (sameInputNode && sameInputNode->first_attribute("Value")->value() != input)
						{
							sameInputNode = sameInputNode->next_sibling("Input");
						}

						if (sameInputNode)
						{
							//edit data
							sameInputNode->first_attribute("Count")->value(XmlDoc.allocate_string(std::to_string(std::stoi(sameInputNode->first_attribute("Count")->value()) + 1).c_str()));
						}
						else
						{
							xml_node<> *inputNode = XmlDoc.allocate_node(node_element, "Input");
							inputNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(input.c_str())));
							inputNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
							sameRewardNode->append_node(inputNode);
						}
					}					
				}
				else
				{
					//create new data
					xml_node<> *rewardNode = XmlDoc.allocate_node(node_element, "Reward");
					rewardNode->append_attribute(XmlDoc.allocate_attribute("Reward", XmlDoc.allocate_string(std::to_string(Reward).c_str())));
					rewardNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
					groupRewardNode->append_node(rewardNode);

					xml_node<> *xNode = XmlDoc.allocate_node(node_element, "X");
					xNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X).c_str())));
					xNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
					rewardNode->append_node(xNode);

					xml_node<> *yNode = XmlDoc.allocate_node(node_element, "Y");
					yNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y).c_str())));
					yNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
					rewardNode->append_node(yNode);

					xml_node<> *deltaXNode = XmlDoc.allocate_node(node_element, "DeltaX");
					int previousX = std::stoi(previousTimeNode->first_node("Values")->first_attribute("X")->value());
					deltaXNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X - previousX).c_str())));
					deltaXNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
					rewardNode->append_node(deltaXNode);

					xml_node<> *deltaYNode = XmlDoc.allocate_node(node_element, "DeltaY");
					int previousY = std::stoi(previousTimeNode->first_node("Values")->first_attribute("Y")->value());
					deltaYNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y - previousY).c_str())));
					deltaYNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
					rewardNode->append_node(deltaYNode);

					xml_node<> *inputNode = XmlDoc.allocate_node(node_element, "Input");
					inputNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(input.c_str())));
					inputNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
					rewardNode->append_node(inputNode);
				}
			}
		}
		else
		{
			xml_node<> *groupRewardNode = XmlDoc.allocate_node(node_element, "GroupReward");
			TimeNode->append_node(groupRewardNode);

			xml_node<> *rewardNode = XmlDoc.allocate_node(node_element, "Reward");
			rewardNode->append_attribute(XmlDoc.allocate_attribute("Reward", "NULL"));
			rewardNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
			groupRewardNode->append_node(rewardNode);

			xml_node<> *xNode = XmlDoc.allocate_node(node_element, "X");
			xNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X).c_str())));
			xNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
			rewardNode->append_node(xNode);
			xml_node<> *yNode = XmlDoc.allocate_node(node_element, "Y");
			yNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y).c_str())));
			yNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
			rewardNode->append_node(yNode);
		}
	}

	void GenerateGroupInput(std::string &input)
	{
		//If Previous Reward Exists
		xml_node<> *previousTimeNode = TimeNode->previous_sibling("Time");
		if (previousTimeNode)
		{
			//get previous node
			xml_node<> *previousGroupInputNode = previousTimeNode->first_node("GroupInput");

			if (previousGroupInputNode->first_node("Input")->first_attribute("Input")->value() == "NULL")
			{
				//create new GroupReward and initialize elements
				xml_node<> *groupInputNode = XmlDoc.allocate_node(node_element, "GroupInput");
				TimeNode->append_node(groupInputNode);

				xml_node<> *inputNode = XmlDoc.allocate_node(node_element, "Input");
				inputNode->append_attribute(XmlDoc.allocate_attribute("Input", XmlDoc.allocate_string(input.c_str())));
				inputNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
				groupInputNode->append_node(inputNode);

				xml_node<> *xNode = XmlDoc.allocate_node(node_element, "X");
				xNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X).c_str())));
				xNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
				inputNode->append_node(xNode);

				xml_node<> *yNode = XmlDoc.allocate_node(node_element, "Y");
				yNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y).c_str())));
				yNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
				inputNode->append_node(yNode);

				xml_node<> *deltaXNode = XmlDoc.allocate_node(node_element, "DeltaX");
				int previousX = std::stoi(previousTimeNode->first_node("Values")->first_attribute("X")->value());
				deltaXNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X - previousX).c_str())));
				deltaXNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
				inputNode->append_node(deltaXNode);

				xml_node<> *deltaYNode = XmlDoc.allocate_node(node_element, "DeltaY");
				int previousY = std::stoi(previousTimeNode->first_node("Values")->first_attribute("Y")->value());
				deltaYNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y - previousY).c_str())));
				deltaYNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
				inputNode->append_node(deltaYNode);

				xml_node<> *rewardNode = XmlDoc.allocate_node(node_element, "Reward");
				rewardNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Reward).c_str())));
				rewardNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
				inputNode->append_node(rewardNode);
			}
			else
			{
				//Copy previous GroupReward
				TimeNode->append_node(XmlDoc.clone_node(previousGroupInputNode));
				//get GroupReward from current TimeNode
				xml_node<> *groupInputNode = TimeNode->first_node("GroupInput");

				//find if there is a element with the same Input
				xml_node<> *sameInputNode = groupInputNode->first_node("Input");
				while (sameInputNode && sameInputNode->first_attribute("Input")->value() != input)
				{
					sameInputNode = sameInputNode->next_sibling("Input");
				}

				if (sameInputNode)
				{
					//Reward already exists; edit data
					sameInputNode->first_attribute("Count")->value(XmlDoc.allocate_string(std::to_string(std::stoi(sameInputNode->first_attribute("Count")->value()) + 1).c_str()));

					{/*Find if X already exists*/ }
					{
						xml_node<> *sameXNode = sameInputNode->first_node("X");
						while (sameXNode && sameXNode->first_attribute("Value")->value() != std::to_string(X))
						{
							sameXNode = sameXNode->next_sibling("X");
						}

						if (sameXNode)
						{
							//edit data
							sameXNode->first_attribute("Count")->value(XmlDoc.allocate_string(std::to_string(std::stoi(sameXNode->first_attribute("Count")->value()) + 1).c_str()));
						}
						else
						{
							xml_node<> *xNode = XmlDoc.allocate_node(node_element, "X");
							xNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X).c_str())));
							xNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
							sameInputNode->append_node(xNode);
						}
					}

					{/*Find if Y already exists*/ }
					{
						xml_node<> *sameYNode = sameInputNode->first_node("Y");
						while (sameYNode && sameYNode->first_attribute("Value")->value() != std::to_string(Y))
						{
							sameYNode = sameYNode->next_sibling("Y");
						}

						if (sameYNode)
						{
							//edit data
							sameYNode->first_attribute("Count")->value(XmlDoc.allocate_string(std::to_string(std::stoi(sameYNode->first_attribute("Count")->value()) + 1).c_str()));
						}
						else
						{
							xml_node<> *YNode = XmlDoc.allocate_node(node_element, "Y");
							YNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y).c_str())));
							YNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
							sameInputNode->append_node(YNode);
						}
					}

					{/*Find if DeltaX already exists*/ }
					{
						int previousX = std::stoi(previousTimeNode->first_node("Values")->first_attribute("X")->value());
						xml_node<> *sameDeltaXNode = sameInputNode->first_node("DeltaX");
						while (sameDeltaXNode && sameDeltaXNode->first_attribute("Value")->value() != std::to_string(X - previousX))
						{
							sameDeltaXNode = sameDeltaXNode->next_sibling("DeltaX");
						}

						if (sameInputNode)
						{
							//edit data
							sameDeltaXNode->first_attribute("Count")->value(XmlDoc.allocate_string(std::to_string(std::stoi(sameDeltaXNode->first_attribute("Count")->value()) + 1).c_str()));
						}
						else
						{
							xml_node<> *deltaXNode = XmlDoc.allocate_node(node_element, "DeltaX");
							deltaXNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X - previousX).c_str())));
							deltaXNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
							sameInputNode->append_node(deltaXNode);
						}
					}

					{/*Find if DeltaY already exists*/ }
					{
						int previousY = std::stoi(previousTimeNode->first_node("Values")->first_attribute("Y")->value());
						xml_node<> *sameDeltaYNode = sameInputNode->first_node("DeltaY");
						while (sameDeltaYNode && sameDeltaYNode->first_attribute("Value")->value() != std::to_string(Y - previousY))
						{
							sameDeltaYNode = sameDeltaYNode->next_sibling("DeltaY");
						}

						if (sameDeltaYNode)
						{
							//edit data
							sameDeltaYNode->first_attribute("Count")->value(XmlDoc.allocate_string(std::to_string(std::stoi(sameDeltaYNode->first_attribute("Count")->value()) + 1).c_str()));
						}
						else
						{
							xml_node<> *deltaYNode = XmlDoc.allocate_node(node_element, "DeltaY");
							deltaYNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y - previousY).c_str())));
							deltaYNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
							sameInputNode->append_node(deltaYNode);
						}
					}

					{/*Find if Reward already exists*/ }
					{
						xml_node<> *sameRewardNode = sameInputNode->first_node("Reward");
						while (sameRewardNode && sameRewardNode->first_attribute("Value")->value() != std::to_string(Reward))
						{
							sameRewardNode = sameRewardNode->next_sibling("Reward");
						}

						if (sameRewardNode)
						{
							//edit data
							sameRewardNode->first_attribute("Count")->value(XmlDoc.allocate_string(std::to_string(std::stoi(sameRewardNode->first_attribute("Count")->value()) + 1).c_str()));
						}
						else
						{
							xml_node<> *inputNode = XmlDoc.allocate_node(node_element, "Reward");
							inputNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Reward).c_str())));
							inputNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
							sameInputNode->append_node(inputNode);
						}
					}
				}
				else
				{
					//create new data
					xml_node<> *inputNode = XmlDoc.allocate_node(node_element, "Input");
					inputNode->append_attribute(XmlDoc.allocate_attribute("Input", XmlDoc.allocate_string(input.c_str())));
					inputNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
					groupInputNode->append_node(inputNode);

					xml_node<> *xNode = XmlDoc.allocate_node(node_element, "X");
					xNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X).c_str())));
					xNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
					inputNode->append_node(xNode);

					xml_node<> *yNode = XmlDoc.allocate_node(node_element, "Y");
					yNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y).c_str())));
					yNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
					inputNode->append_node(yNode);

					xml_node<> *deltaXNode = XmlDoc.allocate_node(node_element, "DeltaX");
					int previousX = std::stoi(previousTimeNode->first_node("Values")->first_attribute("X")->value());
					deltaXNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X - previousX).c_str())));
					deltaXNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
					inputNode->append_node(deltaXNode);

					xml_node<> *deltaYNode = XmlDoc.allocate_node(node_element, "DeltaY");
					int previousY = std::stoi(previousTimeNode->first_node("Values")->first_attribute("Y")->value());
					deltaYNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y - previousY).c_str())));
					deltaYNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
					inputNode->append_node(deltaYNode);

					xml_node<> *rewardNode = XmlDoc.allocate_node(node_element, "Reward");
					rewardNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Reward).c_str())));
					rewardNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
					inputNode->append_node(rewardNode);
				}
			}
		}
		else
		{
			xml_node<> *groupRewardNode = XmlDoc.allocate_node(node_element, "GroupInput");
			TimeNode->append_node(groupRewardNode);

			xml_node<> *inputNode = XmlDoc.allocate_node(node_element, "Input");
			inputNode->append_attribute(XmlDoc.allocate_attribute("Input", "NULL"));
			inputNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
			groupRewardNode->append_node(inputNode);

			xml_node<> *xNode = XmlDoc.allocate_node(node_element, "X");
			xNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(X).c_str())));
			xNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
			inputNode->append_node(xNode);
			xml_node<> *yNode = XmlDoc.allocate_node(node_element, "Y");
			yNode->append_attribute(XmlDoc.allocate_attribute("Value", XmlDoc.allocate_string(std::to_string(Y).c_str())));
			yNode->append_attribute(XmlDoc.allocate_attribute("Count", "1"));
			inputNode->append_node(yNode);
		}
	}
	
} Game;

void ResetXml()
{
	XmlDoc.clear();

	xml_node<>* decl = XmlDoc.allocate_node(node_declaration);
	decl->append_attribute(XmlDoc.allocate_attribute("version", "1.0"));
	decl->append_attribute(XmlDoc.allocate_attribute("encoding", "utf-8"));
	XmlDoc.append_node(decl);

	RootNode = XmlDoc.allocate_node(node_element, "GameData");
	XmlDoc.append_node(RootNode);
}

void main()
{
	ResetXml();

	while (Run)
	{
		std::cout << ">";
		std::vector<std::string> args;
		Input(args);
		
		if (args[0] == "\\HELP")
		{
			std::cout << "Commands:\n" <<
				"\\Help\t\tDisplay help list.\n" <<
				"\\Start\t\tStart the game.\n" <<
				"\\End\t\tEnd the game.\n" <<
				"\\Save\t\tSave the current data to the File.xml.\n" <<
				"\tArguments:\n" <<
				"\tClear\tclears the content of the file before saving.\n" <<
				"\\Display\tDisplay XML data from File.xml.\n" <<
				"\\Print\t\tOutput formatted XML table to File.txt from File.xml.\n" <<
				"\\EXIT\n";
		}
		else if (args[0] == "\\START")
		{
			if (!Game.Play)
			{
				Game.Start();
			}
			else
			{
				std::cout << "Game Already In Progress. Restart? Y/N\n";
				bool proceed = false;
				do
				{
					std::cout << ">";
					Input(args);
					std::transform(args[0].begin(), args[0].end(), args[0].begin(), ::toupper);
					if (args[0] == "Y" || args[0] == "N") { proceed = true; }
					else { std::cout << "Error: Invalid Argument\n"; }
				}
				while (!proceed);
				if (args[0] == "Y") { Game.Start(); }
				else {}
			}
		}
		else if (args[0] == "\\END")
		{
			Game.Play = false;
			std::cout << "Game Ended\n";
		}
		else if (args[0] == "\\SAVE")
		{
			std::fstream xmlFile;
			if (args.size() > 1)
			{
				if (args[1] == "CLEAR")
				{
					xmlFile = std::fstream("Data.xml", std::fstream::out | std::fstream::trunc);
				}
				else
				{
					std::cout << "Error: Invalid Argument\n";
				}
			}
			else
			{
				xmlFile = std::fstream("Data.xml", std::fstream::out | std::fstream::app);
			}
			std::string xmlString;
			rapidxml::print(std::back_inserter(xmlString), XmlDoc);
			xmlFile << XmlDoc;

			xmlFile.close();
		}
		else if (args[0] == "\\DISPLAY")
		{
			FormatXmlData();
			std::cout << OutBuffer << "\n";
		}
		else if(args[0] == "\\PRINT")
		{
			FormatXmlData();
			std::fstream txtFile = std::fstream("Data.txt", std::fstream::out);
			txtFile << OutBuffer;
			txtFile.close();
		}
		else if (args[0] == "\\EXIT")
		{
			Run = false;
		}
		else if (Game.Play == true)
		{
			if (args[0] == "A" || args[0] == "B" || args[0] == "C" || args[0] == "D" || args[0] == "E")
			{
				Game.Update(args[0]);
			}
			else
			{
				std::cout << "Error: Invalid Argument\n";
			}
		}
		else
		{
			std::cout << "Error: Invalid Argument\n";
		}
	}
	
	XmlDoc.clear();

	//std::cout << "\nPress Enter To Continue:";
	//std::string out;
	//std::getline(std::cin, out);
}

void FormatXmlData()
{
	OutBuffer = "";
	std::vector<std::vector<std::vector<std::string>>> elements;
	std::vector<int> elementWidths;
	std::vector<int> elementHeights;
	std::fstream xmlFile = std::fstream("Data.xml", std::fstream::in);

	xml_document<> xmlDoc;
	xml_node<> *rootNode;
	xml_node<> *timeNode = 0;
	xml_node<> *inputNode = 0;
	xml_node<> *valuesNode = 0;
	xml_node<> *rewardNode = 0;
	xml_node<> *groupRewardNode = 0;
	xml_node<> *groupInputNode = 0;

	std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	xmlDoc.parse<0>(&buffer[0]);
	

	// Find our root node
	rootNode = xmlDoc.first_node("GameData");
	timeNode = rootNode->first_node("Time");
	if (!timeNode) { std::cout << "Error reading from file.\n"; return; }

	//init Categories
	elements.push_back({ {"#"}, { " Input", " ------" }, {"  #  "}, {" Pos", " ---"}, {"  #  "}, {" Reward", " ------"}, {"  #  "}, {" GroupReward", " ------------"}, {"  #  "}, {" GroupInput", " ----------"}, {" #"} });
	for (int x = 0; x < elements[0].size(); x++)
	{
		elementWidths.push_back((int)elements[0][x][0].size());
		for (int z = 0; z < elements[0][x].size(); z++)
		{
			elementWidths[x] = __max(elementWidths[x], (int)elements[0][x][z].size());

			if (elementHeights.size() > 0) { elementHeights[0] = __max(elementHeights[0], (int)elements[0][x].size()); }
			else { elementHeights.push_back((int)elements[0][x].size()); }
		}
	}

	int y = 1;
	do
	{
		inputNode = timeNode->first_node("Input");
		valuesNode = timeNode->first_node("Values");
		rewardNode = timeNode->first_node("Reward");
		groupRewardNode = timeNode->first_node("GroupReward");
		groupInputNode = timeNode->first_node("GroupInput");

		std::vector<std::string> groupReward;
		std::vector<std::string> groupInput;

		{/*Format GroupReward*/ }
		{
			xml_node<> *childRewardNode = groupRewardNode->first_node("Reward");
			while (childRewardNode)
			{
				groupReward.push_back(
					childRewardNode->name() +
					std::string(": ") +
					childRewardNode->first_attribute("Reward")->value() +
					std::string("(") +
					childRewardNode->first_attribute("Count")->value() +
					std::string(")")
					);

				{/*add each element to the array*/}
				{
					xml_node<> *childNode = childRewardNode->first_node();
					while (childNode)
					{
						groupReward.push_back(
							childNode->name() + 
							std::string(": ") + 
							childNode->first_attribute("Value")->value() + 
							std::string("(") +
							childNode->first_attribute("Count")->value() +
							std::string(")")
							);

						childNode = childNode->next_sibling();
					}
				}

				childRewardNode = childRewardNode->next_sibling("Reward");

				if (childRewardNode) { groupReward.push_back(""); }
			}
		}

		{/*Format GroupInput*/ }
		{
			xml_node<> *childInputNode = groupInputNode->first_node("Input");
			while (childInputNode)
			{
				groupInput.push_back(
					childInputNode->name() +
					std::string(": ") +
					childInputNode->first_attribute("Input")->value() +
					std::string("(") +
					childInputNode->first_attribute("Count")->value() +
					std::string(")")
					);

				{/*add each element to the array*/ }
				{
					xml_node<> *childNode = childInputNode->first_node();
					while (childNode)
					{
						groupInput.push_back(
							childNode->name() +
							std::string(": ") +
							childNode->first_attribute("Value")->value() +
							std::string("(") +
							childNode->first_attribute("Count")->value() +
							std::string(")")
							);

						childNode = childNode->next_sibling();
					}
				}

				childInputNode = childInputNode->next_sibling("Input");

				if (childInputNode) { groupInput.push_back(""); }
			}
		}

		elements.push_back(
		{ 
			{"# "},
			{inputNode->first_attribute("Input")->value()}, {"  #  "}, 
			{valuesNode->first_attribute("X")->value() + std::string(", ") + valuesNode->first_attribute("Y")->value()}, {"  #  "}, 
			{rewardNode->first_attribute("Reward")->value()}, {"  #  "},
			groupReward, {"  #  "},
			groupInput,
			{"#"}
		});

		//go calculate for all coloumns
		for (int x = 0; x < elements[y].size(); x++) 
		{
			//go through every z element
			for (int z = 0; z < elements[y][x].size(); z++)
			{
				elementWidths[x] = __max(elementWidths[x], (int)elements[y][x][z].size());
			}

			//calculate max hight between every coloumn
			if (elementHeights.size() > y) { elementHeights[y] = __max(elementHeights[y], (int)elements[y][x].size()); }
			else { elementHeights.push_back((int)elements[y][x].size()); }
		}

		y++;
	}
	while ((timeNode = timeNode->next_sibling("Time")) != 0);

	//draw top bar
	for (int x = 0; x < elements[0].size(); x++)
	{
		OutBuffer += std::string(elementWidths[x], '#');
	} 
	OutBuffer += "\n";
	//draw table
	for (int y = 0; y < elements.size(); y++)
	{
		for (int z = 0; z < elementHeights[y]; z++)
		{
			for (int x = 0; x < elements[y].size(); x++)
			{
				//check if it is a vertical column
				size_t pos = elements[0][x][0].find("#");
				if (pos != std::string::npos)
				{
					OutBuffer += std::string(pos, ' ');
					OutBuffer += "#";
					OutBuffer += std::string(elementWidths[x] - ((int)pos + 1), ' ');
				}
				else if ((int)elements[y][x].size() > z)
				{
					OutBuffer += elements[y][x][z];
					OutBuffer += std::string(elementWidths[x] - (int)elements[y][x][z].size(), ' ');//fill in horisontal gap
				}
				else
				{
					//z element doesn't exist

					
					//else
					//{
						//fill in empty space
						OutBuffer += std::string(elementWidths[x], ' ');
					//}
				}
			}
			OutBuffer += "\n";
		}
		//OutBuffer += "\n";
		//horisontal buffers
		for (int x = 0; x < elements[y].size(); x++)
		{
			OutBuffer += std::string(elementWidths[x], '#');
		}
		OutBuffer += "\n";
	}

	xmlFile.close();
}

