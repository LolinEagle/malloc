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

# Debug
TIME		=	/usr/bin/time -v
GREP		=	2>&1 | grep -E "Minor|Major"

all:$(NAME)

clean:
	$(RM) $(OBJ_PATH) .vscode

fclean:clean
	$(RM) *.so *.out

re:fclean
	$(MAKE) all

run:re
	$(CC) $(FLAGS) $(LIB) $(INC) $(OBJ) test/main.c
	clear
	./run_linux.sh $(TIME) ./a.out

test:re
	$(CC) -o test0 test/test0.c
	$(CC) -o test1 test/test1.c
	$(CC) -o test2 test/test2.c
	clear
	@echo Test 0 :
	@$(TIME) ./test0 $(GREP)
	@./run_linux.sh $(TIME) ./test0 $(GREP)
	@echo Test 1 :
	@$(TIME) ./test1 $(GREP)
	@./run_linux.sh $(TIME) ./test1 $(GREP)
	@echo Test 2 :
	@$(TIME) ./test2 $(GREP)
	@./run_linux.sh $(TIME) ./test2 $(GREP)
	@echo Test 3 :
	@$(CC) -o test3 test/test3.c -L. -lft_malloc && ./run_linux.sh ./test3
	@echo Test 4 :
	@$(CC) -o test4 test/test4.c -L. -lft_malloc && ./run_linux.sh ./test4
	@echo Test 5 :
	@$(CC) -o test5 test/test5.c -L. -lft_malloc && ./run_linux.sh ./test5
	@$(RM) test0 test1 test2 test3 test4 test5


$(OBJ_PATH)%.o:$(SRC_PATH)%.c | $(OBJ_DIRS)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

$(NAME):$(OBJ)
	$(CC) $(FLAGS) -shared $(LIB) $(INC) $(OBJ) -o $(NAME)
	$(LN) $(NAME) $(HOSTLIB)

.PHONY:all clean fclean re run
