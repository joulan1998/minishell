/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:47:49 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/21 19:04:56 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_acces(t_minishell *data, char *ftn)
{
	char	**table;
	char	*path;
	int		i;
	char	*node_contet;

	table = NULL;
	i = 0;
	if (!ftn || !data->env_lst)
		return (NULL);
	if (access (ftn, X_OK) == 0)
		return (ft_strdup(ftn));
	else
	{
		if (!(node_contet = ft_find_node(data, "PATH")))
			return (free_table(data), NULL);
		table = ft_split(node_contet, ':');
		while (i < count_table_entries(table))
		{
			path = ft_strjoin(table[i], "/");
			path = joinning_and_free(path, ftn);
			if (access (path, X_OK) == 0)
			{
				ft_free_table (&table);
				free (node_contet);
				return (path);
			}
			free (path);
			i++;
		}
		// ft_free_table(&data->env);
		free (node_contet);
		ft_free_table (&table);
	}
	return (NULL);
}

void	handle_access_cases(int	error)
{
	perror (PROMPT);
	(void) error;
	exit (127);
}

int	exec_smpl_cmnd(t_minishell *data)
{
	char	*path;
	int		fork_res;
	// int 	exec_res;

	path = check_acces (data, data->commands->args[0]);
	fork_res = fork();
	if (fork_res == -1)
		return (perror (PROMPT), -1);
	if (fork_res == 0)
	{
		if (execve(path, data->commands->args, (data->env)) == -1)
		{
			ft_putstr_fd("COMMAND NOT FOUND \n", 2);
			// free (path);
			exit (127);
		}
		// return ( 127);
	}
	else
	{
		while (waitpid (fork_res, &data->status, 0) != -1)
			;
		printf("######>>>>>>>>is %d\n",data->status);
		// wait(NULL);
		// ft_free_table(&data->commands); // chech for exit status
		free (path);
	}
	return (data->status);
}
