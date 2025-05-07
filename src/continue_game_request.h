#ifndef CONTINUE_GAME_REQUEST_H
#define CONTINUE_GAME_REQUEST_H

enum {
	key_escape = 27,
	key_yes = 121,
	key_no = 110
};

static const char continue_quest[] = "Crash! Would you like to continue the game?";

int
affirmative_answer_to_continue_game_request();

#endif
