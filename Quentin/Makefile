# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/19 12:12:56 by qgiraux           #+#    #+#              #
#    Updated: 2024/02/23 11:34:49 by qgiraux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= gcc
FLAG		= -Wall -Wextra -Werror -lreadline -g3
SRCDIR		= src
OBJDIR		= obj
SRC			= $(wildcard $(SRCDIR)/*.c)
OBJ			= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

# Default target
all: $(NAME)

# Rule to build the pipex executable
$(NAME): $(OBJ) libft
	$(CC) $(OBJ) $(FLAG) ./Libft/libft.a -o $(NAME)

	
# Rule to build object files for pipex
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) libft
	@$(CC) $(FLAG) -c $< -o $@

libft :
	@make all -sC ./Libft/

# Create the obj directory if it doesn't exist
$(OBJDIR):
	@mkdir -p $(OBJDIR)


# Clean rule to remove object files
clean:
	rm -f $(OBJDIR)/*.o
	make fclean -sC ./Libft/

# Full clean rule to remove object files and executables
fclean: clean
	make clean
	rm $(NAME)
	make fclean -sC ./Libft/



# Rule to perform a clean build
re: fclean all

.PHONY: all clean fclean re

