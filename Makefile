# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 11:51:58 by qgiraux           #+#    #+#              #
#    Updated: 2024/03/29 12:24:51 by jerperez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 #-pthread -fsanitize=thread 
SRCDIR		= src
OBJDIR		= obj
LIBFT_DIR	= ./Libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBS		= -lreadline $(LIBFT)
INCLUDES	= -I./Libft -I./includes

SUP_FILE = readline.sup
define SUP_CONTENT
{
   sup1
   Memcheck:Leak
   match-leak-kinds: reachable
   ...
   obj:*/libreadline.so.*
}
{
   sup2
   Memcheck:Leak
   match-leak-kinds: reachable
   ...
   fun:readline
}
endef

TEST_FILE = test.sh
define TEST_CONTENT
echo
echo ""
echo "ok"
echo "ok" "lol" ""
echo -n ""
echo -n "ok"
echo -n "ok" "lol" ""
echo
echo lolz > tmp
cat tmp
<tmp echo
echo lolz >> tmp
cat tmp

pwd
pwd ""
pwd ok
pwd ok banane
pwd lolz > tmp
cat tmp
<tmp pwd
pwd lolz >> tmp
cat tmp
rm tmp

patate
patate ""
patate grosse
patate grosse et fraiche et ""
patate lolz > tmp
cat tmp
ls tmp
<tmp patate
patate lolz >> tmp
cat tmp

/usr/bin/ls
/usr/bin/ls main.c
/usr/bin/ls virus_win64.exe
./virus_win64.exe
/usr/bin/ls uh-oh

echo *
echo *.c
echo **.c
echo *.c*
echo .c*
echo .*
echo \*
echo "*"
echo '*'

echo $$?
patate fraiche
echo $$?
true && echo $$? 
false || echo $$?
true && echo $$? || patate || echo $$? && echo $$?
((true && echo $$?) || (patate && patate grosse et delicieuse)) && echo $$?
true
echo $$? | echo $$?
echo $$? | false | echo $$?
false
echo $$? | echo $$?

./minishell
exit 0
./minishell
./minishell
exit 1
exit 2
./minishell
./minishell
./minishell
exit 255
exit 3
exit 42

echo "I survived until the End"
endef

# <<ok cat
# this
# is
# ok

define NEWLINE


endef

SRCS_BLTIN =	bltin_echo.c\
				bltin_pwd.c\
				bltin_export_utils.c\
				bltin_export.c\
				bltin_cd.c\
				bltin_env.c\
				bltin_unset.c\
				bltin_exit.c\

SRCS_DATA =		data_destroy.c\
				data_env.c\
				data_exit_pipe.c\
				data_exit_shell.c\
				data_files.c\
				data_ini.c\
				data_list.c\
				data_operator.c\
				data_redir.c\

SRCS_DLIST =	dlist_free.c\
				dlist_istype_parse.c\
				dlist_istype_token.c\
				dlist_malloc.c\
				dlist.c\

SRCS_ENV =		env.c\

SRCS_ERROR =	error.c\

SRCS_EXEC =		exec_bin.c\
				exec_builtin.c\
				exec_cmd.c\
				exec_dlist.c\
				exec_error.c\
				exec_file.c\
				exec_free.c\

SRCS_EXP =		exp_escape.c\
				exp_filename_list.c\
				exp_filename_wild.c\
				exp_filename.c\
				exp_parameter_quote.c\
				exp_parameter_replace.c\
				exp_parameter_var.c\
				exp_parameter_escape.c\
				exp_parameter.c\
				exp.c\

SRCS_FPRINTF =	fprintf_d.c\
				fprintf.c\

SRCS_HERE =		here_read.c\
				here_tostr.c\
				here.c\

SRCS_QUENTIN =	interpreter.c\

SRCS_NODE =		node_compound.c\
				node_list.c\
				node_pipe_utils.c\
				node_pipe.c\
				node.c\


SRCS_PARSER =	parser_cmd.c\
				parser_compound.c\
				parser_error_msg.c\
				parser_error.c\
				parser_here.c\
				parser_list.c\
				parser_pipelines.c\

SRCS_READLINE =	readline.c\

SRCS_REDIR =	redir_dup.c\
				redir_error.c\
				redir_file.c\
				redir_save.c\

SRCS_SIGNAL =	sig.c\

SRCS_TOKEN =	token_utils.c\
				token.c\

SRCS = 	$(SRCS_BLTIN)\
		$(SRCS_DATA)\
		$(SRCS_BLTIN)\
		$(SRCS_DLIST)\
		$(SRCS_ENV)\
		$(SRCS_ERROR)\
		$(SRCS_EXEC)\
		$(SRCS_EXP)\
		$(SRCS_FPRINTF)\
		$(SRCS_HERE)\
		$(SRCS_QUENTIN)\
		$(SRCS_NODE)\
		$(SRCS_PARSER)\
		$(SRCS_REDIR)\
		$(SRCS_READLINE)\
		$(SRCS_TOKEN)\
		$(SRCS_SIGNAL)\

