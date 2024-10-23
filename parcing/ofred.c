/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ofred.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:11:35 by yosabir           #+#    #+#             */
/*   Updated: 2024/10/23 12:51:05 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

int pipe_counter(t_list **lst)
{
    t_list *current;
    int     i;
    
    current = *lst;
    i = 0;
    while(current)
    {
        if(current->command == PIPE)
            i++;
        current = current->next;
    }
    return (i + 1);
}
int open_file(const char *filename, int flags) 
{
    int fd;
    
    fd = open(filename, flags);
    if (fd == -1)
    {
        perror("Error opening file");
        return (-1);
    }
    return (fd);
}

t_list *skip_spaces(t_list *token) 
{
    while (token && token->command == SPACEE)
        token = token->next;
    return token;
}

void handle_redirections(t_list *token, set_args *cmd_args, t_list *environement) 
{
    cmd_args->input = 0;
    cmd_args->output = 1;

    if (token->command == RD_OUT) 
    {
        if (cmd_args->output != 1)
            cmd_args->output = close(cmd_args->output);
        token = skip_spaces(token->next);
        if(!token)
            return;
        else if (token)
            cmd_args->output = open_file(token->content, O_CREAT | O_RDWR | O_TRUNC | 0666);
        
    }
    else if (token->command == RD_IN) 
    {
        token = skip_spaces(token->next);
        if (!token)
            return;
        else if (token)
            cmd_args->input = open_file(token->content, O_RDONLY);
    }
    else if (token->command == APPEND) 
    {
        if (cmd_args->output != 1)
            cmd_args->output = close(cmd_args->output);
        token = skip_spaces(token->next);
        if (!token)
            return;
        else if (token)
            cmd_args->output = open_file(token->content, O_CREAT | O_WRONLY | O_APPEND | 0666);
    }
    else if (token->command == HEREDOC)
    {
        token = skip_spaces(token->next);
        if (!token)
            return;
        handle_herdoc(cmd_args->input, token->content, environement, token);
    }
}