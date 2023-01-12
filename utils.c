/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 22:23:58 by mafissie          #+#    #+#             */
/*   Updated: 2022/09/25 20:40:11 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philolib.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i++])
		;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int			neg;
	long int	nb;

	neg = 1;
	nb = 0;
	while (*nptr && (*nptr == '\r' || *nptr == '\f' || *nptr == '\v'
			|| *nptr == '\n' || *nptr == ' ' || *nptr == '\t'))
		nptr++;
	if (*nptr == '-')
		ft_error("Nbr neg !", NULL);
	else if (*nptr == '+')
		nptr++;
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		nb = (nb * 10) + *(nptr++) - 48;
		if ((((nb) > INT_MAX) || ((nb * neg) < INT_MIN)))
			ft_error("nbr over !", NULL);
	}
	return (nb * neg);
}

void	ft_digit(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9') && (s[i] != '-' && s[i] != 32))
			ft_error("Bad args !", NULL);
		if (s[i] == '-')
			if (s[i + 1] < '0' || s[i + 1] > '9')
				ft_error("Bad args !", NULL);
		i++;
	}
}
