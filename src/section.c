#include "../includes/nm.h"

void	handle_segment_64(char *ptr, struct segment_command_64	*sc, t_env *env)
{
	uint32_t 					i;
	struct section_64		*sects;

	i = 0;
	sects = (void *)sc +sizeof(struct segment_command_64);
	while(i < sc->nsects)
	{
		if(ft_strcmp(sects->sectname,SECT_TEXT) == 0)
			print_text_section_64(sects, ptr, env);
		sects = (void *)sects + sizeof(struct section_64);
		i++;
	}
}

void	handle_segment_32(char *ptr, struct segment_command	*sc, t_env *env)
{
	uint32_t 					i;
	struct section		*sects;

	i = 0;
	sects = (void *)sc +sizeof(struct segment_command);
	while(i < sc->nsects)
	{
		if(ft_strcmp(sects->sectname,SECT_TEXT) == 0)
			print_text_section_32(sects, ptr, env);
		sects = (void *)sects + sizeof(struct section_64);
		i++;
	}
}

void	handle_text_section_64(char *ptr, t_env *env)
{
	struct segment_command_64	*sc;
	struct mach_header_64	*header;
	uint32_t 					i;

	i = 0;
	header = env->header_64;
	sc = (void *)ptr + sizeof(*header);
	while(i < header->ncmds)
	{
		if(sc->cmd == LC_SEGMENT_64)
			handle_segment_64(ptr, sc, env);
		i++;
		sc = (void *)sc + sc->cmdsize;
	}
}

void						handle_text_section_32(char *ptr, t_env *env)
{
	
	struct segment_command	*sc;
	struct mach_header		*header;
	uint32_t				i;
	uint32_t				ncmds;

	i = 0;
	header = env->header_32;
	if(header->magic == MH_CIGAM)
		return;
	sc = (void *)ptr + sizeof(*header);
	ncmds = header->magic == MH_CIGAM ? header->ncmds : swap_bigendian_littleendian(header->ncmds, sizeof(header->ncmds));
	ft_printf("ncmds: %d\n", ncmds);
	while(i < ncmds)
	{
		ft_printf("CA PSSESFEFWEF\n");
		if(sc->cmd == LC_SEGMENT)
			handle_segment_32(ptr, sc, env);
		i++;
		sc = (void *)sc + sc->cmdsize;
	}
}