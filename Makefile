all:
	@make -C ./src/server/ all --no-print-directory
	@make -C ./src/client/ all --no-print-directory

re:
	@make -C ./src/server/ re --no-print-directory
	@make -C ./src/client/ re --no-print-directory
