NAME = server

# Paths

SRC_PATH = ./
LIB_PATH = ../../lib/
OBJ_PATH = obj/
OUT_PATH = ../../$(NAME)

# Names

SRC_NAME =	main.c \
			helper.c \
			../signals.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

# Files

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

# Flags

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = $(LIB_PATH)libft/libft.a -I$(LIB_PATH)/libft

UNAME=$(shell uname)

all: $(NAME)

PRE:
	@make -C $(LIB_PATH)/libft/ --no-print-directory

$(NAME): PRE $(OBJ)
	@$(CC) -g $(CFLAGS) $(OBJ) $(LIBFT) -o $(OUT_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I$(LIB_PATH)/libft -g -I/usr/include -I$(SRC_PATH) -o $@ -c $<

clean:
	@make clean -C $(LIB_PATH)libft/ --no-print-directory
	@echo "Delete fdf/$(OBJ_PATH)"
	@rm -rf $(OBJ_PATH) db

fclean:	clean
	@make fclean -C $(LIB_PATH)libft/ --no-print-directory
	@echo "Delete fdf/$(NAME)"
	@rm -f $(OUT_PATH) db

db: $(SRC)
	$(CC) $(CFLAGS) -g $(SRC) $(LIBFT) -o $@
	gdb $@

re:	fclean all

.PHONY: all clean fclean re libft db
