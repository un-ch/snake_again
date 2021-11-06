#include <time.h>		/*	for time	*/
#include <stdlib.h>		/*	for srand	*/
#include <ncurses.h>
#include "screen.h"
#include "string.h"
#include "display_message.h"
#include "end_program.h"
#include "objects.h"
#include "get_random_number.h"
#include "coordinates.h"
#include "barrier.h"
#include "target.h"
#include "snake_object.h"
#include "round_settings.h"
#include "handle_direction.h"
#include "continue_game_request.h"

enum { exit_success_code = 0 };
enum { max_snake_length = 5 };
enum { max_round_num = 5 };

int main()
{
	srand(time(NULL));
	initscr();
	/* enable ctrl-c, ctrl-d: */
	cbreak();
	/* enable escape-sequences: */
	keypad(stdscr, 1);
	/* disable automatic input symbols on the screen: */
	noecho();
	curs_set(0);

	struct coordinates_deque snake;
	struct coordinates_list *target, *barrier;
	struct coordinates crd;
	struct round_settings rnd_stt;
	int direction_signal;

	display_message_center(greeting_message);
	set_settings_initial_round(&rnd_stt);
	timeout(rnd_stt.snake_speed);
	set_objects_another_round(&snake,
								&target,
								&barrier,
								rnd_stt,
								&crd);

	while((direction_signal = getch()) != key_escape) {
		handle_direction_signal(direction_signal,
											&crd,
											&snake);
		display_target(target);
		display_barrier(barrier);
		/*
		display_target_in_fog_of_war(snake.first->coord, target);
		display_barrier_in_fog_of_war(snake.first->coord, barrier);
		*/
		if(is_contact_with_borders(snake.first->coord) ||
			(is_contact_with_barrier(snake.first->coord, barrier))) {
			display_message_center("crash!");
			game_settings_decrease(&rnd_stt);
			if(rnd_stt.round_num < 1) {
				if(affirmative_answer_to_continue_game_request()) {
					set_settings_initial_round(&rnd_stt);
					set_objects_another_round(&snake,
												&target,
												&barrier,
												rnd_stt,
												&crd);
					continue;
				} else {
					end_program_crash_end();
				}
			}
			set_objects_another_round(&snake,
										&target,
										&barrier,
										rnd_stt,
										&crd);
		}
		if(is_contact_with_target(snake.first->coord, target)) {
			update_after_contact_with_target(&rnd_stt,
												&snake,
												snake.first->coord);
			if(rnd_stt.current_snake_length > max_snake_length) {
				game_settings_increase(&rnd_stt);
				if(rnd_stt.round_num > max_round_num) {
					end_program_win();
				}
				set_objects_another_round(&snake,
											&target,
											&barrier,
											rnd_stt,
											&crd);
			}
		}
	}
	clear_screen();

	/* restore terminal after ncurses activity: */
	endwin();

	return exit_success_code;
}
