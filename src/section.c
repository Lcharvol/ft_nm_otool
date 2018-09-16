#include "../includes/nm.h"

void	handle_text_section_64(char *ptr)
{
	struct segment_command_64	*sc;
	struct section_64		*sects;
	struct mach_header_64	*header;
	uint32_t 					i;
	uint32_t				ncmds;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	sc = (void *)ptr + sizeof(*header);
	while(i < ncmds)
	{
		if(sc->cmd == LC_SEGMENT_64)
		{
			i = 0;
			sects = (void *)sc +sizeof(struct segment_command_64);
			while(i < sc->nsects)
			{
				if(ft_strcmp(sects->sectname,SECT_TEXT) == 0)
					print_text_section_64(sects, ptr);
				sects = (void *)sects + sizeof(struct section_64);
				i++;
			}
		};
		i++;
		sc = (void *)sc + sc->cmdsize;
	}
}

void	handle_text_section_32(char *ptr)
{
	
	struct segment_command	*sc;
	struct section		*sects;
	struct mach_header	*header;
	uint32_t 					i;
	uint32_t				ncmds;

	i = 0;
	header = (struct mach_header *)ptr;
	ncmds = header->ncmds;
	sc = (void *)ptr + sizeof(*header);

	while(i < ncmds)
	{
		if(sc->cmd == LC_SEGMENT)
		{
			i = 0;
			sects = (void *)sc +sizeof(struct segment_command);
			while(i < sc->nsects)
			{
				if(ft_strcmp(sects->sectname,SECT_TEXT) == 0)
					print_text_section_32(sects, ptr);
				sects = (void *)sects + sizeof(struct section);
				i++;
			}
		};
		i++;
		sc = (void *)sc + sc->cmdsize;
	}
}