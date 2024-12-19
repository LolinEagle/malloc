ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		=	libft_malloc_$(HOSTTYPE).so
HOSTLIB		=	libft_malloc.so
SRC			=	free.c malloc.c realloc.c utils.c
CC			=	gcc
RM			=	rm -rf
LN			=	ln -sf
FLAGS		=	-Wall -Werror -Wextra -fPIC
LIB			=	-L. -lft_malloc_$(HOSTTYPE)
INC			=	-Iinc
SRC_PATH	=	./src/
OBJ_PATH	=	./obj/
OBJ_DIRS	=	$(OBJ_PATH)
OBJ			=	$(addprefix $(OBJ_PATH),$(SRC:.c=.o))

all:$(NAME)

clean:
	$(RM) $(OBJ_PATH) .vscode

fclean:clean
	$(RM) *.so *.out

re:fclean
	$(MAKE) all

run:re
	$(CC) $(FLAGS) $(LIB) $(INC) $(OBJ) src/main.c
	clear
	LD_LIBRARY_PATH=. LD_PRELOAD=./$(NAME) ./a.out

$(OBJ_PATH)%.o:$(SRC_PATH)%.c | $(OBJ_DIRS)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

$(NAME):$(OBJ)
	$(CC) $(FLAGS) -shared $(LIB) $(INC) $(OBJ) -o $(NAME)
	$(LN) $(NAME) $(HOSTLIB)

.PHONY:all clean fclean re run
