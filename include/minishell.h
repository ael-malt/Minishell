/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:10:09 by lazanett          #+#    #+#             */
/*   Updated: 2023/09/19 11:11:25 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>



//---------------------------EXECUTE.C-------------------------------------//

//---------------------------------------------------------------------//

//------------------------------INIT.C----------------------------------//
void			ft_init_struc(t_struc *nb, char **av);
int				alloc_tabs(t_struc *nb);
int				init_forks(t_struc *nb);
int				init_philos(t_struc *nb);
long long		ft_atoi(const char *str);
//----------------------------------------------------------------------//

//------------------------------PARSING.C----------------------------------//

//---------------------------------------------------------------------//

//----------------------------THREAD.C----------------------------------//
void			create_thread(t_struc *nb);
void			join_thread(t_struc *nb, pthread_t tid);
void			*monito(void *data);
int				meal_check(t_struc *temp);
int				philo_dead(t_struc *nb);
//----------------------------------------------------------------------//

//------------------------------TIME.C----------------------------------//
long long int	get_time(t_struc *nb);
long long int	ft_usleep(long long int time, t_struc *nb);
//----------------------------------------------------------------------//

//---------------------------UTILS.C------------------------------------//
void			ft_write(t_phil *philo, char *str);
void			ft_free(t_struc	*nb);
void			end(t_struc *nb);
void			ft_error(char *s, int fd, t_struc *nb);
//---------------------------------------------------------------------//

#endif
