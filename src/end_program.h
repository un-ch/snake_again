#ifndef END_PROGRAM_H
#define END_PROGRAM_H

enum {
	exit_success = 0,
	exit_failure = 1
};

enum end_type {
	quit, win, malloc_err, monochrome_display
};

void
end(enum end_type how);

#endif
