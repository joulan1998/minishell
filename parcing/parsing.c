/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 11:07:04 by yosabir           #+#    #+#             */
/*   Updated: 2024/10/22 13:15:29 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"  // "space" "" '' $ | > < >> << \t

static void	handle_single_char(char *str, int i, t_list **lst)
{
	t_list	*new_node;

	new_node = ft_lstnew(ft_substr(str, i, 1));
	if (str[i] == '|')
		new_node->command = PIPE;
	else if (str[i] == '<')
		new_node->command = RD_IN;
	else if (str[i] == '>')
		new_node->command = RD_OUT;
	ft_lstadd_back(lst, new_node);
}

static int	parse_operator(char *str, int i, t_list **lst)
{
	t_list	*new_node;
	// printf("---OPERATOR---");
	if (str[i] == '<' && str[i + 1] == '<')
	{
		new_node = ft_lstnew(ft_substr(str, i, 2));
		new_node->command = HEREDOC;
		ft_lstadd_back(lst, new_node);
		i++;
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		new_node = ft_lstnew(ft_substr(str, i, 2));
		new_node->command = APPEND;
		ft_lstadd_back(lst, new_node);
		i++;
	}
	else
	{
		new_node = NULL;
		handle_single_char(str, i, lst);
	}
	return (i);
}

static int	parse_variable(char *str, int i, t_list **lst)
{
	t_list	*new_node;
	int		k;

	k = i;
	i++;

	if (str[i] == '_' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
	{
		while (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != '\'' && str[i] != '"')
			i++;
		i--;
		new_node = ft_lstnew(ft_substr(str, k + 1, i - k));
		new_node->command = VAR;
		ft_lstadd_back(lst, new_node);
	}
	else
		return k;

	return i;
}

int parse_quote(char *str, int i, t_list **lst) 
{
    t_list *node;
    int j;
    char quote_char;

    j = i;
    quote_char = str[i];
    i++;

    while (str[i] && str[i] != quote_char)
        i++;

    if (str[i] == '\0') 
    {
        ft_putstr_fd("syntax error\n", 2);
        exit_status(258, 1);
        return -1;
    }

    node = ft_lstnew(ft_substr(str, j, (i - j) + 1));
    if (quote_char == '"')
        node->command = D_QUOTE;
    else if (quote_char == '\'')
        node->command = S_QUOTE;
    ft_lstadd_back(lst, node);
    return i;
}

t_list	*parsing(char *str)
{
	t_list	*lst;
	int		i;
	
	i = 0;
	lst = NULL;
	while (str[i])
    {
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
            i = parse_operator(str, i, &lst);
        else if (str[i] == '$' && str[i + 1])
            i = parse_variable(str, i, &lst);
        else if (str[i] == '\'' || str[i] == '"')
		{
            i = parse_quote(str, i, &lst);
			if (i < 0)
				break;
		}
        else if (str[i] == ' ' || str[i] == '\t')
            i = parse_spaces(str, i, &lst);
		else
            i = parse_word(str, i, &lst);
        i++;
    }
    return lst;
}
