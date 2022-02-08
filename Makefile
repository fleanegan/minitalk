all:
	@make -C ./src/server/ all --no-print-directory
	@make -C ./src/client/ all --no-print-directory

re:
	@make -C ./src/server/ re --no-print-directory
	@make -C ./src/client/ re --no-print-directory

clean:
	@make -C ./src/server/ clean --no-print-directory
	@make -C ./src/client/ clean --no-print-directory

fclean:
	@make -C ./src/server/ fclean --no-print-directory
	@make -C ./src/client/ fclean --no-print-directory
