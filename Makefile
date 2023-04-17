# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 13:03:55 by youngjpa          #+#    #+#              #
#    Updated: 2023/04/17 16:29:36 by yuhyeongmin      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS		=	minishell.c				\
				./parse/arg_check.c 	\
				./parse/ft_split_arg.c	\
				./parse/join_string.c	\
				./parse/parse.c 		\
				./parse/quotes_setting.c\
				./parse/tokenize_util.c		\
				./parse/tokenize.c			\
				./utilites/exit_errono.c	\
				./utilites/file_open_check.c\
				./utilites/init_and_free.c \
				./utilites/signal_handle.c \
				./utilites/systemcall1.c \
				./utilites/systemcall2.c \
				./utilites/utils1.c \
				./utilites/utils2.c \
				./utilites/utils3.c \
				./utilites/utils4.c \
				./utilites/utils5.c \
				./env/env_utils.c	\
				./env/env_utils2.c	\
				./execute/execute.c	\
				./execute/ft_valid_token.c\
				./execute/ft_exec_utils.c\
				./execute/ft_heredoc.c\
				./execute/ft_init_clear_cmd.c\
				./execute/ft_open_files.c\
				./execute/ft_path.c\
				./execute/ft_redirection.c\
				./execute/ft_temp_file.c\
				./builtins/cd_utils.c\
				./builtins/ft_cd.c\
				./builtins/ft_env.c\
				./builtins/ft_echo.c\
				./builtins/ft_exit.c\
				./builtins/ft_export_check_valid.c\
				./builtins/ft_export_no_arg_utils.c\
				./builtins/ft_export.c\
				./builtins/ft_pwd.c\
				./builtins/ft_unset.c\

OBJS		= $(SRCS:%.c=%.o)

SAN = -fsanitize=address -g3
DEBUG = -g
CC = gcc $(DEBUG) $(SAN)
CFLAGS = -Werror -Wall -Wextra
READLINE_LIB 	= -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC	= -I/opt/homebrew/opt/readline/include
# READLINE_LIB 	= -lreadline -L${HOME}/.brew/opt/readline/lib
# READLINE_INC	= -I${HOME}/.brew/opt/readline/include

FT_DIR	= ./libft
FT 	= ft

all			:	$(NAME)

$(NAME)		:	$(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(READLINE_LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean		:
		rm -f $(OBJS)

fclean		:	clean
		rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re bonus
