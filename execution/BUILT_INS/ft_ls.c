/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:08:13 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/12 18:37:02 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_ls(t_minishell *data)
{
	struct  dirent *dirread;
	DIR *dir;
	if (data->commands->args[1])
		dir = opendir(data->commands->args[1]);
	else 
		dir = opendir(".");
	dirread = readdir(dir);
	while (dirread)
	{
		printf("%s\n",dirread->d_name);
	}
	
	return (0);
	
	
}