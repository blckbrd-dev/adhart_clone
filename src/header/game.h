#pragma once

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

#include "events.h"
#include "level.h"

namespace adhart
{
	class game
	{
	private:
		level* _level = nullptr;
		
		// windows
		WINDOW* _win		= nullptr;
		WINDOW* _win_lvl	= nullptr;
		WINDOW* _win_ui		= nullptr;
		WINDOW* _win_log	= nullptr;

		uint16_t _win_widht = 0;
		uint16_t _win_height = 0;

	public:

		game_event event = game_event::none;

		game(uint16_t width, uint16_t height, 
				uint16_t x, uint16_t y)

		{
			// main window
			initscr();
			cbreak();
			keypad(stdscr, TRUE);
			noecho();
			curs_set(0);

			// let width be max width always
			//_win = newwin(height, width, y, x);
			int max_x = 0, max_y = 0;
			getmaxyx(stdscr, max_y, max_x);

			_win_widht = max_x - 2*x;
			_win_height = height;


			_win = newwin(_win_height, _win_widht, y, x);
			refresh();

			box(_win, 0, 0);
			wmove(_win, 0, 5);
			wprintw(_win, " Adhart ");

			wrefresh(_win);

			// game window
			uint16_t lvl_offs_x = 10;
			uint16_t lvl_offs_y = 4;
			_win_lvl = newwin(_win_height - lvl_offs_y - 6, _win_widht * 0.5f,
					lvl_offs_y, lvl_offs_x);

			box(_win_lvl, 0, 0);
			wmove(_win_lvl, 0, 5);
			wprintw(_win_lvl, " GAME ");

			wrefresh(_win_lvl);

			/* WIN LOG */
			_win_log = newwin(_win_height - lvl_offs_y - 20, _win_widht * 0.5f,
					_win_height - lvl_offs_y - 14 + lvl_offs_y + 8, lvl_offs_x);

			/* WIN UI */
			uint16_t ui_offs_x = _win_widht * 0.5f + lvl_offs_x;
			uint16_t ui_offs_y = 4;

			_win_ui = newwin(_win_height - ui_offs_y, _win_widht * 0.4f,
					ui_offs_y, ui_offs_x);
			box(_win_ui, 0, 0);
			wmove(_win_ui, 0, 5);
			wprintw(_win_ui, " UI ");
			wrefresh(_win_ui);


		}

		~game()
		{
			delete _level;

			// clear main window
			endwin();
		}


		void run()
		{
			/* init level */
			_level = new level(_win_lvl, this);
			log("level initialized.");
			log("game started.");

			while(true)
			{
				_level->render();
				render_ui();

				// events
				int ch = getch();
				if(ch == KEY_LEFT)
				{
					event = game_event::k_move_left;
				} 
				else if(ch == KEY_RIGHT)
				{
					event = game_event::k_move_right;
				}
				else if(ch == ' ')
				{
					event = game_event::k_skip;
				}
			}
		}
	
		void log(std::string str)
		{
			werase(_win_log);
			box(_win_log, 0, 0);
			wmove(_win_log, 0, 5);
			wprintw(_win_log, " LOG ");

			// print last log
			wmove(_win_log, 2, 2);
			wprintw(_win_log, last_log.c_str());

			wmove(_win_log, 3, 2);
			wprintw(_win_log, str.c_str());
			wrefresh(_win_log);

			last_log = str;
		}

	private:
		std::string last_log;

		void render_ui()
		{
			wmove(_win_ui, 2, 4);
			wprintw(_win_ui, "Use <-. -> to move.");

			// print stats
			wmove(_win_ui, 4, 4);
			wprintw(_win_ui, "Health 100");
			wmove(_win_ui, 5, 4);
			wprintw(_win_ui, "Armour 100");

			wrefresh(_win_ui);
		}
	};
}
