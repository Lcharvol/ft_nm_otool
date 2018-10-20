/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:23:30 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/19 15:30:03 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

struct section					*handle_segment_32(struct segment_command *sc,
		int n_sect)
{
	uint32_t					i;
	struct section				*sects;

	i = 0;
	sects = (void *)sc + sizeof(struct segment_command);
	while (i < sc->nsects)
	{
		if (i == (uint32_t)(n_sect))
			return (sects);
		sects = (void *)sects + sizeof(struct section);
		i++;
	}
	return (sects);
}

struct section_64				*handle_segment_64(
		struct segment_command_64 *sc, int n_sect)
{
	uint32_t					i;
	struct section_64			*sects;

	i = 0;
	sects = (void *)sc + sizeof(struct segment_command_64);
	while (i < sc->nsects)
	{
		if (i == (uint32_t)(n_sect - 1))
			return (sects);
		sects = (void *)sects + sizeof(struct section_64);
		i++;
	}
	return (sects);
}

struct section					*get_section_32(char *ptr, int n_sect)
{
	struct segment_command		*sc;
	struct mach_header			*header;
	uint32_t					i;
	uint32_t					ncmds;
	unsigned int				sec_summ;

	i = 0;
	header = (struct mach_header *)ptr;
	sc = (void *)ptr + sizeof(*header);
	sec_summ = 0;
	ncmds = header->magic == MH_MAGIC ? header->ncmds :
		swap_bigendian_littleendian(header->ncmds, sizeof(header->ncmds));
	while (i < ncmds)
	{
		if ((((void *)sc + sc->cmdsize) > ((void *)ptr + header->sizeofcmds))
			& (i < (ncmds - 2)))
			exit(0);
		if (sc->cmd == LC_SEGMENT && (sec_summ + sc->nsects) > n_sect)
			return (handle_segment_32(sc, n_sect - sec_summ - 1));
		sec_summ += sc->nsects;
		sc = (void *)sc + sc->cmdsize;
		i++;
	}
	return (NULL);
}

struct section_64				*get_section_64(char *ptr, int n_sect)
{
	struct segment_command_64	*sc;
	struct mach_header_64		*header;
	uint32_t					i;
	uint32_t					ncmds;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	sc = (void *)ptr + sizeof(*header);
	ncmds = header->magic == MH_MAGIC_64 ? header->ncmds :
		swap_bigendian_littleendian(header->ncmds, sizeof(header->ncmds));
	while (i < ncmds)
	{
		if ((((void *)sc + sc->cmdsize) > ((void *)ptr + header->sizeofcmds))
			& (i < (ncmds - 2)))
			exit(0);
		if (sc->cmd == LC_SEGMENT_64 && sc->nsects > 0)
			return (handle_segment_64(sc, n_sect));
		sc = (void *)sc + sc->cmdsize;
		i++;
	}
	return (NULL);
}

static unsigned char			get_sect_type_32(int n_sect, char *ptr,
		unsigned char type)
{
	struct section				*section;

	section = get_section_32(ptr, n_sect);
	ft_putstr("section->sectname: ");
	ft_putnbr(n_sect);
	ft_putendl(section->sectname);
	if (!ft_strcmp((char*)section->sectname, SECT_TEXT))
		return ((type & N_EXT) ? 'T' : 't');
	else if (!ft_strcmp((char*)section->sectname, SECT_BSS))
		return ((type & N_EXT) ? 'B' : 'b');
	else if (!ft_strcmp((char*)section->sectname, SECT_DATA))
		return ((type & N_EXT) ? 'D' : 'd');
	else
		return ((type & N_EXT) ? 'S' : 's');
}

static unsigned char			get_sect_type_64(int n_sect, char *ptr,
		unsigned char type)
{
	struct section_64			*section;

	section = get_section_64(ptr, n_sect);
	if (!ft_strcmp((char*)&section->sectname, SECT_TEXT))
		return ((type & N_EXT) ? 'T' : 't');
	else if (!ft_strcmp((char*)&section->sectname, SECT_BSS))
		return ((type & N_EXT) ? 'B' : 'b');
	else if (!ft_strcmp((char*)&section->sectname, SECT_DATA))
		return ((type & N_EXT) ? 'D' : 'd');
	else
		return ((type & N_EXT) ? 'S' : 's');
}

unsigned char					get_type_32(char *ptr, unsigned char type,
		int n_sect)
{
	if (n_sect == NO_SECT)
	{
		if ((type & N_TYPE) == N_UNDF)
			return ('U');
		else if ((type & N_TYPE) == N_ABS)
			return ((type & N_EXT) ? 'A' : 'a');
	}
	else if (n_sect != NO_SECT)
		return (get_sect_type_32(n_sect, ptr, type));
	return ('?');
}

unsigned char					get_type_64(char *ptr, unsigned char type,
		int n_sect)
{
	if (n_sect == NO_SECT)
	{
		if ((type & N_TYPE) == N_UNDF)
			return ('U');
		else if ((type & N_TYPE) == N_ABS)
			return ((type & N_EXT) ? 'A' : 'a');
	}
	if ((type & N_TYPE) == N_SECT)
		return (get_sect_type_64(n_sect, ptr, type));
	return ('?');
}
