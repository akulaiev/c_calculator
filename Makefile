
SRC =		main.c\
			my_stack.c\
			ft_itoa.c\
			transform_to_rpn.c\
			solve_rpn.c
SRC_DIR =	./src/
OBJ_DIR =	./obj/
OBJ = 		$(addprefix $(OBJ_DIR),$(SRC:.c=.o))
INC =		./includes/calculator.h
NAME =		calculator
Chipmunk =	./Chipmunk2D/libchipmunk.a
CFLAG =		-g -Werror -Wextra -Wall
CC =		clang

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	@$(CC) $(CFLAG) -I./includes -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAG) -o $(NAME) $(OBJ)
		
$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

exe:
	./$(NAME) "-1 + 3 + 3"

re: $(REMAKE) fclean all

commit:
		make fclean
		git add -A
		git commit -m "$(MSG)"
		git push

vpath %.cpp $(SRC_DIR)