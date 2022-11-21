/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 14:54:36 by jbax          #+#    #+#                 */
/*   Updated: 2022/11/18 18:35:12 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_all.h"

void	*philo_main(void *list)
{
	t_philo_list	*plist;

	plist = (t_philo_list *)list;
	printf("i'm philo %d tread %d\n", plist->philo_id, *plist->sync);
	return (0);
}

int	create_thread(t_philo_list *plist)
{
	int	i;

	i = 0;
	while (plist && i < plist->time->n_philo)
	{
		if (error_table(pthread_create(&plist->thread_id, NULL, philo_main, plist)))
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
	ph.n_philo = ft_atoi(argv[1]);
	ph.t_death = ft_atoi(argv[2]);
	ph.t_eat = ft_atoi(argv[3]);
	ph.t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		ph.x_eat = ft_atoi(argv[5]);
	else
		ph.x_eat = -1;
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
	printf("philos-%d-death-%d-eat-%d-sleep-%d\n",
		ph.n_philo, ph.t_death, ph.t_eat, ph.t_sleep);
	pthread_join(plist->thread_id, 0);
	pthread_join(plist->next->thread_id, 0);
	sleep(2);
	return (0);
}
