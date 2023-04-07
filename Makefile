# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyyoo <hyyoo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 13:03:55 by youngjpa          #+#    #+#              #
#    Updated: 2023/04/07 15:49:21 by hyyoo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS		=	minishell.c				 \
				./parse/argc_checker.c 	 \
				./parse/ft_split_arg.c   \
				./parse/join_string.c    \
				./parse/parse.c 		 \
				./parse/quotes_setting.c \
				./parse/tokenize_util.c  \
				./parse/tokenize.c		 \
				./utillites/exit_errono.c \
				./utillites/file_open_check.c\
				./utillites/init_and_free.c \
				./utillites/signal_handle.c \
				./utillites/systemcall1.c \
				./utillites/systemcall2.c \
				./utillites/util1.c \
				./utillites/util2.c \
				./utillites/util3.c \
				./utillites/util4.c \
				./utillites/util5.c \

OBJS		= $(SRCS:%.c=%.o)

CC = gcc $(DEBUG)
CFLAGS = -Werror -Wall -Wextra
# SAN = -fsanitize=address -g3
DEBUG = -g
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


# int	is_whitespace(char *line);
# void	main_init(int argc, char *argv[]);
# int	main(int argc, char *argv[], char *envp[]);
# #parse
# static void	first(t_cmd_info *tmp, t_cmd_info **ptr, t_cmd_info **head);
# void	argc_checker(t_cmd_info **cmd);

# static void	*is_free(char **str, int str_index);
# static int	get_word_cnt(char const *str, char c);
# static char	**set_worddup(char const *s, char c, char **mem);
# char	**ft_split_argc(char const *s, char c, int *argc);

# char	*ft_strjoin_char(char *s1, char s2);

# static char	*parse_in_pipe(char *str, int *pipe, t_cmd_info **cmd, t_cmd_info *next);
# static char	*add_redirect_space(char *str, char *line, char c);
# static char	*parse_out_pipe(char *str, char *line, int quotes, int *pipe);
# void	parse(char *line, t_cmd_info *cmd);

# int	parse_set_quotes(char line, int quotes, t_cmd_info *cmd);
# char	*ft_strjoin_free(char *s1, char *s2);
# void	delete_argv(t_cmd_info *cmd, int *i);
# void	argv_change(t_cmd_info *cmd, char *new, int i);

# static char	*replace_while_dollar(char str, char *new, t_info_env *head, int quotes);
# static char	*replace_while_else(char c, char *new, int quotes);
# static int	dollar_check(char c);
# static char	*replace_while(t_cmd_info *cmd, t_info_env *head, int i);
# void	replace(t_cmd_info *cmd, t_info_env *head);
