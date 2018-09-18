#include "../includes/nm.h"

void						handle_fat_arch_content(t_env *env, unsigned long i, struct fat_header	*header_fat, char *ptr)
{
	struct fat_arch		*arch;
	unsigned long		arch_offset;
	cpu_type_t			cputype;

	arch = (void *)header_fat + sizeof(struct fat_header) + (i * sizeof(struct fat_arch));
	cputype = header_fat->magic == FAT_MAGIC ? arch->cputype : swap_bigendian_littleendian(arch->cputype, sizeof(arch->cputype));
	arch_offset = header_fat->magic == FAT_MAGIC ? arch->offset : swap_bigendian_littleendian(arch->offset, sizeof(arch->offset));
	env->header_32 = (struct mach_header *)((void *)ptr + arch_offset);
	if(cputype == CPU_TYPE_X86_64)
		otool((void *)ptr + arch_offset, env);
}

void						handle_fat_arch(char *ptr, t_env *env)
{
	struct fat_header	*header_fat;
	unsigned long		nfat_arch;
	unsigned long		i;

	i = -1;
	header_fat = env->header_fat;
	nfat_arch = header_fat->magic == FAT_MAGIC ? header_fat->nfat_arch :
		swap_bigendian_littleendian(header_fat->nfat_arch , sizeof(header_fat->nfat_arch ));
	while(++i < nfat_arch)
		handle_fat_arch_content(env, i, header_fat, ptr);
}