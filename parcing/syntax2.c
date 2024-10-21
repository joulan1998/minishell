/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:46:17 by yosabir           #+#    #+#             */
/*   Updated: 2024/10/21 16:56:54 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

int is_space(t_list *token)
{
    return (token && (token->command == SPACEE));
}

int check_redirection_followed_by_pipe(t_list *current)
{
    t_list *next_token;
    
    next_token = current->next;

    while (is_space(next_token))
        next_token = next_token->next;

    if (next_token && (next_token->command == PIPE))
        return (1);
    if (!next_token)
        return (1);
    return (0);
}

int check_consecutive_pipes(t_list *current)
{
    t_list *next_token;
    
    next_token = current->next;

    while (is_space(next_token))
        next_token = next_token->next;

    if (next_token && ft_strcmp(next_token->content, "|") == 0)
        return (1);
    
    if (!next_token)
        return (1);
    return (0);
}

int syntax(t_list **lst)
{
    if (syntax_consecutive_redirection(lst) || syntax_end_of_command(lst) 
         || syntax_redpipe(lst))
        return (error_message(1), 1);
    return (0);
}
