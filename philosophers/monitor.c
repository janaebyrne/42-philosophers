/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:55:02 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/10 21:43:05 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Function to print a timestamped message
void print_timestamp(t_philo *philo, char *action)
{
    long timestamp;
    
    if (*philo->dead_flag == 1) 
    {
        pthread_mutex_unlock(philo->output_mutex);
        return; // Stop printing if a philosopher has already died
    }
    pthread_mutex_lock(philo->output_mutex);
    timestamp = get_time() - philo->start_time; // Calculate the elapsed time
    printf("%ld %d %s\n", timestamp, philo->id, action);
    pthread_mutex_unlock(philo->output_mutex);
}

int	this_philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->eating_mutex);
	if (get_time() - philo->last_meal >= time_to_die
		&& philo->is_eating== 0)
		return (pthread_mutex_unlock(philo->eating_mutex), 1);
	pthread_mutex_unlock(philo->eating_mutex);
	return (0);
}

int check_if_any_died(t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos[0].philo_count)
    {
        if (this_philo_dead(&philos[i], philos[i].time_to_die))
        {
            print_timestamp(philos, "died");
            pthread_mutex_lock(philos[i].dead_mutex);
            *philos[i].dead_flag = 1;
            pthread_mutex_unlock(philos[i].dead_mutex);
            return (1);
        }
        i++;
    }
    return (0);
}

int check_all_ate(t_philo *philos)
{
    int i;
    int finished;
    
    i = 0;
    finished = 0;
    if (philos[0].num_times_to_eat == -1)
        return (0);
    while (i < philos[0].philo_count)
    {
        pthread_mutex_lock(philos[i].eating_mutex);
        if (philos[i].meals_eaten >= philos[0].num_times_to_eat)
            finished++;
        pthread_mutex_unlock(philos[i].eating_mutex);
        i++;
    }
    if (finished == philos[0].philo_count)
    {
        pthread_mutex_lock(philos[0].dead_mutex);
        *philos[0].dead_flag = 1;
        pthread_mutex_unlock(philos[0].dead_mutex);
        return (1);
    }
    return (0);
}

void *monitor(void *arg)
{
    t_philo *philos;
    
    philos = (t_philo *)arg;
    while (1)
    {
        if (check_if_any_died(philos) == 1|| check_all_ate(philos) == 1)
            break;
        usleep(50);
    }
    return (arg);
}