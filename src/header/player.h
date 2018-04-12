#pragma once

#include "entity.h"
#include "game.h"

namespace adhart
{

class player : public entity 
{

	game& _game;

public:
	player(game& game) : 
		_game {game}
	{

	}

	~player() override
	{

	}

	void behavior(game_event& event) override
	{
		switch(event)
		{
			case game_event::k_move_left:
				_game.log("move left.");
				break;
			case game_event::k_move_right:
				_game.log("move right");
				break;
			case game_event::k_skip:
				_game.log("waiting...");
				break;
			default: break;
		}
		
	}
};

}
