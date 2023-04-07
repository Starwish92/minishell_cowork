/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:08:04 by mher              #+#    #+#             */
/*   Updated: 2023/04/07 14:30:33 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define READ 0
# define WRITE 1

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>

# include "../struct/struct.h"
# include "../utiles/utiles.h"
# include "../builtins/builtin.h"

void	executor(t_cmd_info *cmd, t_info_env *env_head);
void	redirect(t_cmd_info *cmd);
int		heredoc(t_cmd_info *cmd);
void	close_unused_fd(t_cmd_info *cmd, pid_t pid);
int		check_valid_syntax(t_cmd_info *cmd_head);
void	wait_child(void);
int		is_need_fork(t_cmd_info *cmd);
void	restore_redirection_char(t_cmd_info *cmd);

char	*get_cmd_path(t_cmd_info *cmd, t_info_env *env_head);

int		io_file_open(t_cmd_info *cmd, t_info_env *env_head);
void	trim_cmd_argv(t_cmd_info *cmd, const char *set, int direction);

char	*get_tmp_file_name(void);
void	delete_tmp_file(void);
int		init_heredoc(t_cmd_info *cmd);
void	clear_cmd(t_cmd_info *cmd_head);

#endif
