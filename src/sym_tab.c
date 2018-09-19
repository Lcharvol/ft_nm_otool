#include "../includes/nm.h"

static void				handle_ran_lib(t_env *env, char *ptr, uint32_t size, struct ranlib	*lib)
{
	uint32_t		i;
	struct ar_hdr	*header;
	void			*tmp_ptr;
	void			*prev_tmp_ptr;
	
	i = -1;
	size /= sizeof(struct ranlib);
    ft_printf("Archive : %s\n", env->file_name);
	while(++i < size)
	{
		header = (void*)ptr + lib[i].ran_off;
        env->ar_name = (void*)header + sizeof(*header);
		tmp_ptr = (void*)header + sizeof(*header) + ft_atoi(&header->ar_name[3]);
		if(tmp_ptr != prev_tmp_ptr)
			otool(tmp_ptr, env);
		prev_tmp_ptr = tmp_ptr;
	};
}

static void				handle_ran_lib_64(t_env *env, char *ptr, uint64_t size, struct ranlib_64	*lib)
{
	uint32_t		i;
	struct ar_hdr	*header;
	void			*tmp_ptr;
	void			*prev_tmp_ptr;
	
	i = -1;
	size /= sizeof(struct ranlib);
	ft_printf("Archive : %s\n", env->file_name);
	while(++i < size)
	{
		header = (void*)ptr + lib[i].ran_off;
		env->ar_name = (void*)header + sizeof(*header);
		tmp_ptr = (void*)header + sizeof(*header) + ft_atoi(&header->ar_name[3]);
		if(tmp_ptr != prev_tmp_ptr)
			otool(tmp_ptr, env);
		prev_tmp_ptr = tmp_ptr;
	};
}

void				handle_sym_tab(char *ptr, t_env *env)
{
	void			*new_ptr;
	uint32_t		*size;
	struct ar_hdr	*header;

	header = (void *)ptr + SARMAG;
	new_ptr = (void *)header + sizeof(* header);
	size = (uint32_t *)((void *)new_ptr + 20);
	if (ft_strcmp(new_ptr, SYMDEF) == 0 ||
			ft_strcmp(new_ptr, SYMDEF_SORTED) == 0)
		handle_ran_lib(env, ptr, size[0], (void *)new_ptr + 24);
	else if (ft_strcmp(new_ptr, SYMDEF_64) == 0 ||
			ft_strcmp(new_ptr, SYMDEF_64_SORTED) == 0)
		handle_ran_lib_64(env, ptr, size[0], (void *)new_ptr + 24);
}