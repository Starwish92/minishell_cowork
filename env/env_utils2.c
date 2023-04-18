/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shane <shane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:10:25 by hyyoo             #+#    #+#             */
/*   Updated: 2023/04/18 16:32:45 by shane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_key2(char *key_value)
{
	char	*temp;
	size_t	len;
	size_t	i;

	len = ft_strlen(key_value);
	temp = (char *)ft_malloc(sizeof(char), len + 1);
	i = 0;
	while (i < len)
	{
		temp[i] = key_value[i];
		++i;
	}
	temp[i] = 0;
	return (temp);
}

char	*get_env_value2(void)
{
	char	*temp;

	temp = ft_strdup("don't_print_this");
	return (temp);
}

t_env_info	*compare_env_key(t_env_info *info_env, char *key)
{
	t_env_info	*temp;

	temp = info_env;
	while (temp->env_key != 0 && ft_strncmp(key, temp->env_key, ft_strlen(key)))
		temp = temp->next;
	return (temp);
}

char	*ft_getenv(t_env_info *info_env, char *key)
{
	t_env_info	*cur;

	cur = compare_env_key(info_env, key);
	if (ft_strcmp(cur->env_val, "don't_print_this"))
		return (NULL);
	return (cur->env_val);
}
