# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angerard <angerard@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 11:54:53 by angerard          #+#    #+#              #
#    Updated: 2024/12/04 16:04:08 by angerard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############################################

GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NC = \033[0m
Magenta = \033[0;35m
CYAN = \033[0;36m
GRAY = \033[0;90m
RED = \033[0;31m
SPINNERS = "🔄 🔁 ↩️ ↪️ 🔄 🔁"

#############################################

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes

SRC_DIR = src

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/args_checker.c $(SRC_DIR)/data_init.c $(SRC_DIR)/routine.c $(SRC_DIR)/monitoring.c  $(SRC_DIR)/threads.c $(SRC_DIR)/utils.c

OBJ_DIR = .cache

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#############################################

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(Magenta)"
	@echo "																								  		"
	@echo " ██▓███   ██░ ██  ██▓ ██▓     ▒█████    ██████  ▒█████   ██▓███   ██░ ██ ▓█████  ██▀███    ██████    "
	@echo " ▓██░  ██▒▓██░ ██▒▓██▒▓██▒    ▒██▒  ██▒▒██    ▒ ▒██▒  ██▒▓██░  ██▒▓██░ ██▒▓█   ▀ ▓██ ▒ ██▒▒██    ▒   "
	@echo " ▓██░ ██▓▒▒██▀▀██░▒██▒▒██░    ▒██░  ██▒░ ▓██▄   ▒██░  ██▒▓██░ ██▓▒▒██▀▀██░▒███   ▓██ ░▄█ ▒░ ▓██▄     "
	@echo " ▒██▄█▓▒ ▒░▓█ ░██ ░██░▒██░    ▒██   ██░  ▒   ██▒▒██   ██░▒██▄█▓▒ ▒░▓█ ░██ ▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒  "
	@echo " ▒██▒ ░  ░░▓█▒░██▓░██░░██████▒░ ████▓▒░▒██████▒▒░ ████▓▒░▒██▒ ░  ░░▓█▒░██▓░▒████▒░██▓ ▒██▒▒██████▒▒  "
	@echo " ▒▓▒░ ░  ░ ▒ ░░▒░▒░▓  ░ ▒░▓  ░░ ▒░▒░▒░ ▒ ▒▓▒ ▒ ░░ ▒░▒░▒░ ▒▓▒░ ░  ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░  "
	@echo " ░▒ ░      ▒ ░▒░ ░ ▒ ░░ ░ ▒  ░  ░ ▒ ▒░ ░ ░▒  ░ ░  ░ ▒ ▒░ ░▒ ░      ▒ ░▒░ ░ ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░  "
	@echo " ░░        ░  ░░ ░ ▒ ░  ░ ░   ░ ░ ░ ▒  ░  ░  ░  ░ ░ ░ ▒  ░░        ░  ░░ ░   ░     ░░   ░ ░  ░  ░    "
	@echo "           ░  ░  ░ ░      ░  ░    ░ ░        ░      ░ ░            ░  ░  ░   ░  ░   ░           ░    "
	@echo "                                                                                                     "
	@total=$(words $(OBJ)); \
	count=0; \
	for file in $(OBJ); do \
		count=$$((count + 1)); \
		percentage=$$((count * 100 / total)); \
		progress=$$((percentage / 2)); \
		spinner=$$(echo $(SPINNERS) | cut -d ' ' -f $$(($$count % 6 + 1))); \
		bar=""; \
		for i in $$(seq 1 $$progress); do bar="$${bar}█"; done; \
		for i in $$(seq $$progress 49); do bar="$${bar}░"; done; \
		if [ $$percentage -eq 100 ]; then \
			bar="███████████████████████████████████████████████████"; \
		fi; \
		printf "\r$(YELLOW)Compiling : $${bar} %d%% $${spinner}" $$percentage; \
		sleep 0.01; \
	done; \
	printf "\n"; \
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I./includes; \
	echo "$(GREEN)Program $(NAME) ready!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@ -I./includes
	@echo "$(GREEN)Compilation successful!$(NC)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(YELLOW)Cleaning project...$(Magenta)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Clean successful!$(NC)"

fclean: clean
	@echo "$(YELLOW)Full clean of project...$(Magenta)"
	@rm -f $(NAME) *.o
	@echo "$(GREEN)fclean successful!$(NC)"

re: fclean all

.PHONY: all fclean clean re
