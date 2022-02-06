all:
	@make -C ./src/server/ all --no-print-directory
	@make -C ./src/client/ all --no-print-directory
