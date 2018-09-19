#include "../includes/nm.h"

int						is_corrupted_64(struct segment_command_64	*sc, t_env *env)
{
	if((sc->fileoff + sc->vmsize) > env->file_size)
		return (1);
	return (0);
}

int						is_corrupted(struct segment_command	*sc, t_env *env)
{
	if((sc->fileoff + sc->vmsize) > env->file_size)
		return (1);
	return (0);
}

int                     is_fat_corrupted()
{
    
}