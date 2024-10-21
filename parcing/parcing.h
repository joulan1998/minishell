/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:58:15 by yosabir           #+#    #+#             */
/*   Updated: 2024/10/21 11:22:37 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCING_H
# define PARCING_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct enviroment
{
    char **env;
} env_struct;

typedef struct set_list
{
    int input;
    int output;
    char **args;
    struct set_list *next;
}   set_args;

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
    SPACEE,
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
size_t  ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);

// helper function 2
size_t	ft_strlen(const char *str);
char	*ft_itoa(int n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	*ft_memcpy(void *dst, const void *src, size_t n);



// parcing functiong
t_list  *parsing(char *str);
int     parse_word(char *str, int i, t_list **lst);
int     parse_spaces(char *str, int i, t_list **lst);
void    classing(t_list **lst);

// syntax functions
int     check_redirection_followed_by_pipe(t_list *lst);
int     check_consecutive_pipes(t_list *lst);
int     is_space(t_list *token);
int     is_valid_next(t_list *token);
int     syntax_redpipe(t_list **lst);
int     syntax_consecutive_redirection(t_list **lst);
int     syntax_end_of_command(t_list **lst);
int     syntax_quotes(t_list **lst);
int     syntax(t_list **lst);
int     error_message();

//expand functions
char *get_var_value(char *str);

//heredoc functions
int create_unique_heredoc_file();

//openingfiles / handling red
int pipe_counter(t_list **lst);
void handle_redirections(t_list *token, set_args *cmd_args);
void add_arg_to_set_args(set_args *cmd_args, char *new_arg);
void storing_args(t_list **current, set_args *cmd_args);

//settinglist
set_args *settingargs(t_list **lst);


#endif