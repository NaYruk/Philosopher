/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:48:04 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/18 17:36:59 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* 
	Main Function for the Philosophers 42 project :
	- Check if Argument is < 5 or > 6, because the number of meal for exit
		is an optionnal arg.
	- Write_an_error is a function for write everything in the error output.
	- Check_args is a function for check the validity of each args.
	- init_all is a function for initialize all structure for the suit.
	- create_threads is a function for create all threads.
	- free_data is a function for free all data malloc in init_data. 

*/

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	(void)argc;
	(void)argv;
	if (argc < 5 || argc > 6)
		return (write_an_error("Error ! nbr of args is invalid\n"));
	 if (check_args(argv) == 1)
		return (1);
 	if (init_all(&data, argv) == 1)
		return (1);
	if (create_threads(data) == 1)
		return (free_data(&data), 1);
	if (wait_threads(data) == 1)
		return (free_data(&data), 1);
	free_data(&data);
	return (0);
}
