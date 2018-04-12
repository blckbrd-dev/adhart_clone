#pragma once

#include <string>
#include <vector>

#include <curses.h>
#include "player.h"

namespace adhart
{

	/*
	 * Class should receieve a window 
	 * to use.
	 */
	class level
	{
		friend class game;

	private:
		static const char WALL		= '#';
		static const char PATH		= '.';
		static const char HOLE		= '_';

		static const uint8_t WIDTH = 32;
		static const uint8_t HEIGHT = 3;

		char** _map[HEIGHT][WIDTH];
		uint16_t _width, _height, _offset_x, _offset_y;
		WINDOW* const _win;

		std::vector<entity*> entities;
		game* _game;

		level(WINDOW* const win, game* __game) :
			_win { win },
			_game { __game }
		{

			_offset_y = 3;
			_offset_x = 5;

		}

		~level()
		{
			for(auto e : entities)
			{
				delete e;
			}
		}

		void init()
		{
		}

		void render()
		{
			wmove(_win, _offset_y, _offset_x);
			for(uint8_t i=0; i<HEIGHT; i++)
			{
				wmove(_win, _offset_y + i, _offset_x);

				for(uint8_t j=0; j<WIDTH; j++)
				{
					// generate top wall and bottom wall
					if(i == 0 || i == 2)
					{
						wprintw(_win, "%c", WALL);
					}

					// generate pathway
					if(i == 1)
					{
						wprintw(_win, "%c", PATH);
					}
				}	
			}

			wrefresh(_win);

			wmove(_win, _offset_y + 1, _offset_x);
			for(auto& e : entities)
			{
				e->behavior(_game->event);
				wmove(_win, _offset_y + 1, _offset_x + e->pos_x);
				wprintw(_win, "%c", e->symbol);
			}
		}

	};

}
