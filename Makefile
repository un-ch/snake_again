default:
	@cd src && $(MAKE) --no-print-directory

all:	@default

clean:
	@cd src && $(MAKE) clean --no-print-directory

run:
	@./src/snake_again
