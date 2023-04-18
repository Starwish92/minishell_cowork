/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyyoo <hyyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:28:52 by hyyoo             #+#    #+#             */
/*   Updated: 2023/04/18 18:28:55 by hyyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	ft_write(STDOUT_FILENO, "\n", 1);
	free(pwd);
	return (EXIT_SUCCESS);
}
