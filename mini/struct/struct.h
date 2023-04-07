/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngjpa <youngjpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:09:22 by youjeon           #+#    #+#             */
/*   Updated: 2023/04/07 15:31:46 by youngjpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>
# include <stdlib.h>

int	g_exit_signal_code; //$? == 오류코드 위해서

typedef struct s_cmd_info //s_cmd_info
{
	char			**cmd_and_av; //cmd_and_av
	// 커멘드랑 알규먼트 같이 가지고 있음, 파이프 기준으로 엑스큐트에 넘김
	// echo -n 42 | cat -e 
	// echo, -n, 42 
	// cat, -e
	int				ac; //ac
	bool			ft_pipe_flag; //ft_pipe_flag
	bool			ft_dollar_flag; //ft_dollar_flag
	int				fd[2]; //fd
	int				ft_in_files; //ft_in_files
	int				ft_out_files; //ft_out_files
	char			*ft_command_path; //ft_command_path
	struct s_cmd_info	*prev; //prev
	struct s_cmd_info	*next; //next
}						t_cmd_info; //t_cmd_info

typedef struct s_info_env //s_info_env
{
	char			*key; //env_key
	char			*value; //env_val
	struct s_info_env	*next; //next
	struct s_info_env	*prev; //prev
}	t_info_env; //t_info_env

void		*ft_frees(void *ptr);
t_cmd_info		*ft_list_init(void);
void		ft_free_list(t_cmd_info *cmd);

#endif

