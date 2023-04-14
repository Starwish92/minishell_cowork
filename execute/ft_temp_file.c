/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_temp_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:02:01 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/14 20:55:52 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_get_tmp_file_num(void)
{
	static int	tmp_file_num;

	return (tmp_file_num++);
}

char	*ft_get_tmp_file(void)
{
	int		tmp_num;
	char	*str_num;
	char	*file_name;

	while (1)
	{
		tmp_num = ft_get_tmp_file_num();
		str_num = ft_itoa(tmp_num);
		file_name = ft_strjoin("tmp_file_", str_num);
		if (is_exist_file(file_name) == 0)
		{
			free(str_num);
			return (file_name);
		}
		free(file_name);
		free(str_num);
	}
}

void	ft_del_tmpfile(void)
{
	int		tmp_num;
	char	*str_num;
	char	*file_name;

	tmp_num = ft_get_tmp_file_num();
	while (--tmp_num > -1)
	{
		str_num = ft_itoa(tmp_num);
		file_name = ft_strjoin("tmp_file_", str_num);
		if (is_exist_file(file_name))
			unlink(file_name);
		free(str_num);
		free(file_name);
	}
	return ;
}
