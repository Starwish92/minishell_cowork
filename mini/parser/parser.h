/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:46:48 by youjeon           #+#    #+#             */
/*   Updated: 2023/04/07 14:30:33 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../struct/struct.h"
# include "../utiles/utiles.h"
# include "../builtins/builtin.h"

char	**ft_split_argc(char const *s, char c, int *argc);
char	*ft_strjoin_char(char *s1, char s2);
int		parse_set_quotes(char line, int quotes, t_cmd_info *cmd);
void	parse(char *line, t_cmd_info *cmd);
void	replace(t_cmd_info *cmd, t_info_env *head);
void	delete_argv(t_cmd_info *cmd, int *i);
void	argc_checker(t_cmd_info **cmd);
void	argv_change(t_cmd_info *cmd, char *new, int i);
char	*ft_strjoin_free(char *s1, char *s2);

#endif
