#include "utils.h"
int direction;
int by;
#include "flags.h"

#define die() exit(EXIT_FAILURE)

char __shiftAlphaRight(unsigned char alpha, int by, int line, const char *fn)
{
	if (alpha == ' ')return alpha;

	if (alpha > 127) {
		printf("utf-8 support needed\n");
		die();
	}

	return alpha + by;
}
#define shiftAlphaRight(a, by) __shiftAlphaRight(a, by, __LINE__, __func__)

char __shiftAlphaLeft(unsigned char alpha, int by, int line, const char *fn)
{
	if (alpha == ' ')return alpha;

	if (alpha > 127) {
		printf("utf-8 support needed\n");
		die();
	}

	return alpha - by;
}
#define shiftAlphaLeft(a, by) __shiftAlphaLeft(a, by, __LINE__, __func__)

void crack_string(unsigned char *str, int direction, int by)
{
	int i, len;
	len = strlen(str);
	char (*go)(unsigned char alpha, int by, int line, const char *fu);

	if (direction == flag_left) {
		go = __shiftAlphaLeft;
	} else {
		go = __shiftAlphaRight;
	}

	for (i = 0; i < len; i += 1) {
		str[i] = go(str[i], by, __LINE__, __func__);
	}
}

#define BUF_SIZE 1024


int main(int argc, char **argv)
{
	xinit(argc, argv);
	flagCheckFlags(argc, argv);
	char buffer[BUF_SIZE];
	size_t contentSize = 0;
	unsigned char *content = NULL;
	content = xmalloc(sizeof(char) * BUF_SIZE);
	content[0] = '\0';
	if (!isatty(fileno(stdin))) {
		while(fgets(buffer, BUF_SIZE, stdin) != NULL) {
			unsigned char *old = content;
			contentSize += strlen(buffer);
			content = xrealloc((void **)&content, contentSize);
			strcat(content, buffer);
		}
	}
	crack_string(content, direction, by);

	printf("\n");
	printf("%s\n", content);
	xfree();
	free(content);
	return EXIT_SUCCESS;
}

