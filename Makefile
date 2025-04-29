default:
	@cd src && $(MAKE) --no-print-directory

all:	default

clean:
	@cd src && $(MAKE) clean --no-print-directory

run:	all
	@./src/snake_again

.PHONY: default all clean run
