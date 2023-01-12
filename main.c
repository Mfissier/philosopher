/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:00:45 by mafissie          #+#    #+#             */
/*   Updated: 2022/10/02 18:29:00 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philolib.h" 
#include <unistd.h>

int	main(int ac, char **av)
{
	t_content	content;

	as_error_args(ac, av);
	init_data(&content, ac, av);
	gettimeofday(&content.timeout, NULL);
	init_mutex(&content);
	if (content.nbr_phil == 1)
	{
		print_thread(&content, 0, 3);
		print_thread(&content, 0, 0);
		usleep(content.t_death * 1000);
		print_thread(&content, 0, 4);
	}
	else
	{
		gettimeofday(&content.timeout, NULL);
		init_mutex(&content);
		launch_philosophers(&content);
		destroy_mutex(&content);
	}
	return (0);
}
