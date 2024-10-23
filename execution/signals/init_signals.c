/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:43:28 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/21 12:22:29 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c_sig(int sig)
{
	if (g_signal == 1)
		return ;
	//rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}
static void	sig_quit_handler(int sig)
{
	(void)sig;
	if (!g_signal)
		return ;
	// rl_replace_line("", 0);
	// rl_redisplay();
	rl_on_new_line();
	// printf("\n");
	// ft_putnbr_fd(sig, 1);
	// ft_putstr_fd("\n", 1);
}

void	init_signl(void)
{
	signal(SIGINT, ctrl_c_sig);
	signal(SIGQUIT, sig_quit_handler);
	// if (catch_signals)
		// rl_catch_signals = 0;
	// signal(SIGQUIT, ctrl_int_sig);
}