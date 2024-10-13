/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:43:28 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/07 19:08:57 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c_sig(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}
void	ctrl_int_sig(int sig)
{
	(void) sig;
}

void	init_signl(void)
{
	signal(SIGINT, ctrl_c_sig);
	// signal(SIGQUIT, ctrl_int_sig);
}