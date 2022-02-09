#ifndef END_PROGRAM_H_SENTRY
#define END_PROGRAM_H_SENTRY

enum { exit_success_code = 0 };

enum end_type {
	quit	= 1,
	win		= 2
};

void
end(int end_type);

#endif
