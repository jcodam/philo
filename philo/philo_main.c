/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 14:54:36 by jbax          #+#    #+#                 */
/*   Updated: 2022/12/16 17:49:06 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_all.h"

static void	*philo_stomach(void *list)
{
	t_philo_list	*plist;

	plist = (t_philo_list *)list;
	usleep(900);
	while (1)
	{
		pthread_mutex_lock(plist->time_mutex);
		if (plist->last_meal == -1)
		{
			pthread_mutex_unlock(plist->time_mutex);
			return (0);
		}
		if (to_late_for_dinner(plist->ogtime, plist, 0, 0))
		{
			pthread_mutex_unlock(plist->time_mutex);
			return (0);
		}
		pthread_mutex_unlock(plist->time_mutex);
		usleep(5000);
	}
	return (0);
}

static int	eet_sleep_think_repeat(int i, t_philo_list *plist,
			struct timeval ogtime)
{
	while (i != plist->time->x_eat + 1 && i)
	{
		pthread_mutex_lock(plist->fork_right);
		pthread_mutex_lock(plist->fork_left);
		if (to_late_for_dinner(ogtime, plist, "has taken a fork\n", 1))
			return (0);
		if (to_late_for_dinner(ogtime, plist, "has taken a fork\n", 1))
			return (0);
		if (to_late_for_dinner(ogtime, plist, "is eating\n", 1))
			return (0);
		pthread_mutex_lock(plist->time_mutex);
		plist->last_meal = run_time(ogtime);
		pthread_mutex_unlock(plist->time_mutex);
		if (sleepy(ogtime, plist, plist->time->t_eat, 1))
			return (0);
		i++;
		unlock_fork(plist);
		if (to_late_for_dinner(ogtime, plist, "is sleeping\n", 0))
			return (0);
		if (sleepy(ogtime, plist, plist->time->t_sleep, 0))
			return (0);
		if (to_late_for_dinner(ogtime, plist, "is thinking\n", 0))
			return (0);
	}
	return (1);
}

void	*philo_main(void *list)
{
	t_philo_list	*plist;
	int				i;
	pthread_t		sub_tread;

	plist = (t_philo_list *)list;
	if (pthread_create(&sub_tread,
			0, philo_stomach, plist))
	{
		put_s("create error\n");
		return (0);
	}
	pthread_mutex_lock(plist->time_mutex);
	gettimeofday(&plist->ogtime, 0);
	i = 1;
	plist->last_meal = run_time(plist->ogtime);
	pthread_mutex_unlock(plist->time_mutex);
	if (!(plist->philo_id % 2))
		usleep(900);
	eet_sleep_think_repeat(i, plist, plist->ogtime);
	pthread_mutex_lock(plist->time_mutex);
	plist->last_meal = -1;
	pthread_mutex_unlock(plist->time_mutex);
	pthread_join(sub_tread, 0);
	return (0);
}

static void	wait_to_join(t_philo_list *plist)
{
	int	i;

	i = 0;
	while (i < plist->time->n_philo)
	{
		pthread_join(plist->thread_id, 0);
		if (plist->next)
			plist = plist->next;
		i++;
	}
}

// void	leaks(void)
// {
// 	system("leaks -q philo");
// }
// 	atexit(&leaks);

int	main(int argc, char **argv)
{
	t_philo_time	ph;
	t_philo_list	*plist;
	int				i;
	int				j;

	if (check_args(argc))
		return (0);
	if (time_new(argc, argv, &ph))
		return (0);
	i = 0;
	j = 0;
	plist = 0;
	while (i < ph.n_philo)
	{
		i++;
		philo_addback(&plist, philo_new(&ph, i, &j));
		if (!plist)
			return (0);
	}
	if (create_thread(plist))
		return (0);
	wait_to_join(plist);
	while (plist)
		philo_del(&plist);
	return (0);
}
