#include "Player.h"
#include <fstream>
#include <iostream>

void Player::SetPlayerAnimation()
{
 	for (int x = 0; x < AnimationList.size(); x++)
	{
 		if (AnimationList[x].direction == PlayerSprite->Movement.CurrentDirection && AnimationList[x].state == PlayerSprite->Movement.CurrentState && AnimationList[x].costumeType == CostumeType::None)
		{
			PlayerAnimations.CharacterAnimation = AnimationList[x];
			PlayerSprite->Texture = PlayerAnimations.CharacterAnimation.Textures[0];
		}
	}
}
void Player::SetPlayerCostumeAnimation()
{
	if (CurrentCostume->Type == CostumeType::None)
	{
		return;
	}
	for (int x = 0; x < AnimationList.size(); x++)
	{
		if (AnimationList[x].direction == PlayerSprite->Movement.CurrentDirection && AnimationList[x].state == PlayerSprite->Movement.CurrentState && CurrentCostume->Type == AnimationList[x].costumeType)
		{
			PlayerAnimations.CostumeAnimation = AnimationList[x];
			CostumeSprite->Texture = PlayerAnimations.CostumeAnimation.Textures[0];
		}
	}
}

void Player::UpdatePlayerCharacterAnimation()
{
	if(PlayerSprite->Movement.LastDirection != PlayerSprite->Movement.CurrentDirection || PlayerSprite->Movement.LastState != PlayerSprite->Movement.CurrentState)
	{
		SetPlayerAnimation();
	}
	PlayerAnimations.CharacterAnimation.Speed.Counter++;

	if (!(PlayerAnimations.CharacterAnimation.Speed.Counter == PlayerAnimations.CharacterAnimation.Speed.TargetUntilChange))
	{
		return;
	}

	PlayerSprite->Texture = PlayerAnimations.CharacterAnimation.Textures[PlayerAnimations.CharacterAnimation.lastindex];
	PlayerAnimations.CharacterAnimation.lastindex++;

	if (PlayerAnimations.CharacterAnimation.lastindex  >= PlayerAnimations.CharacterAnimation.Textures.size())
	{
		PlayerAnimations.CharacterAnimation.lastindex = 0;
	}

	PlayerAnimations.CharacterAnimation.Speed.Counter = 0;
	
}

void Player::UpdatePlayerCostumeAnimation()
{
	if (PlayerSprite->Movement.LastDirection != PlayerSprite->Movement.CurrentDirection || PlayerSprite->Movement.LastState != PlayerSprite->Movement.CurrentState)
	{
		SetPlayerCostumeAnimation();
	}
	if (CurrentCostume == nullptr || CurrentCostume->Type == CostumeType::None)
	{
		return;
	}

	PlayerAnimations.CostumeAnimation.Speed.Counter++;

	if (!(PlayerAnimations.CostumeAnimation.Speed.Counter == PlayerAnimations.CostumeAnimation.Speed.TargetUntilChange))
	{
		return;
	}

	CostumeSprite->Texture = PlayerAnimations.CostumeAnimation.Textures[PlayerAnimations.CostumeAnimation.lastindex];
	PlayerAnimations.CostumeAnimation.lastindex++;

	if (PlayerAnimations.CostumeAnimation.lastindex >= PlayerAnimations.CostumeAnimation.Textures.size())
	{
		PlayerAnimations.CostumeAnimation.lastindex = 0;
	}

	PlayerAnimations.CostumeAnimation.Speed.Counter = 0;
	
}

void Player::UpdatePlayerAnimation()
{
	UpdatePlayerCharacterAnimation();
	UpdatePlayerCostumeAnimation();
}

void Player::UpdatePlayer()
{

	UpdatePlayerAnimation();
}

void Player::LoadAnimations(std::string FileName)
{

			std::string PlayerFile = "Assets/Sprites/Animations/PlayerAnimations/master.txt";
			std::string CostumeFile = "Assets/Sprites/Animations/CostumeAnimations/master.txt";
			std::string FileText = "Assets/Sprites/Animations/PlayerAnimations/";
			std::string line = "";

			std::ifstream playerfile(PlayerFile);
			if (playerfile.is_open())
			{

				while (std::getline(playerfile, line))
				{
					std::string FileText = "Assets/Sprites/Animations/PlayerAnimations/";
					int index = 0;
					State s;
					Direction d;
					std::string temp = "";
					std::string txtfile = "";
					std::string State = "";
					//std::string Costume = "none";
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
								State = temp;
								temp = "";
							}
							else if (index == 2)
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

					FileText += txtfile;
					Animation a = Animation(FileText, s, d);
					AnimationList.push_back(a);
					line = "";


				}
			}
			playerfile.close();
			std::ifstream costumefile(CostumeFile);
			if (costumefile.is_open())
			{
				while (std::getline(costumefile, line))
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
					std::string FileText = "Assets/Sprites/Animations/CostumeAnimations/";
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

					if (Costume == "none")
					{
						c = CostumeType::None;
					}
					if (Costume == "basic")
					{
						c = CostumeType::Basic;
					}
					if (Costume == "advanced")
					{
						c = CostumeType::Advanced;
					}

					FileText += txtfile;
					Animation a = Animation(FileText, s, d, c);
					AnimationList.push_back(a);
					line = "";
				}
			}
			costumefile.close();
	std::cout << "SPRITE AND SPRITE ANIMATIONS LOADED" << std::endl;
}
				
			


