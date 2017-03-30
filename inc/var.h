/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:00:16 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 17:00:27 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_H
# define VAR_H

void			var_init(char **environ);
void			var_shutdown(void);
void			var_clear(void);
int				var_set(const char *name, const char *value);
int				var_unset(const char *name);
int				var_get(const char *name, const char **value);
char *const		*var_get_environ(void);

#endif
