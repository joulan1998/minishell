/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:48:34 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/19 15:30:24 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	final_update(t_minishell *data, char *key, char *value, bool create)
{
	t_environ	*lst;

	lst = data->env_lst;
	if (!create)
	{
		while (lst)
		{
			if (!ft_strncmp(lst->var, key, (ft_strlen(lst->var) + 1)))
			{
				if (value)
				{
					free (lst->value);
					lst->value = value;
				}
			}
			lst = lst->next;
		}
		return (0);
	}
	else
		return (ft_lstadd_back_env
			(&data->env_lst, ft_lstnew_env(key, value)), 0);
	return (1);
}

int	test_print(t_minishell *data)
{
	t_environ	*local_lst;
	int			i;
	char		*temp;
	char		*temp1;
	char		**list;

	list = malloc((ft_lstsize(data->env_lst) + 1) * sizeof(char *));
	local_lst = data->env_lst;
	if (!list)
		return (0);
	i = 0;
	while (local_lst)
	{
		if (!ft_strncmp(local_lst->var, "_", 2))
		{
			local_lst = local_lst->next;
			continue ;
		}
		if (!local_lst->value)
			list[i] = ft_strjoin(local_lst->var, "=");
		else
		{
			temp = ft_strjoin(local_lst->var, "=\"");
			temp1 = ft_strjoin(local_lst->value, "\"");
			if (!temp || !temp1)
				return (ft_free_table(&list), -1);
			list[i] = ft_strjoin(temp, temp1);
			free (temp);
			free (temp1);
		}
		i++;
		local_lst = local_lst->next;
	}
	list[i] = NULL;
	sort_and_print(list);
	ft_free_table(&list);
	return (1);
}

int	is_exits(t_minishell *data, char *key)
{
	t_environ	*local;
	char		*local_key;

	local = data->env_lst;
	local_key = extract_key (key);
	if (local_key[ft_strlen (local_key) - 1] == '+')
		local_key[ft_strlen (local_key) - 1] = '\0';
	while (local)
	{
		if (ft_strncmp(local->var, local_key, ft_strlen(local->var) + 1) == 0)
			return (free(local_key), 1);
		local = local->next;
	}
	return (free(local_key), 0);
}

int	ft_append_for_export(t_minishell *data, char *line)
{
	t_environ	*local;
	char		*tmp;
	char		*local_value;
	char		*var;

	local = data->env_lst;
	local_value = extract_value(line);
	var = extract_key(line);
	var[ft_strlen(var)-1] = '\0';
	while (local)
	{
		if (!ft_strncmp(local->var, var, ft_strlen(local->var)))
		{
			tmp = local->value;
			local->value = ft_strjoin(local->value, local_value);
			free (tmp);
			free (local_value);
			return (0);
		}
		local = local->next;
	}
	ft_lstadd_back_env (&(data->env_lst), ft_lstnew_env(var, local_value));
	return (-1);
}

int	update_export(t_minishell *data, char **table)
{
	char	*key;
	char	*value;
	int		i;
	int		re;

	i = -1;
	while (table && table[++i])
	{
		if (check_syntax_for_export(table[i]))
		{
			key = extract_key(table[i]);
			value = extract_value(table[i]);
			if (is_exits(data, key) && (ft_strchr(key, '+') != NULL))
				re = ft_append_for_export(data, table[i]);
			else if (is_exits(data, key) && (ft_strchr(key, '+') == NULL))
				re = final_update(data, key, value, false);
			else if (!is_exits(data, key) && (ft_strchr(table[i], '=') != NULL))
				re = final_update(data, key, extract_value(table[i]), true);
			else if ((ft_strchr(table[i], '=') == NULL))
				re = final_update(data, key, extract_value(table[i]), true);
		}
		else
			return (ft_error_export_2_args("export", table[i]), 0);
	}
	return (re);
}

int	ft_export(t_minishell *data)
{
	t_environ	*local;
	char		**args;

	local = (data)->env_lst;
	args = &((data)->commands->args[1]);
	if (!(*args))
		test_print(data);
	else
		update_export(data, args);
	return (0);
}
