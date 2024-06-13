#include "Player.h"
#include <fstream>
#include <iostream>

void Player::SetAnimation()
{
	for (int x = 0; x < AnimationList.size(); x++)
	{
		if (AnimationList[x].direction == Sprite->Movement.CurrentDirection && AnimationList[x].state == Sprite->Movement.CurrentState && costumeType == AnimationList[x].costumeType)
		{
			CurrentAnimation = &AnimationList[x];
			Sprite->Texture = CurrentAnimation->PlayerTextures[0];
			if (CurrentAnimation->costumeType > CostumeType::Plain)
			{
				Sprite->Costume = CurrentAnimation->CostumeTextures[0];
				CurrentAnimation->lastindex = 0;
			}
		}
	}
}

void Player::UpdateAnimation()
{
	if(Sprite->Movement.LastDirection != Sprite->Movement.CurrentDirection || Sprite->Movement.LastState != Sprite->Movement.CurrentState)
	{
		SetAnimation();
	}
	CurrentAnimation->Speed.Counter++;

	if (CurrentAnimation->Speed.Counter == CurrentAnimation->Speed.TargetUntilChange)
	{
		Sprite->Texture = CurrentAnimation->PlayerTextures[CurrentAnimation->lastindex];
		if (CurrentAnimation->costumeType > CostumeType::Plain)
		{
			Sprite->Costume = CurrentAnimation->CostumeTextures[CurrentAnimation->lastindex];
		}
		CurrentAnimation->lastindex++;
		if (CurrentAnimation->lastindex  >= CurrentAnimation->PlayerTextures.size())
		{
			CurrentAnimation->lastindex = 0;
		}
		CurrentAnimation->Speed.Counter = 0;
	}
}

void Player::UpdatePlayer()
{
	UpdateAnimation();
}

void Player::LoadAnimations(std::string FileName)
{
	std::ifstream file(FileName);
	if (file.is_open())
	{
		std::string fileText = "Assets/Player/Animations/";
		std::string line = "";
		while(std::getline(file, line))
		{
			int index = 0;
			State s;
			Direction d;
			CostumeType c;
			std::string temp = "";
			std::string txtfile = "";
			std::string State = "";
			std::string Costume = "";
			std::string Direction = "";

			for (int x = 0; x < line.size(); x++)
			{
				if (line.at(x) != '#')
				{
					temp += line.at(x);
				}
				else
				{
					if (index == 0)
					{
						txtfile = temp;
						temp = "";
					}
					else if (index == 1)
					{
						Costume = temp;
						temp = "";
					}
					else if (index == 2)
					{
						State = temp;
						temp = "";
					}
					else if (index == 3)
					{
						Direction = temp;
						temp = "";
					}
					index++;
				}
				
			}
			if (State == "idle")
			{
				s = State::Idle;
			}
			if (State == "walking")
			{
				s = State::Walking;
			}
			if (State == "running")
			{
				s = State::Running;
			}

			if (Direction == "north")
			{
				d = Direction::North;
			}
			if (Direction == "south")
			{
				d = Direction::South;
			}
			if (Direction == "west")
			{
				d = Direction::West;
			}
			if (Direction == "east")
			{
				d = Direction::East;
			}

			if (Costume == "plain")
			{
				c = CostumeType::Plain;
			}
			if (Costume == "basic")
			{
				c = CostumeType::Basic;
			}
			if (Costume == "advanced")
			{
				c = CostumeType::Advanced;
			}
			fileText += txtfile;
			Animation a = Animation(fileText, c, s, d);
			AnimationList.push_back(a);
			fileText = "Assets/Player/Animations/";
			line = "";
		}
	}
	file.close();
	std::cout << "SPRITE AND SPRITE ANIMATIONS LOADED" << std::endl;
}
//walkup.txt#plain#idle#east