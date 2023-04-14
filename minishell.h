/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:07:34 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/14 20:54:58 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <term.h>
# include <signal.h>
# include <sys/errno.h>
# include <sys/_types.h>
# include <readline/history.h>
# include <readline/readline.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	4096
# endif

# define READ 0
# define WRITE 1
# define REDIR_L -60
# define REDIR_R -62

# define SHE 0
# define DFL 1
# define IGN 2

int	g_exit_signal_code;

typedef struct s_cmd_info
{
	char				**cmd_and_av;
	int					ac;
	bool				ft_pipe_flag;
	bool				ft_dollar_flag;
	int					fd[2];
	int					ft_in_files;
	int					ft_out_files;
	char				*ft_command_path;
	struct s_cmd_info	*prev;
	struct s_cmd_info	*next;
}			t_cmd_info;

typedef struct s_env_info
{
	char				*env_key;
	char				*env_val;
	struct s_env_info	*next;
	struct s_env_info	*prev;
}			t_env_info; 

void		print_checker(t_cmd_info *cmd, t_env_info *env);

void		*ft_free(void *ptr);
t_cmd_info	*ft_cmd_init(void);
void		ft_free_list(t_cmd_info *cmd);
t_env_info	*compare_env_key(t_env_info *info_env, char *key);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcpy(char *dest, const char *src, size_t destsize);
char		*ft_strdup(const char *s1);
void		ft_putstr_fd(char *s, int fd);
int			ft_isspace(char c);

char		*ft_strchr(const char *s, int c);

void		ft_dup2(int fd1, int fd2);
void		ft_pipe(int *fds);
pid_t		ft_fork(void);

int			ft_open(char *fname, int oflag, int mode);
int			ft_close(int fd);
void		*ft_malloc(size_t size, size_t n);
int			ft_write(int fd, const void *buf, size_t byte);
void		ft_execve(const char *file, char *const *argv, char *const *envp);
char		*ft_getcwd(char *buf, size_t size);

int			is_exist_file(char *tmp_file_name);
void		exit_errno(char *str1, char *str2, int exit_code);
void		print_quote_err3(char *cmd, char *str1, char *str2);
void		print_err1(char *str);
void		print_err2(char *str1, char *str2);
void		print_err3(char *cmd, char *str1, char *str2);

void		set_signal(int sig_int, int sig_quit);

int			ft_str_isspace(char *str);
void		ft_main_init(int argc, char **argv);
static void	first(t_cmd_info *tmp, t_cmd_info **ptr, t_cmd_info **head);
void		ft_arg_check(t_cmd_info **cmd);

static void	*is_free(char **str, int str_index);
static int	get_word_cnt(char const *str, char c);
static char	**set_worddup(char const *s, char c, char **mem);
char		**ft_split_arg(char const *s, char c, int *argc);

char		*ft_join_ascii(char *s1, char s2);

static char	*in_pipe(char *str, int *ch_pipe, t_cmd_info **cmd, t_cmd_info *next);
static char	*add_redirect_space(char *str, char *input, char c);
static char	*out_pipe(char *str, int *ch_pipe, char *input, int ch_quote);
void		ft_parse(char *input, t_cmd_info *cmd);

int			set_quotes(char str, int ch_quotes, t_cmd_info *cmd);
char		*ft_strjoin_free(char *s1, char *s2);
void		ft_del_argv(t_cmd_info *cmd, int *i);
void		ft_change_argv(t_cmd_info *cmd, char *new, int i);

static char	*ft_tokenize_while_dollar(char str, char *new, t_env_info *head, int quotes);
static char	*ft_tokenize_while_else(char c, char *new, int quotes);
static int	dollar_check(char c);
static char	*ft_tokenize_while(t_cmd_info *cmd, t_env_info *head, int i);
void		ft_tokenize(t_cmd_info *cmd, t_env_info *head);

int			ft_env_init(t_env_info *info_env, char **envp);
t_env_info	*new_env(char *key_value);
t_env_info	*compare_env_key(t_env_info *info_env, char *key);
char		*get_env_value(char *key_value);
char		*get_env_key(char *key_value);

char	*ft_getenv(t_env_info *info_env, char *key);


static char	**get_envp(t_env_info *head);
static int	os_builtins(t_cmd_info *cmd, t_env_info *info_env);
static int	execute_cmd(t_cmd_info *cmd, t_env_info *info_env);
static void	do_fork_cmd(t_cmd_info *cmd, t_env_info *info_env);
static void	do_cmd(t_cmd_info *cmd, t_env_info *info_env);

void	execute(t_cmd_info *cmd, t_env_info *info_env);
void	ft_redirect(t_cmd_info *cmd);
int		heredoc(t_cmd_info *cmd);
void	ft_close_not_use_fd(t_cmd_info *cmd, pid_t pid);
int		check_valid_token(t_cmd_info *cmd);
void	wait_child(void);
int		ft_is_need_fork_cmd(t_cmd_info *cmd);
void	restore_redirection_char(t_cmd_info *cmd);

char	*ft_get_cmd_path(t_cmd_info *cmd, t_env_info *info_env);

int		io_file_open(t_cmd_info *cmd, t_env_info *info_env);
void	ft_command_argv_trim(t_cmd_info *cmd, const char *set, int direction);

char	*ft_get_tmp_file(void);
void	ft_del_tmpfile(void);
int		ft_here_init(t_cmd_info *cmd);
void	ft_clear_command(t_cmd_info *cmd);

int		ft_open(char *fname, int oflag, int mode);
int		ft_close(int fd);
void	ft_dup2(int fd1, int fd2);
void	ft_pipe(int *fds);
pid_t	ft_fork(void);


// int	ft_is_valid_identifier(char *identifier);
// void printstderr(char *str);
// int	cmd_and_av_cnt(char **cmd_and_av);
// int	change_dir(char *path);
// int	mini_cd(t_cmd_info *cmd, t_env_info *env);
// int	mini_echo(t_cmd_info *cmd, t_env_info *env);
// int mini_env(t_cmd_info *cmd, t_env_info *env);
// int mini_exit(t_cmd_info *cmd);
// int	mini_export(t_cmd_info *cmd, t_env_info *env);
// int	mini_pwd(t_cmd_info *cmd, t_env_info *env);
// int mini_unset(t_cmd_info *cmd, t_env_info *env);


//builtin
int		ft_pwd(void);
int		ft_cd(char *path, t_env_info *info_env);
int		ft_env(t_env_info *info_env);
int		ft_echo(int argc, char **argv);
int		ft_exit(t_cmd_info *cmd);
int		ft_unset(int argc, char **argv, t_env_info *info_env);
t_env_info	*dup_env_list(t_env_info *cur);
t_env_info	*sort_env_list(t_env_info *head);
void	free_env_list(t_env_info *env);
char	*get_pwd_key_value(const char *key);
void	export_pwd(const char *pwd, t_env_info *info_env);

int		ft_export(int argc, char **argv, t_env_info *info_env);
void	export_key_value(t_env_info *info_env, char *key_value);
int		check_valid_identifier(int argc, char **argv);
int		is_all_digit(char *key_value, char set);
int		is_have_space(char *key_value, char set);
int		is_have_specific_char(char *key_value, char c);

int		init_env_list(t_env_info *cur, char **envp);
t_env_info	*new_env(char *key_value);
char	*get_env_key(char *key_value);
char	*get_env_value(char *key_value);
t_env_info	*compare_env_key(t_env_info *info_env, char *key);
char	*ft_getenv(t_env_info *info_env, char *key);


#endif

