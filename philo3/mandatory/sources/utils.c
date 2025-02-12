/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:48:37 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/12 18:49:10 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* It is a function for write a string in the error output. */

int	write_an_error(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = -1;
	while (str[++i] != '\0')
		write(2, &str[i], 1);
	return (1);
}

/* Is a function for convert a string in number */

int	convert_char_to_int(char *str)
{
	int	i;
	int	result;

	if (!str)
		return (1);
	i = -1;
	result = 0;
	while (str[++i] != '\0')
		result = result * 10 + (str[i] - '0');
	return (result);
}
