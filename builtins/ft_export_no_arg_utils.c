
#include "../minishell.h"

static void	swap_env(t_env_info *env1, t_env_info *env2)
{
	char	*tmp_k;
	char	*tmp_v;

	tmp_k = env1->env_key;
	tmp_v = env1->env_val;
	env1->env_key = env2->env_key;
	env1->env_val = env2->env_val;
	env2->env_key = tmp_k;
	env2->env_val = tmp_v;
}

static t_env_info	*dup_env(t_env_info *cur)
{
	t_env_info	*new;

	new = (t_env_info *)ft_malloc(sizeof(t_env_info), 1);
	if (cur == NULL)
	{
		new->env_key = NULL;
		new->env_val = NULL;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		new->env_key = ft_strdup(cur->env_key);
		new->env_val = ft_strdup(cur->env_val);
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

t_env_info	*dup_env_list(t_env_info *cur)
{
	t_env_info	*ret;
	t_env_info	*new;
	t_env_info	*tmp;

	ret = dup_env(cur);
	tmp = ret;
	cur = cur->next;
	while (cur->env_key)
	{
		new = dup_env(cur);
		tmp->next = new;
		new->prev = tmp;
		tmp = new;
		cur = cur->next;
	}
	new = dup_env(NULL);
	tmp->next = new;
	new->prev = tmp;
	return (ret);
}

t_env_info	*sort_env_list(t_env_info *head)
{
	t_env_info	*cur;

	cur = head;
	while (cur->next->env_key)
	{
		if (ft_strcmp(cur->env_key, cur->next->env_key) > 0)
		{
			swap_env(cur, cur->next);
			cur = head;
		}
		else
			cur = cur->next;
	}
	return (head);
}

void	free_env_list(t_env_info *info_env)
{
	t_env_info	*next;

	while (info_env->env_key)
	{
		next = info_env->next;
		free(info_env->env_key);
		free(info_env->env_val);
		free(info_env);
		info_env = next;
	}
	free(info_env->env_key);
	free(info_env->env_val);
	free(info_env);
}
