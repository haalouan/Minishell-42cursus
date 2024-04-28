/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:28:38 by achater           #+#    #+#             */
/*   Updated: 2024/04/28 16:29:26 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(char	**args)
{
	if (args == NULL )
	{
		chdir(getenv("HOME"));
		return;
	}
	if (chdir(args[0]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", args[0]);
		return;
	}
}

int cmp(char *s1)
{
	int i = 0;

	if(s1[i] == '-' && s1[i + 1] == 'n')
	{
		i++;
		while(s1[i])
		{
			if(s1[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}
void	ft_echo(char **args)
{
	int j;
	int n;

	j = 0;
	n = 0;
	if (args == NULL)
	{
		printf("\n");
		return;
	}
	if (cmp(args[0]) == 0)
	{
		j++;
		n = 1;
	}
	while (args[j])
	{
		if (cmp(args[j]) == 0 && n == 1)
		{
			j++;
			continue ;
		}
		printf("%s", args[j]);
		if (args[j + 1])
			printf(" ");
		j++;
	}
	if (n == 0)
		printf("\n");
}
void	ft_env(t_env *env_list, char **args)
{
	if(args && args[0])
	{
		printf("env: %s: No such file or directory\n", args[0]);
		return;
	}

	while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}
void	ft_exit(char **args)
{
	printf("exit\n");
	if(args && args[0])
		printf("minishell: exit: %s: numeric argument required\n", args[0]);
	exit(0);
}
void	ft_pwd()
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if(pwd == NULL)
	{
		perror("getcwd");
		return;
	}
	printf("%s\n", pwd);
}

void	ft_remove(t_env **env_list, char *key)
{
	t_env *temp = *env_list;
	t_env *prev = NULL;

	while(env_list && temp->next != NULL)
	{
		if (ft_strcmp(temp->key, key) != 0)
		{
			prev = temp;
			temp = temp->next;
		}
		else if (prev == NULL && ft_strcmp(temp->key, key) == 0)
		{
			*env_list = temp->next;
			free(temp);
			return;
		}
		else if (ft_strcmp(temp->key, key) == 0)
		{
			prev->next = temp->next;
			free(temp);
			return;
		}
		if(temp->next == NULL && ft_strcmp(temp->key, key) == 0)
		{
			prev->next = NULL;
			free(temp);
			return;
		}
	}
	return;
}

void	ft_unset(t_env **env_list, char **args)
{
	int i = 0;

	if (args == NULL)
		return;
	while (args[i])
	{
		ft_remove(env_list, args[i]);
		i++;
	}
}

void	ft_builtins(t_list *cmds, t_env **env_list)
{
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		ft_echo(cmds->args);
	else if (ft_strcmp(cmds->cmd, "cd") == 0)
		ft_cd(cmds->args);
	else if (ft_strcmp(cmds->cmd, "env") == 0 && cmds)
		ft_env(*env_list, cmds->args);
	// else if (ft_strcmp(cmds->cmd, "export") == 0)
	// 	ft_export(cmds->args);
	else if (ft_strcmp(cmds->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		ft_unset(env_list,cmds->args);
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		ft_exit(cmds->args);
}

void set_env(char **env, t_env **env_list)
{
	int i = 0;
	// int j = 0;
	// t_env *new;
	char **splited_env = NULL;

	while(env[i])
	{
		splited_env = ft_split(env[i], '=');
		ft_lstadd_back(env_list, ft_lstnew(splited_env[0], splited_env[1]));
		i++;
	}
}

// int main(int argc, char **argv, char **env)
// {
// 	// printf("%s\n", argv[1]);
// 	t_list *cmds;
// 	cmds = malloc(sizeof(t_list));
// 	cmds->redir = NULL;
// 	cmds->cmd = "cd";
// 	cmds->args = ft_split("", ' ');
// 	cmds->next = NULL;
// 	t_env *env_list = NULL;
// 	t_env *temp = env_list;

// 	int i = 0;

// 	set_env(env, &env_list);

// 	ft_builtins(cmds, &env_list);
// 	return (0);
// }

void execution(t_list **list,char **env)
{
	t_env *env_list = NULL;


	set_env(env, &env_list);
	ft_builtins(*list, &env_list);

}
