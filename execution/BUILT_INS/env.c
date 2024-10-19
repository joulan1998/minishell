/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:06:33 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/18 22:31:25 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_minishell *data)
{
	t_environ	*local;

	local = data->env_lst;
	while (local)
	{
		printf("%s=%s\n", local->var, local->value);
		local = local->next;
	}
	return (0);
}
