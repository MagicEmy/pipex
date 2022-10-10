NAME	:=	pipex
INC		:=	-I includes
HEADERS	:=	includes/pipex.h
SRC		:=	main.c \
			split.c \
			split_assist.c \
			access_exec.c \
			piping.c \
			execution.c
B_SRC	:=	main_bonus.c \
			split_bonus.c \
			split_assist_bonus.c \
			access_exec_bonus.c \
			piping_bonus.c \
			execution_bonus.c
OBJ		:= $(SRC:%.c=obj/%.o)
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -g -fsanitize=address

ifdef BONUS
	OBJ = $(B_SRC:%.c=b_obj/%.o)
endif

all:	$(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) ${OBJ} $(INC) -o $(NAME)

bonus:	
	@make BONUS=1

obj/%.o: src/%.c
	@mkdir -p obj
	@$(CC) $(INC) $(CFLAGS) -o $@ -c $<

b_obj/%.o: b_src/%.c
	@mkdir -p b_obj
	@$(CC) $(INC) $(CFLAGS) -o $@ -c $<
	
clean:
	@rm -f $(OBJ) 
	@rm -f ${B_OBJ}
	@rm -rf obj 
	@rm -rf b_obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
