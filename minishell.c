/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyyoo <hyyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:03:41 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/07 15:38:23 by hyyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
		{
			return (0);
		}
		line++;
	}
	return (1);
}

void	main_init(int argc, char *argv[])
{
	struct termios	term;

	if (argc != 1)
		exit_with_err("argument input error", NULL, 126);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(SHE, SHE);
	g_exit_signal_code = 0;
	(void)argc;
	(void)argv;
}

int	main(int argc, char *argv[], char *envp[])
{
	char				*line;
	t_cmd_info			*cmd;
	t_info_env			env_head;
	struct termios		term;

	tcgetattr(STDIN_FILENO, &term); //터미널fd, 터미널 속성 저장 포인터
	//터미널의 속성을 변경한다. ctrl + c 를 입력하였을 때 그냥 새로운 줄이 입력되어야 하는데,
	// ctrl + c에 대한 반향(echo) '^C' 이 출력되는 현상이 있기 때문에 
	//echo 를 출력하지 않도록 막아두고 필요할 때마다 수동으로 출력한다. 
	main_init(argc, argv);
	init_env_list(&env_head, envp);
	while (42)
	{
		line = readline("minishell $ ");
		if (!line) //EOF처리 cntl + d
			break ;
		if (*line != '\0')
			add_history(line); //history 저장
		if (*line != '\0' && !is_whitespace(line))
		{
			cmd = ft_list_init();
			parse(line, cmd);
			replace(cmd, &env_head);
			argc_checker(&cmd);
			//여기까지가 파싱.
			// executor(cmd, &env_head);
			ft_free_list(cmd);
		}
		free(line);
		//system("leaks minishell | grep leaked"); //
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	/*
	int  tcsetattr(int fd, int action, const struct termios* termios_p);
	- action필드의 내용데로 설정한다.
    . TCSANOW:    값을 즉시 변경한다.
	*/
}

/*
환경변수 구조체 하나, 파이프와 달러표시 플래그, 커멘드,
와일문으로 readline무한루프 돌면서 커멘드 커멘드 계속 초기화하면서 파싱부로 돌입.
', "처리, 
input을 null, 세미콜론, 파이프, 리다이렉션 기준으로 분해.
tcgetattr
tcsetattr로 cntl + d, c, \ 처리

*/
