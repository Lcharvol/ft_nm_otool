/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 02:21:28 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/09 17:01:58 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <sys/mman.h>
#include <sys/stat.h> 
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <stdlib.h>

# define ARCH_64 64
# define ARCH_32 32
typedef struct			s_env
{
	uint32_t				magic_number;
	char					*file_name;
	void					*start;
    int						arch_type;
    unsigned int            is_swap;
	struct mach_header_64	*header_64;
	struct mach_header		*header_32;
}   						t_env;

int	                    print_usage(void);
int                     open_exit(char *file_name);
int                     fstat_exit(void);
int                     mmap_munmap_exit(char *type);
void                    handle_header_64(char *ptr, t_env *env);
void                    handle_header_32(char *ptr, t_env *env);

#endif
