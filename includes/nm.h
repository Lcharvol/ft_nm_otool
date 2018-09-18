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
# include </usr/include/mach-o/fat.h>
# include </usr/include/mach/machine.h>


# define NM "NM"
# define OTOOL "OTOOL"
# define MY_CPU_TYPE CPU_TYPE_X86_64
typedef struct			s_env
{
	uint32_t				magic_number;
	char					*exec_type;
	char					*file_name;
	void					*start;
    int						arch_type;
    unsigned int            is_swap;
	struct mach_header_64	*header_64;
	struct mach_header		*header_32;
	struct fat_header		*header_fat;
}   						t_env;

int	                    print_usage(void);
int                     open_exit(char *file_name);
int                     fstat_exit(void);
int                     mmap_munmap_exit(char *type);
void                    handle_header_64(char *ptr, t_env *env);
void                    handle_header_32(char *ptr, t_env *env);
void					handle_fat_header(char *ptr, t_env *env);
void					handle_text_section_64(char *ptr, t_env *env);
void					handle_text_section_32(char *ptr, t_env *env);
void					print_text_section_32(struct section	*sects, char *ptr, t_env *env);
void					print_text_section_64(struct section_64	*sects, char *ptr, t_env *env);
uint64_t				swap_bigendian_littleendian(uint64_t number, size_t sizeoff);
void					handle_fat_arch(char *ptr, t_env *env);
void					otool(char *ptr, t_env *env);

#endif
