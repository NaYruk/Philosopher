GREEN = \033[32m
CYAN = \033[36m
YELLOW = \033[33m
RESET = \033[0m

CC = cc 
INCLUDES = -I./mandatory/includes
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES)

SRC_PATH = ./mandatory/sources
SRC = $(SRC_PATH)/errors.c $(SRC_PATH)/main.c $(SRC_PATH)/parsing.c $(SRC_PATH)/init.c

OBJ_PATH = ./mandatory/tmp
OBJ = $(OBJ_PATH)/errors.o $(OBJ_PATH)/main.o $(OBJ_PATH)/parsing.o $(OBJ_PATH)/init.o
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