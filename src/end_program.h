#ifndef END_PROGRAM_H_SENTRY
#define END_PROGRAM_H_SENTRY

enum {
	exit_success = 0,
	exit_failure = 1
};

enum end_type {
	quit, win, malloc_err
};

void
end(enum end_type how);

#endif
