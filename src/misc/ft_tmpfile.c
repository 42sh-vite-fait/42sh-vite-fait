#include <sys/time.h>
#include <fcntl.h>
#include "ft_printf.h"

#ifdef P_tmpdir
# define DFLT_PATH P_tmpdir "/"
#else
# define DFLT_PATH "/tmp/"
#endif

static char	*gen_candidate(const char *prefix)
{
	struct timeval	time;
	char			*filename;
	int				ret;

	if (gettimeofday(&time, NULL) == -1)
		return (NULL);
	ret = ft_asprintf(&filename, "%s%s%zu%zu",
			DFLT_PATH,
			prefix,
			time.tv_sec,
			time.tv_usec);
	if (ret == -1)
		return (NULL);
	return (filename);
}

static char	*gen_tmp_name(const char *prefix)
{
	char	*filename;

	if (access(DFLT_PATH, W_OK) == -1)
		return (NULL);
	filename = gen_candidate(prefix);
	while (filename != NULL && access(filename, F_OK) == -1)
		filename = gen_candidate(prefix);
	return (filename);
}

char	*ft_tmpfile(const char *prefix)
{
	if (prefix == NULL)
		prefix = "";
	return (gen_tmp_name(prefix));
}
