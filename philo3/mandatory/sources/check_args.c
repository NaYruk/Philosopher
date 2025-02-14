/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:45:26 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/14 15:25:11 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	int	nbr;

	i = 0;
	while (argv[++i] != NULL)
	{
		if (args_is_nbr(argv[i]) == false)
			return (write_an_error("Error ! An arg is not a Number !\n"));
		nbr = convert_char_to_int(argv[i]);
		if (nbr == -1)
			return (write_an_error("Error ! An arg is > to INT_MAX !\n"));
		if (nbr == 0 && i == 1)
			return (write_an_error("Error ! Nbr of Philo == 0 !\n"));
	}
	return (0);
}
