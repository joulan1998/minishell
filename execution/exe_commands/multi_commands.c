/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:43:06 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/16 19:39:20 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// void initialize_fds(int ***table, int n) {
//     int i;

//     // Allocate memory for the table of pointers
//     *table = malloc(n * sizeof(int *));
//     if (!(*table)) {
//         perror("malloc");
//         exit(69);
//     }

//     for (i = 0; i < n; i++) {
//         (*table)[i] = malloc(2 * sizeof(int)); // Allocate space for 2 file descriptors
//         if (!(*table)[i]) {
//             perror("malloc");
//             // Clean up previously allocated memory before exiting
//             for (int j = 0; j < i; j++) {
//                 free((*table)[j]);
//             }
//             free(*table);
//             exit(56);
//         }
//     }
// }
int initialize_fds(int ***table, int n)
{
    int i;

	i = 0;
    *table = malloc(n * sizeof(int *));
    if (!(*table))
		return (-1);
    while (i < n)
	{
		(*table)[i] = malloc(2 * sizeof(int));
        if (!(*table)[i])
			return (-1);
		i++;
    }
	return (i);
}
void close_fd(int *n)
{
    if (!n) return;
    while (*n > 0)
	{
        // printf("the >%d< is closed!\n", *n);
        close(*n);
        n++;
    }
}

void multi_util(t_minishell *data, char **cmd, int read_fd, int print, int *to_close)
{
    int fork_res = fork();
    if (fork_res == -1)
	{
        perror("forking");
        return;
    }
    if (fork_res == 0) {
        close_fd(to_close);
        if (read_fd != 0)
		{
            if (dup2(read_fd, 0) == -1) perror("dup2 read_fd");
            close(read_fd);
        }
        if (print != 1)
		{
            if (dup2(print, 1) == -1) perror(cmd[0]);
            close(print);
        }
        // char **args = ft_split(cmd, ' ');
        execve(check_acces(data, cmd[0]), cmd, data->env);
        perror("child execve");
		// ft_free_table(&args);
        exit(EXIT_FAILURE); // Exit if execve fails
    }
	else
        wait(NULL);
}

int multi_commands(t_minishell *data)
{
    int size;
    int **pipe_fd;
	int i;
	set_args *args;
	args = data->commands;
	size = ft_lstsize_c(args);

	if (initialize_fds(&pipe_fd, size-1) == -1)
		return (-1);
	i = 0;
    while (i < (size))
	{
        if ((i < size - 1))
		{
			if (pipe(pipe_fd[i]) != 0)
				return(perror("pipe error"), -1);
        }
        if (i == 0)
            multi_util(data, args->args, 0, pipe_fd[0][1], (int[]){pipe_fd[0][0], -1});
        else if (i == (size -1))
            multi_util(data, args->args, pipe_fd[i - 1][0], 1, (int[]){pipe_fd[i - 1][1], -1});
        // else if ((i < size - 1) && (i > 0))
		else
            multi_util(data, args->args, pipe_fd[i - 1][0], pipe_fd[i][1], (int[]){/*pipe_fd[i-1][1], pipe_fd[i][0],*/ -1}); 
        if (i > 0)
            close(pipe_fd[i - 1][0]);
        if (i < size - 1)
            close(pipe_fd[i][1]);
		i++;
		args = args->next;
    }
    // Close any remaining pipe ends (cleanup)
    for (int j = 0; j < size - 1; j++) {
        close(pipe_fd[j][0]);
        close(pipe_fd[j][1]);
    }

    return 0;
}




// void close_fd(int *n)
// {
// 	int *local;
// 	if (!n)
// 		return;
// 	local = n;
// 	while (*local > 0)
// 	{
// 		printf("the >%d< is closed!\n",*local);
// 		close(*local);
// 		local++;
// 	}
// }

// void	multi_util(t_minishell *data, char *cmd, int read_fd, int print, int *to_close)
// {
// 	int fork_res;
	
// 	fork_res = fork();
// 	if (fork_res == -1)
// 		perror("forking");
// 	if (fork_res == 0)
// 	{	
// 		close_fd(to_close);
// 		if (read_fd != 0)
// 		{
// 			dup2(read_fd,0);
// 			close(read_fd);
// 		}
// 		if (print != 1)
// 		{
// 			dup2(print, 1);
// 			close(print);
// 		}
// 		execve(check_acces(data,ft_split(cmd ,' ')[0]),ft_split(cmd , ' '), data->env);
// 		perror("child");
// 	}
// 	else
// 		wait(NULL);
// }

// int multi_commands(t_minishell *data)
// {
// 	int	size;
// 	int i;
// 	int pipe_fd[4][2];

// 	i = 0;
// 	size = count_table_entries(data->commands);
// 	while (i < size)
// 	{
// 		if (i == 0)
// 		{
// 			int p_x = pipe(pipe_fd[i]);
// 			if (p_x == -1)
// 				perror("first_pipe error");
// 			multi_util(data, data->commands[0], 0, pipe_fd[0][1], (int []){pipe_fd[0][0], -1}); 
// 		}
// 		else if (i < (size - 1))
// 		{
// 			int p = pipe(pipe_fd[i]);
// 			if (p == -1)
// 				perror("second pipe");
// 			multi_util(data, data->commands[i], pipe_fd[i-1][0], pipe_fd[i][1], (int[]) {pipe_fd[i-1][1], pipe_fd[i][0], -1});
// 		}
// 		// // else
// 		else if (i == (size -1))
// 			multi_util(data, data->commands[i], pipe_fd[i-1][0], 1,(int[]){pipe_fd[i-1][1], -1});
// 		i++;
// 	}
// 	close(pipe_fd[0][0]);
// 	close(pipe_fd[0][1]);
// 	// close(pipe_fd[1][0]);
// 	// close(pipe_fd[1][1]);
// 	// int status = 0;
// 	// while (waitpid(-1, &status, 0) != -1)
// 	// 	;
// 	return (0);
// }
