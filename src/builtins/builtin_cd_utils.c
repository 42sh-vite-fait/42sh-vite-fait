#include "string_42.h"
#include "builtins.h"

const char	*get_next_component(t_string *component, const char *path)
{
	ssize_t		sep;

	if (path[0] == '\0')
		return (NULL);
	string_truncate(component, 0);
	sep = ft_strchrpos(path, '/');
	if (sep == -1)
	{
		string_cat(component, path);
		return (ft_strchr(path, '\0'));
	}
	string_ncat(component, path, sep);
	while (path[sep] == '/')
		sep += 1;
	return (path + sep);
}
