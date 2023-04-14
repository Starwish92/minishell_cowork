/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:01:49 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/14 20:54:38 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_redirect_pipe_in(t_cmd_info *cmd)
{
	if (cmd->prev == false)
		return ;
	return (ft_dup2(cmd->prev->fd[READ], STDIN_FILENO));
}

static void	ft_redirect_pipe_out(t_cmd_info *cmd)
{
	if (cmd->ft_pipe_flag == false)
		return ;
	return (ft_dup2(cmd->fd[WRITE], STDOUT_FILENO));
}

static void	ft_redirect_infile(t_cmd_info *cmd)
{
	if (cmd->ft_in_files < 0)
		return ;
	return (ft_dup2(cmd->ft_in_files, STDIN_FILENO));
}

static void	ft_redirect_outfile(t_cmd_info *cmd)
{
	if (cmd->ft_out_files < 0)
		return ;
	return (ft_dup2(cmd->ft_out_files, STDOUT_FILENO));
}

void	ft_redirect(t_cmd_info *cmd)
{
	ft_redirect_pipe_in(cmd);
	ft_redirect_pipe_out(cmd);
	ft_redirect_infile(cmd);
	ft_redirect_outfile(cmd);
	return ;
}