#include <stdio.h>
#include "../libft/includes/libft.h"

int		main()
{
	int	ret;
	char *line;

	ret = 0;
	line = NULL;
	while ((ret = get_next_line(0, &line)) != 0)
		printf("%s\n", line);
	return (0);
}
