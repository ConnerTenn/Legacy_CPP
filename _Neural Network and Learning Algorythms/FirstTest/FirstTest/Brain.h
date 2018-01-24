
#pragma once

#include <vector>
#include <string>




struct Frame
{
	std::string Act;
	std::vector<double> In;
	double Reward;
	int age;
};


class Brain
{
public:
	std::vector<std::string> PossibleActions;

	std::string CurrentAction;
	std::vector<double> CurrentInputList;
	double CurrentReward;

	std::vector<Frame> FrameList;

	Brain()
	{
		srand(0);
	}

	void Update()
	{
		FrameList.push_back({ CurrentAction, CurrentInputList, CurrentReward, 0 });

		{/*Data Mining*/}
		{

		}

		CurrentAction = PossibleActions[rand() % (int)PossibleActions.size()];
	}
};