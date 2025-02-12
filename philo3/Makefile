GREEN = \033[32m
CYAN = \033[36m
YELLOW = \033[33m
RESET = \033[0m

CC = cc 
INCLUDES = -I./mandatory/includes
CFLAGS = -Wall -Wextra -Werror -g3 $(INCLUDES)

SRC_PATH = ./mandatory/sources
SRC = $(SRC_PATH)/main.c $(SRC_PATH)/utils.c $(SRC_PATH)/check_args.c $(SRC_PATH)/init_all.c $(SRC_PATH)/free_functions.c $(SRC_PATH)/create_thread.c

OBJ_PATH = ./mandatory/tmp
OBJ = $(OBJ_PATH)/main.o $(OBJ_PATH)/utils.o $(OBJ_PATH)/check_args.o $(OBJ_PATH)/init_all.o $(OBJ_PATH)/free_functions.o $(OBJ_PATH)/create_thread.o
NAME = philo

all: $(NAME)

$(NAME): display_starting_msg $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo "\n$(GREEN)Compilation of Philosophers project is complete.$(RESET)\n"

display_starting_msg:
	@echo "\n$(CYAN)Starting compilation...$(RESET)\n"

clean: 
	   @echo "Cleaning $(YELLOW)Philosophers$(RESET) object files..."
	   @rm -rf $(OBJ_PATH)
	   @echo "Cleaning $(YELLOW)Philosophers$(RESET) object files is FINISH"

fclean: 
		@echo "\n$(GREEN)Cleaning all...\n$(RESET)"
		@echo "Cleaning $(YELLOW)Philosophers$(RESET) object files..."
	    @rm -rf $(OBJ_PATH)
	    @echo "Cleaning $(YELLOW)Philosophers$(RESET) object files is FINISH"
		@rm -rf $(NAME)
		@echo "Cleaning $(YELLOW)Executable$(RESET) file..."
		@echo "Cleaning $(YELLOW)Executable$(RESET) file is FINISH"


re: fclean all

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
		@mkdir -p $(OBJ_PATH)
		@echo "Compiling $<"
		@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re