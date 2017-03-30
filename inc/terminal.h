/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:00:15 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 17:28:25 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include <stdint.h>

# define CAPS_CURSOR_UP		"UP"
# define CAPS_CURSOR_DOWN	"DO"
# define CAPS_CURSOR_LEFT	"LE"
# define CAPS_CURSOR_RIGHT	"RI"
# define CAPS_CLEAR_EOL		"ce"
# define CAPS_CLEAR_EOS		"cd"
# define CAPS_SCROLL_UP		"sf"

int		init_terminal_module(void);
int		terminal_start_raw_mode(void);
int		terminal_stop_raw_mode(void);
void	terminal_move_cursor(const char *cap, unsigned len);
void	terminal_execute_caps(const char *cap);
int		terminal_check_caps(void);

#endif
