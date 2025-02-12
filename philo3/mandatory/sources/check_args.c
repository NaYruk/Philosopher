/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:45:26 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/12 18:52:10 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	check_sup_int_max(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i] != '\0')
		count++;
	if (count > 10)
		return (true);
	return (false);
}

/* Function for check if each arg is really a number */

static bool	args_is_nbr(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
	}
	return (true);
}

/* 
	Function for check the validity of each arg :
*/

int	check_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i] != NULL)
	{
		if (check_sup_int_max(argv[i]) == true)
			return (write_an_error("Error ! An arg is > to INT_MAX !\n"));
		if (args_is_nbr(argv[i]) == false)
			return (write_an_error("Error ! An arg is not a Number !\n"));
	}
	return (0);
}
