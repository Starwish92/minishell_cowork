/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:44:28 by youjeon           #+#    #+#             */
/*   Updated: 2023/04/07 14:31:20 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*replace_while_dollar(char str, char *new, t_info_env *head, int quotes)
{
	static char	*env = NULL; //U, US, USE, USER

	if (ft_isalnum(str) || str == '_')
		env = ft_strjoin_char(env, str);
	else if (str == '?' && env == NULL) //$? == 오류코드 처리 NULL있는 이유는 $?뒤에 뭐 붙었을때 대비해서
	{
		env = ft_itoa(g_exit_signal_code);
		new = ft_strjoin_free(new, env);
		env = ft_frees(env);
	}
	else
	{
		if (env != NULL)
		{
			new = ft_strjoin_free(new, ft_getenv(head, env));
			if (!(str == '\"' && quotes != 1) && !(str == '\'' && quotes != 2))
				new = ft_strjoin_char(new, str);
			// printf("new == %s\n", new);
			// printf("env == %s\n", env);
			env = ft_frees(env);
			g_exit_signal_code = 0; //성공했다는 뜻
		}
		else
			new = ft_strjoin_char(new, '$'); //$뒤에 아무것도 붙지 않았으면 $만 출력
	}
	return (new);
}

static char	*replace_while_else(char c, char *new, int quotes)
{
	char	*result;

	result = NULL;
	if (c == -32)
		result = ft_strjoin_char(new, ' ');
	else if (!(c == '\"' && quotes != 1) && !(c == '\'' && quotes != 2)) //'$USER', "$USER" 구분 위해서
	{
		result = ft_strjoin_char(new, c);
	}
	else
	{
		return (new);
	}
	return (result);
}

static int	dollar_check(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '$')
		return (1);
	else
		return (0);
}

static char	*replace_while(t_cmd_info *cmd, t_info_env *head, int i)
{
	int		j;
	char	*new;
	int		dollar;
	int		quotes;

	quotes = 0;
	dollar = 0;
	j = 0;
	new = NULL;
	while (j <= (int)ft_strlen(cmd->cmd_and_av[i])) //cmd의 모든 이중배열 탐색 // 캐릭터별로 와일문 탐색
	{
		quotes = parse_set_quotes(cmd->cmd_and_av[i][j], quotes, cmd); //', "짝 확인
		if (cmd->cmd_and_av[i][j] == '$' && quotes != 1 && dollar == 0) //'$가 아닐때 $상태로 바꿈
			dollar = 1;
		else if (dollar == 1)
		{
			new = replace_while_dollar(cmd->cmd_and_av[i][j], new, head, quotes);
			dollar = dollar_check(cmd->cmd_and_av[i][j]); //달러뒤에 아무것도 없으면 다시 $ 0 으로 초기화
		}
		else
			new = replace_while_else(cmd->cmd_and_av[i][j], new, quotes);
		j++;
	}
	return (new);
}

void	replace(t_cmd_info *cmd, t_info_env *head)
{
	int		i;
	char	*new;
	
	while (cmd) //cmd의 argv를 모두 처리 ->next 로돌면서
	{
		i = 0;
		while (i < cmd->ac) //각 cmd의 argv를 모두 순회
		{
			new = replace_while(cmd, head, i); //빈 배열에 replace_while "$USER"등의 처리
			if (new == NULL && cmd->ft_dollar_flag)
			{
				delete_argv(cmd, &i); //환경변수의 value가 비어있다면
			}
			// else if (new == NULL) //달러가없고 new가 NULL; '' 혹은 ""처리를 위해서
			// {
			// 	// printf("here\n");
			// 	new = ft_strdup("");
			// 	argv_change(cmd, new, i);
			// }
			else
				argv_change(cmd, new, i);
			i++;
		}
		cmd = cmd->next;
	}
}
