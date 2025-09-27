#include "cub3d.h"

void	ft_error(char *msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (msg)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
	}
	else
	{
		write(STDERR_FILENO, "Ocorreu um erro desconhecido.", 29);
	}
	write(STDERR_FILENO, "\n", 1);
	ft_gc_exit(EXIT_FAILURE);
}

void	check_file_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
		ft_error("O arquivo de cena deve ter a extensão '.cub'.");
}