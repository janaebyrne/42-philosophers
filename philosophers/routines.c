/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:53 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/10 21:44:23 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void   philo_think(t_philo *philo)
{
    print_timestamp(philo, "is thinking");
}

void    philo_sleep(t_philo *philo)
{
    print_timestamp(philo, "is sleeping");
    ft_usleep(philo->time_to_sleep);
}

void philo_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    print_timestamp(philo, "has taken a fork"); //right
    pthread_mutex_lock(philo->left_fork);
    print_timestamp(philo, "has taken a fork");
    philo->is_eating = 1;
    print_timestamp(philo, "is eating");
    pthread_mutex_lock(philo->eating_mutex);
    philo->last_meal = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->eating_mutex);
    usleep(philo->time_to_eat * 1000);
    philo->is_eating = 0;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}


void   *routine(void *arg)
{
    t_philo *philo;
    t_program *program;
    philo = (t_philo *)arg;
    if (philo->philo_count == 1)
    {
        return(one_philo_routine(philo));
        clean_up(NULL, program, philo->right_fork);
        return(NULL);
    }
    if (philo->id % 2 == 0)
    {
        ft_usleep(10);
    }
    while (!dead_checker(philo))
    {
        philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);
    }
    return(arg);
}

void	*one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_timestamp(philo, "has taken right fork");
    pthread_mutex_unlock(philo->right_fork);
	philo_sleep(philo);
	return (NULL);
}