# SRCS = 	main.c\
# 		$(SRCS_BLTIN)\
# 		$(SRCS_DATA)\
# 		$(SRCS_BLTIN)\
# 		$(SRCS_DLIST)\
# 		$(SRCS_ENV)\
# 		$(SRCS_ERROR)\
# 		$(SRCS_EXEC)\
# 		$(SRCS_EXP)\
# 		$(SRCS_FPRINTF)\
# 		$(SRCS_HERE)\
# 		$(SRCS_QUENTIN)\
# 		$(SRCS_NODE)\
# 		$(SRCS_PARSER)\
# 		$(SRCS_REDIR)\
# 		$(SRCS_READLINE)\
# 		$(SRCS_TOKEN)\
# 		$(SRCS_SIGNAL)\

SRC		=	$(addprefix $(SRCDIR)/, $(SRCS))

OBJS	= 	$(SRCS:.c=.o)
#OBJ		= 	$(addprefix $(OBJDIR)/, $(OBJS))
OBJ		= 	$(OBJDIR)/main.o $(addprefix $(OBJDIR)/, $(OBJS))

###############################################

_COLOR_END=\033[0m
_COLOR_BOLD=\033[1m
_COLOR_RED=\033[31m
_COLOR_GREEN=\033[32m
_COLOR_YELLOW=\033[33m

###############################################

# Default target
all: $(LIBFT) $(NAME)

# Rule to build the executable
$(NAME): $(OBJ)
	@echo "$(_COLOR_YELLOW)Linking $<$(_COLOR_END)"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "$(_COLOR_GREEN)Ready to use $(_COLOR_BOLD)$@ !$(_COLOR_END)"

# Rule to build object files
./$(OBJDIR)/%.o: ./$(SRCDIR)/%.c
	@mkdir -p $(@D)
	@echo Compiling: $<
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

./$(OBJDIR)/%.o: ./%.c
	@mkdir -p $(@D)
	@echo Compiling: $<
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT) :
	@echo "Making $(_COLOR_BOLD)$(LIBFT)$(_COLOR_END)"
	@make all -sC $(LIBFT_DIR)
	@echo "$(_COLOR_GREEN)Ready to use $(_COLOR_BOLD)$@ !$(_COLOR_END)"

# Create the obj directory if it doesn't exist
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Clean rule to remove object files and directory, plus libft
clean:
	@rm -rf $(OBJDIR)
	@echo "$(_COLOR_YELLOW)Removed $(_COLOR_BOLD)$(OBJDIR)$(_COLOR_END)"
	@make fclean -sC $(LIBFT_DIR)
	@echo "$(_COLOR_YELLOW)Cleaned $(_COLOR_BOLD)$(LIBFT_DIR)$(_COLOR_END)"

# Full clean rule to remove object files and executables
fclean: clean
	@rm -f $(NAME)
	@echo "$(_COLOR_YELLOW)Removed $(_COLOR_BOLD)$(NAME)$(_COLOR_END)"

# Rule to perform a clean build
re: fclean all

$(SUP_FILE):
	@echo '$(subst $(NEWLINE),\n,${SUP_CONTENT})' > $(SUP_FILE)
#@printf '%s\n' $(subst $(NEWLINE),,${SUP_CONTENT}) > $(SUP_FILE)

v: all $(SUP_FILE)
	valgrind -q --trace-children=yes --track-fds=yes --suppressions=$(SUP_FILE) ./$(NAME) || (exit 0)
	rm $(SUP_FILE)
#valgrind --leak-check=full -q --trace-children=yes --track-fds=yes --show-leak-kinds=all --suppressions=$(SUP_FILE) ./$(NAME)
	
	

test_debug: CFLAGS += -D MS_DEBUG_DISABLE_TTYCHECK=1
test_debug: re

test: test_debug
	@echo '$(subst $(NEWLINE),\n,${TEST_CONTENT})' > $(TEST_FILE)
	@echo exit "" >> $(TEST_FILE)
	@touch 1_bash 1_mini 2_bash 2_mini
	@echo "$(_COLOR_YELLOW)Running tests from $(_COLOR_BOLD)$(TEST_FILE)$(_COLOR_END)"
	@<$(TEST_FILE) ./$(NAME) 1>1_mini 2>2_mini
	@sed -rzi 's/minishell> [^\n]*\n//g' 1_mini
	@<$(TEST_FILE) bash 1>1_bash 2>2_bash
	@sed -rzi 's/minishell> [^\n]*\n//g' 1_bash
	@if [ -z "$(diff 1_bash 1_mini)" ]; then rm 1_bash 1_mini; else echo "$(_COLOR_RED)Bad stdout, see $(_COLOR_BOLD)1_bash 1_mini !$(_COLOR_END)"; fi
	@if [ $(cat 2_bash | wc -l) -eq $(cat 2_mini | wc -l) ]; then rm 2_bash 2_mini; else echo "$(_COLOR_RED)Bad stderr, see $(_COLOR_BOLD)2_bash 2_mini !$(_COLOR_END)"; fi
	@if [ -f 1_mini ] || [ -f 2_mini ]; then echo "$(_COLOR_YELLOW)Trace:$(_COLOR_END)" && <$(TEST_FILE) ./$(NAME); else rm $(TEST_FILE) && echo "$(_COLOR_GREEN)Tests OK!$(_COLOR_END)"; fi

.PHONY: all clean fclean re

