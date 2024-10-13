/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:58:15 by yosabir           #+#    #+#             */
/*   Updated: 2024/10/06 16:17:32 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCING_H
# define PARCING_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"


typedef enum s_type
{
    BUILT_IN,
    SIMPLE_COMMAND,
} t_type;

typedef enum s_command
{
    RD_IN,
    RD_OUT,
    APPEND,
    HEREDOC,
    S_QUOTE,
    D_QUOTE,
    PIPE,
    VAR,
    // SPACE,
    WORD,
} t_command;

typedef struct s_list
{
    char        *content;
    t_type      type;
    t_command   command;
    struct s_list  *next;
} t_list;

// list utils
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void *));

// helper funcions
int     ft_strcmp(char *s1, char *s2);
// size_t  ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	*ft_strdup(const char *s);


// parcing functiong
t_list  *parsing(char *str);
int     parse_word(char *str, int i, t_list **lst);
int     parse_spaces(char *str, int i, t_list **lst);
void    classing(t_list **lst);

// syntax functions
int    check_redirection_followed_by_pipe(t_list *lst);
int    check_consecutive_pipes(t_list *lst);
int    is_space(t_list *token);
int    is_valid_next(t_list *token);
int    syntax1(t_list **lst);
int    syntax2(t_list **lst);
int    syntax3(t_list **lst);
int    syntax4(t_list **lst);
int    syntax(t_list **lst);
int    error_message();





#endif