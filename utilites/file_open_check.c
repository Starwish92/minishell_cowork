/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngjpa <youngjpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:01:26 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/07 15:47:03 by youngjpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_exist_file(char *tmp_file_name)
{
	int	fd;

	fd = open(tmp_file_name, O_RDONLY);
	close(fd);
	if (fd == -1)
		return (0);
	else
		return (1);
}
