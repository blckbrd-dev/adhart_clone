#pragma once

#include "events.h"

namespace adhart
{

class entity
{
public:

	int pos_x = 0;
	char symbol = 'x';

	entity();
	virtual ~entity() = 0;

	virtual void behavior(game_event&) =0;

};

}
