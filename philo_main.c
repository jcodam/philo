/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 14:54:36 by jbax          #+#    #+#                 */
/*   Updated: 2022/11/23 17:03:15 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_all.h"

int	run_time(struct timeval begin)
{
	struct timeval	new;
	int				i;
	int				t;

	gettimeofday(&new, 0);
	t = new.tv_sec - begin.tv_sec;
	i = ((new.tv_usec + (t * 1000000)) - begin.tv_usec) / 1000;
	return (i);
}

int	sleepy(struct timeval og, t_philo_list *plist, int time)
{
	struct timeval	base;
	int				i;
	int				j;

	i = 1;
	gettimeofday(&base, 0);
	while (i)
	{
		usleep(100);
		j = run_time(base);
		if (j >= time)
			i = 0;
		if (run_time(og) >= plist->last_meal + plist->time->t_death)
		{
			pthread_mutex_lock(plist->death);
			*plist->sync = -1;
			pthread_mutex_unlock(plist->death);
			printf("time; %d philo %d died\n", run_time(og), plist->philo_id);
			return (1);
		}
	}
	return (0);
}

void	*philo_main(void *list)
{
	t_philo_list	*plist;
	struct timeval	ogtime;
	int				i;

	plist = (t_philo_list *)list;
	gettimeofday(&ogtime, 0);
	i = 1;
	while (i != plist->time->x_eat + 1 && i)
	{
		pthread_mutex_lock(plist->fork_right);
		pthread_mutex_lock(plist->fork_left);
		printf("time; %d philo %d has taken right fork\n", run_time(ogtime), plist->philo_id);
		printf("time; %d philo %d has taken left fork\n", run_time(ogtime), plist->philo_id);
		plist->last_meal = run_time(ogtime);
		printf("time; %d philo %d is eating\n", plist->last_meal, plist->philo_id);
		sleepy(ogtime, plist, plist->time->t_eat);
		i++;
		pthread_mutex_unlock(plist->fork_left);
		pthread_mutex_unlock(plist->fork_right);
		printf("time; %d philo %d id sleeping\n", run_time(ogtime), plist->philo_id);
		sleepy(ogtime, plist, plist->time->t_sleep);
		printf("time; %d philo %d is thinking\n", run_time(ogtime), plist->philo_id);
	}
	pthread_mutex_lock(plist->death);
	*plist->sync += 1;
	if (*plist->sync == plist->time->n_philo)
		*plist->sync = -1;
	pthread_mutex_unlock(plist->death);
	return (0);
}

int	create_thread(t_philo_list *plist)
{
	int	i;

	i = 0;
	while (plist && i < plist->time->n_philo)
	{
		if (error_table(pthread_create(&plist->thread_id,
					0, philo_main, plist)))
		{
			put_s("create error\n");
			return (1);
		}
		plist = plist->next;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_time	ph;
	t_philo_list	*plist;
	int				i;
	int				j;

	if (check_args(argc))
		return (0);
	time_new(argc, argv, &ph);
	i = 0;
	j = 0;
	plist = 0;
	while (i < ph.n_philo)
	{
		i++;
		philo_addback(&plist, philo_new(&ph, i, &j));
	}
	if (create_thread(plist))
		return (0);
	while(1)
	{
		pthread_mutex_lock(plist->death);
		if (*plist->sync == -1)
			return (0);
		pthread_mutex_unlock(plist->death);
	}
	return (0);
}
