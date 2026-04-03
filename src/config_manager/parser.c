#include "config_manager.h"

t_config_parser_result	config_parse_line(int file, char **key, char **value)
{
	char			*line;
	unsigned int	split_index;
    char *trimmed;

	line = get_next_line(file);
	if (!line)
		return (t_config_parser_error_memory_error);
	split_index = 0;
	while (line[split_index] && line[split_index] != '=')
		split_index++;
	if (!line[split_index])
	{
		free(line);
		return (t_config_parser_error_equal_not_found);
	}
    if (!split_index)
    {
        free(line);
        return (t_config_parser_error_no_key);
    }
    *key = ft_substr(line, 0, split_index);
    trimmed = ft_strtrim(*key, "\t ");
    free(*key);
    *key = trimmed;
    *value = ft_substr(line, split_index + 1, ft_strlen(line + split_index + 1));
    trimmed = ft_strtrim(*value, "\t ");
    free(*value);
    *value = trimmed;
    return(t_config_parser_error_success);
}
