#ifndef UTILS_H
#define UTILS_H

#include <errno.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *programName;
#define OK 0

void __xerrno(int line, const char *fn)
{
	if (errno) {
		printf(
			"%s:%s:%d: %s\n",
			programName, fn, line,
			strerror(errno)
		);
		exit(EXIT_FAILURE);
	}
}
#define xerrno() __xerrno(__LINE__, __func__)

void *__xmalloc(size_t size, int line, const char *fn)
{
	errno = 0;
	void *data = NULL;
	data = malloc(size);
	if (data == NULL) {
		printf(
			"%s:%s:%d: %s\n",
			programName, fn, line,
			strerror(errno)
		);
		exit(EXIT_FAILURE);
	}
	return data;
}
#define xmalloc(s) __xmalloc(s, __LINE__, __func__)

void *__xcalloc(size_t count, size_t size, int line, const char *fn)
{
	errno = 0;
	void *data = NULL;
	data = calloc(count, size);
	if (data == NULL) {
		printf(
			"%s:%s:%d: %s\n",
			programName, fn, line,
			strerror(errno)
		);
		exit(EXIT_FAILURE);
	}
	return data;
}
#define xcalloc(c, s) __xcalloc(c, s, __LINE__, __func__)

void *__xrealloc(void **ptr, size_t size, int line, const char *fn)
{
	errno = 0;
	*ptr = realloc(*ptr, size);
	if (*ptr == NULL) {
		printf(
			"%s:%s:%d: %s\n",
			programName, fn, line,
			strerror(errno)
		);
		exit(EXIT_FAILURE);
	}
	return *ptr;
}
#define xrealloc(p, s) __xrealloc(p, s, __LINE__, __func__)

void xinit(int argc, char **argv)
{
	size_t len = strlen(argv[0]);
	programName = xcalloc(len + 1, sizeof(char));
	memcpy(programName, argv[0], len);
}

void xfree(void)
{
	free(programName);
}

#endif /* UTILS_H */
