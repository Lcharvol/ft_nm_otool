#include "../includes/nm.h"

void	handle_header_64(char *ptr, t_env *env)
{
    struct mach_header_64	*header;

    header = (struct mach_header_64 *)ptr;
    env->header_64 = header;
};

void	handle_header_32(char *ptr, t_env *env)
{
    struct mach_header	*header;

    header = (struct mach_header *)ptr;
    env->header_32 = header;
};