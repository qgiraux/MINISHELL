# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 15:40:17 by qgiraux           #+#    #+#              #
#    Updated: 2024/01/18 15:47:49 by qgiraux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CC		= gcc
FLAG	= -Wall -Wextra -Werror -g3
SRCDIR	= src
OBJDIR	= obj
SRC		= $(wildcard $(SRCDIR)/*.c)
OBJ		= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

# Default target
all: $(NAME)

# Rule to build the pipex executable
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(FLAG) -o $(NAME)

# Rule to build object files for pipex
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(FLAG) -c $< -o $@


# Create the obj directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean rule to remove object files
clean:
	@rm -f $(OBJ)

# Full clean rule to remove object files and executables
fclean: clean
	@rm -f $(NAME)

# Rule to perform a clean build
re: fclean all

.PHONY: all clean fclean re bonus
