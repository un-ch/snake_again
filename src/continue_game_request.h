#ifndef CONTINUE_GAME_REQUEST_H_SENTRY
#define CONTINUE_GAME_REQUEST_H_SENTRY

enum { key_escape = 27 };
enum { key_yes = 121 };
enum { key_no = 110 };

static const char question_on_game_continue[] = \
					"would you like to continue the game?";

int
affirmative_answer_to_continue_game_request();

#endif
