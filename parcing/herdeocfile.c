/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdeocfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:11:29 by yosabir           #+#    #+#             */
/*   Updated: 2024/10/23 12:51:21 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

t_heredoc_info	open_create_herdoc_file(void)
{
	int				fd;
	int				i;
	char			*heredoc_name;
	char			*num;
	t_heredoc_info	info;

	i = 1;
	while (1)
	{
		num = ft_itoa(i);
		heredoc_name = ft_strjoin(ft_strdup("/tmp/heredoc"), num);
		free(num);
		if (access(heredoc_name, F_OK) == -1)
			break ;
		i++;
		free(heredoc_name);
	}
	fd = open(heredoc_name, O_CREAT | O_RDWR | O_APPEND, 0666);
	info.file_name = heredoc_name;
	info.input = fd;
	return (info);
}
void	handle_herdoc(int input, char *del, t_list *env, t_list *token)
{
	char			*line;
	char			*result;
	int				dont_expand;
	t_heredoc_info	info;

	dont_expand = 0;
	if (token->command == D_QUOTE)
		dont_expand = 1;
	info = open_create_herdoc_file();
	line = readline("> ");
	if (!line)
		return (free(info.file_name), free(line));
	while (!ft_strcmp(line, del))
	{
		result = expand_here_doc(line, env, dont_expand);
		write(info.input, result, ft_strlen(result));
		write(info.input, "\n", 1);
		free(result);
		line = readline("> ");
		if (!line)
			return (free(info.file_name), free(line));
	}
	(close(info.input), input = open(info.file_name, O_RDONLY));
	(free(info.file_name), free(line));
}

