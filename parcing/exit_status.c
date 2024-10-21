/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:31:12 by yosabir           #+#    #+#             */
/*   Updated: 2024/10/21 16:31:14 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	exit_status(int new_stat, int set)
{
	static int	status;

	if (set)
		status = new_stat;
	return (status);
}