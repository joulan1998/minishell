/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:48:34 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/12 18:42:26 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int final_update(t_minishell *data, char *key, char *value, bool create)
{
	t_environ	*lst;

	lst = data->env_lst;
	if (!create)
	{
		while (lst)
		{
			if (!ft_strncmp(lst->var, key, (ft_strlen(lst->var) + 1)))
			{
				free (lst->value);
				lst->value = value;
			}
			lst = lst->next;
		}
		return (0);
	}
	else
		return(ft_lstadd_back_env(&data->env_lst, ft_lstnew_env(key, value)), 0);
	return (1);
}

int test_print(t_minishell *data)
{
    t_environ	*local_lst;
    int			i;

	local_lst = data->env_lst;
    int size = ft_lstsize(data->env_lst);
    char **list = malloc((size + 1) * sizeof(char *));
    if (!list)
        return 0;
	i = 0;
    while (local_lst)
	{
		// if (local_lst->value)
		// {
        	char *temp = ft_strjoin(local_lst->var, "=");
        	if (!temp)
			{
        	    while (i > 0) free(list[--i]);
        	    free(list);
        	    return 0;
        	}
        	list[i] = ft_strjoin(temp, local_lst->value);
        	free(temp);
        	if (!list[i])
			{
        	    while (i > 0) free(list[--i]);
        	    free(list);
        	    return 0;
        	}
		// }
        i++;
        local_lst = local_lst->next;
    }
    list[i] = NULL;
	sort_and_print(list);
    i = 0;
    while (list[i])
	{
        free(list[i]);
        i++;
    }
    free(list);
    return 1;
}

int	entry_already_exits(t_minishell *data, char *key)
{
	t_environ *local;
	char *local_key;

	local = data->env_lst;
	local_key = extract_key(key);
	if (local_key[ft_strlen(local_key) - 1] == '+')
		local_key[ft_strlen(local_key) -1] = '\0';
	while (local)
	{
		if (ft_strncmp(local->var , local_key, ft_strlen(local->var) + 1) == 0)
			return(free(local_key),1);
		local = local->next;
	}
	return(free(local_key),0);
}

int ft_append_for_export(t_minishell *data, char *line)
{
	t_environ	*local;
	char		*tmp;
	char		*local_value;
	char		*var;
	
	local = data->env_lst;
	local_value = extract_value(line);
	int i =0;
	while (line[i] != '+')
		i++;
	var = extract_key(line);
	var[ft_strlen(var)-1] ='\0';
	while (local)
	{
		if (!ft_strncmp(local->var, var, ft_strlen(local->var)))
		{
			tmp = local->value;
			local->value = ft_strjoin(local->value, local_value);
			free(tmp);
			free(local_value);
			return(0);
		}
		local = local->next;
	}
	ft_lstadd_back_env(&(data->env_lst),ft_lstnew_env(var,local_value));
	return(-1);
}

int	update_export(t_minishell *data, char **table)
{
	int i;
	int result;
	char *key;
	char *value;

	i = 0;
	result = 0;
	while (table && table[i])
	{
		if (check_syntax_for_export(table[i]))
		{
			key = extract_key(table[i]);
			value = extract_value(table[i]);
			if (entry_already_exits(data, key) && (ft_strchr(key, '+') != NULL))
				ft_append_for_export(data, table[i]);
			else if (entry_already_exits(data, key) && (ft_strchr(key, '+') == NULL))
				final_update(data, key, value, false);
			else
				final_update(data, key, extract_value(table[i]), true);
		}
		else
			return(ft_error_export_2_args("export",table[i]), 0);
		i++;
	}
	return(result);
}

int	ft_export(t_minishell *data)
{
	t_environ *local;
	char **args;
	local = (data)->env_lst;
	args = &((data)->commands->args[1]);
	if (!(*args))
		test_print(data);
	else
		update_export(data, args);
	return(0);
}
