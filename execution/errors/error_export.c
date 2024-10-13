/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:23:49 by ael-garr          #+#    #+#             */
/*   Updated: 2024/09/28 17:33:28 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int ft_error(/*t_minishell *data,*/char	*first, t_tags message)
{
	ft_putstr_fd("minishell: ",2);
	ft_putstr_fd(first,2);
	if (message == COMMAND_NOT_FOUND)
		ft_putstr_fd(": command not found\n",2); 
	return (0);
}