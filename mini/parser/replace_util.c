/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:11:34 by youjeon           #+#    #+#             */
/*   Updated: 2023/04/07 14:30:03 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *)ft_malloc(sizeof(char), (s1_len + s2_len + 1));
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, s2, s2_len + 1);
	free(s1);
	return (ret);
}

void	delete_argv(t_cmd_info *cmd, int *i)
{
	int		tmp;

	tmp = *i;
	cmd->cmd_and_av[tmp] = ft_frees(cmd->cmd_and_av[tmp]);
	while (tmp < cmd->ac - 1)
	{
		cmd->cmd_and_av[tmp] = cmd->cmd_and_av[tmp + 1];
		tmp++;
	}
	*i = *i - 1;
	cmd->ac = cmd->ac - 1;
	cmd->ft_dollar_flag = false;
	cmd->cmd_and_av[tmp] = 0;
}

void	argv_change(t_cmd_info *cmd, char *new, int i)
{
	if (new == NULL) //달러가없고 new가 NULL; '' 혹은 ""처리를 위해서
		new = ft_strdup("");
	cmd->cmd_and_av[i] = ft_frees(cmd->cmd_and_av[i]);
	cmd->cmd_and_av[i] = new;
}
