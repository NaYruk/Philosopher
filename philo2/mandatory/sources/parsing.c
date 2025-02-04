/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:23:50 by marcmilliot       #+#    #+#             */
/*   Updated: 2025/02/04 11:58:15 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Function for check if the number is > to INT_MAX */

static bool	check_char_nbr_sup_ten(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
	{
		i++;
	}
	if (i > 10)
		return (true);
	else
		return (false);
	
}

/* Function for check if args is not a number */

static bool	arg_is_not_a_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (true);
		i++;
	}
	return (false);
}

/* Function for check the validity of arguments */

int	parse_args(char **argv)
{
	int	i;
	
	i = 0;
	while (argv[++i] != NULL)
	{
		if (check_char_nbr_sup_ten(argv[i]) == true)
			return (error_args());
		if (arg_is_not_a_nbr(argv[i]) == true)
			return (error_args());
	}
	return (0);
}
