/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:14:30 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/05 21:19:13 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_isdigit(char *str)
{
    int i;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return (1);
        }
        i++;
    }
    return (0);
}

// Checks that the input is only numbers

int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

// Checks if the program input is correct

int	check_valid_args(char **argv)
{
	if (ft_atoi(argv[1]) > PHILOSOPHERS_MAX || ft_atoi(argv[1]) <= 0
		|| check_arg_content(argv[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(argv[2]) <= 0 || check_arg_content(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || check_arg_content(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || check_arg_content(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_content(argv[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
    return (0);
}

// int check_input(int argc, char **argv)
// {
//     int i;
//     int philosophers;
    
//     i = 1;
//     if (argc != 5 && argc != 6)
//     {
//         printf("Usage: no of philos, time to die, time to eat, time to sleep, no of times to eat\n");
//         return (1);
//     }
//     while (i < argc)
//     {
//         if (ft_isdigit(argv[i]) == 1)
//         {   
//             printf("%s\n", argv[i]);
//             printf("Error: Argument %d (%s) must be an integer\n", i, argv[i]);
//             return (1);
//         }
//         philosophers = ft_atoi(argv[1]);
//         if (philosophers > PHILOSOPHERS_MAX || ft_atoi(argv[1]) <= 0)
//         {
//             printf("Error: Invalid no of philosophers\n");
//             return (1);
//         }
//         if (ft_atoi(argv[i]) <= 0)
//         {
//             printf("Error: Arguments must be positive integers\n");
//             return (1);
//         }
//         i++;
//     }
//     return (0);
// }


