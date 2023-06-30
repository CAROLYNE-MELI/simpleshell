#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter's struct
 * @buf: address of bufferr
 * @len: address of len varr
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	zsize_t k = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing's left in the buffer, fill  */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		k = getline(buf, &len_p, stdin);
#else
		k = _getline(info, buf, &len_p);
#endif
		if (k > 0)
		{
			if ((*buf)[k - 1] == '\n')
			{
				(*buf)[k - 1] = '\0'; /* remove trailing newline */
				k--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = k;
				info->cmd_buf = buf;
			}
		}
	}
	return (k);
}

/**
 * get_input - getingg a line withoutt de newline
 * @info: parameter structs
 *
 * Return: bytes red
 */
zsize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain bufferer */
	static size_t i, j, len;
	zsize_t k = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	k = input_buf(info, &buf, &len);
	if (k == -1) /* EOF. */
		return (-1);
	if (len)
	{
		j = i; /* init new itterator to current baf position */
		p = buf + i; /* get pointer for de return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semiccolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increament past nulled ';'' */
		if (i >= len) /* reached towars de end of buffer? */
		{
			i = len = 0; /* reset posittion and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer 2 current command position */
		return (_strlen(p)); /* return length of current cmd */
	}

	*buf_p = buf; /* else not a chain, pass back buffeerr from _getline() */
	return (k); /* return length of buffeerr from _getline() */
}

/**
 * read_buf - reading a buffer
 * @info: parameter's sstruct
 * @buf: bufferr
 * @i: sizee
 *
 * Return: k
 */
zsize_t read_buf(info_t *info, char *buf, size_t *i)
{
	zsize_t k = 0;

	if (*i)
		return (0);
	k = read(info->readfd, buf, READ_BUF_SIZE);
	if (k >= 0)
		*i = k;
	return (k);
}

/**
 * _getline - gets the next line of input from standartdIN
 * @info: parameter structs
 * @ptr: address of pointer to buffeerr, preallocated or NULL
 * @length: size of preallocated ptr buffeerr if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t z;
	zsize_t k = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	k = read_buf(info, buf, &len);
	if (k == -1 || (k == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	z = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + z : z + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, z - i);
	else
		_strncpy(new_p, buf + i, z - i + 1);

	s += z - i;
	i = z;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Bblocks ctrl-C
 * @sig_num: the signal no..
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
