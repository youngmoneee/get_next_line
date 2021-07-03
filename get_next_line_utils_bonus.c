/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 01:10:48 by youngpar          #+#    #+#             */
/*   Updated: 2021/07/03 19:37:32 by youngpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int			ft_strlen(char *src)
{
	int		idx;

	idx = 0;
	while (src[idx])
		idx++;
	return (idx);
}

char		*ft_strdup(char *src)
{
	int		idx;
	char	*ret;

	idx = 0;
	if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (0);
	while (src[idx])
	{
		ret[idx] = src[idx];
		idx++;
	}
	ret[idx] = '\0';
	return (ret);
}
