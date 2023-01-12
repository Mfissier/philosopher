/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 22:23:51 by mafissie          #+#    #+#             */
/*   Updated: 2022/09/15 23:30:45 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philolib.h" 

void	putserr(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	ft_error(char *str, void *pcontent)
{
	if (pcontent != NULL)
		free(pcontent);
	putserr(str);
	exit(2);
}

void	as_error_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac == 5 || ac == 6)
	{
		while (i < ac)
		{
			ft_digit(av[i]);
			ft_atoi(av[i]);
			i++;
		}
	}
	else
		ft_error("Incorrect args !", NULL);
}
