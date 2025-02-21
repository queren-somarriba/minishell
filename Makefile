# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 12:33:33 by qsomarri          #+#    #+#              #
#    Updated: 2025/02/18 17:19:25 by qsomarri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell 

CC = @cc

CFLAGS = -Wall -Wextra -Werror -g -I./includes 

LDFLAGS = -lreadline

RM = @rm -rf

MAKE = @make --no-print-directory -C

SRCS_DIR = srcs

BUILTIN_DIR = $(SRCS_DIR)/builtin

ERROR_MGMT_DIR = $(SRCS_DIR)/error_mgmt

MAIN_DIR = $(SRCS_DIR)/main

REDIRECTION_DIR = $(SRCS_DIR)/redirections

EXEC_DIR = $(SRCS_DIR)/exec

PARSER_DIR = $(SRCS_DIR)/parser

SRCS =	$(MAIN_DIR)/minishell.c \
	$(MAIN_DIR)/initializer.c \
	$(MAIN_DIR)/minishell_utils.c \
	$(MAIN_DIR)/list_utils.c \
	$(PARSER_DIR)/expansion.c \
	$(PARSER_DIR)/expansion_utils.c \
	$(PARSER_DIR)/parser.c \
	$(PARSER_DIR)/parser_utils.c \
	$(PARSER_DIR)/quotes.c \
	$(PARSER_DIR)/tokenizer.c \
	$(PARSER_DIR)/tokenizer_utils.c \
	$(EXEC_DIR)/exec_cmd.c \
	$(EXEC_DIR)/process.c \
	$(EXEC_DIR)/child_process.c \
	$(BUILTIN_DIR)/builtin_utils.c \
	$(BUILTIN_DIR)/env.c \
	$(BUILTIN_DIR)/env_utils.c \
	$(BUILTIN_DIR)/export.c \
	$(BUILTIN_DIR)/cd.c \
	$(BUILTIN_DIR)/pwd.c \
	$(BUILTIN_DIR)/echo.c \
	$(BUILTIN_DIR)/unset.c \
	$(BUILTIN_DIR)/exit.c \
	$(REDIRECTION_DIR)/redirections.c \
	$(REDIRECTION_DIR)/redirections_utils.c \
	$(REDIRECTION_DIR)/here_doc.c \
	$(ERROR_MGMT_DIR)/free.c \
	$(ERROR_MGMT_DIR)/outputs.c \
	$(ERROR_MGMT_DIR)/signal_handler.c \
	$(ERROR_MGMT_DIR)/check_pars_error.c \

OBJ_DIR = obj

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Cible principale
all:	$(NAME)

# Création de l'exécutable
$(NAME):	$(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft $(LDFLAGS)
		@echo "\033[0;92m * $(NAME) program file was created\033[0m *"

# Construction de la libft
$(LIBFT):
	@$(MAKE) $(LIBFT_PATH) all

# Création du répertoire des objets
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Nettoyage des fichiers objets
clean:
	@$(MAKE) $(LIBFT_PATH) clean
	@$(RM) $(OBJ_DIR)
	@echo "\033[0;91m* $(NAME) object files was deleted *\033[0m"

# Nettoyage complet
fclean:	clean
	@$(MAKE) $(LIBFT_PATH) fclean
	@$(RM) $(NAME)
	@echo "\033[0;91m* $(NAME) was deleted *\033[0m"

# Reconstruction complète
re: fclean all

.PHONY: all clean fclean re
