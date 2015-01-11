#ifndef FLAGS_H
#define FLAGS_H

/*enum flags_enum {
	flag_help = 1,
	flag_man,
	flag_len
};*/

enum flags_enum {
	flag_right = 1,
	flag_left,
	flag_by,
	flag_len
};

unsigned long flags;
int flagnum[flag_len];

void flagErrorDublicatedCommand(char *flag)
{
	printf(
		"%s: %s Duplicated command\n",
		programName,
		flag
	);
	exit(EXIT_FAILURE);
}

const char *flagToStr(int flag)
{
	switch (flag) {
	case flag_left:
		return "-l";
	case flag_right:
		return "-b";
	case flag_by:
		return "-by";

	}
}

void flagErrorIncompatible(int flagA, char *flagB)
{
	printf(
		"%s: %s is incompatible to %s\n",
		programName,
		flagToStr(flagA),
		flagB
	);
}

int flagIsCompatible(int flagType, int flagWith, char *flag)
{
	int compatible = 1;
	if (flags & (1 << flagWith)) {
		compatible = 0;
		flagErrorIncompatible(flagWith, flag);
	}
	return compatible;
}

int flagIsDublicate(int flagType, char *flag)
{
	if (flags & (1 << flagType)) {
		flagErrorDublicatedCommand(flag);
	}
}

int flagCheckFlag(char *flag)
{
	int fatal    = 0;
	int flagType = 0;
/*	if (strcmp("-h", flag) == OK) {
		flagType = flag_help;
		flagIsDublicate(flagType, flag);	
		if (!flagIsCompatible(flagType, flag_man, flag)) {
			fatal = 1;
		}
		goto out;
	}
	if (strcmp("-m", flag) == OK) {
		flagType = flag_man;
		flagIsDublicate(flagType, flag);	
		if (!flagIsCompatible(flagType, flag_help, flag)) {
			fatal = 1;
		}
		goto out;
	}*/
	if (strcmp("-r", flag) == OK) {
		flagType = flag_right;
		flagIsDublicate(flagType, flag);	
		if (!flagIsCompatible(flagType, flag_left, flag)) {
			fatal = 1;
		}
		direction = flag_right;
		goto out;
	}
	if (strcmp("-l", flag) == OK) {
		flagType = flag_left;
		flagIsDublicate(flagType, flag);	
		if (!flagIsCompatible(flagType, flag_right, flag)) {
			fatal = 1;
		}
		direction = flag_left;
		goto out;
	}

	if (flag[1] == 'b' && flag[2] == 'y') {
		flagType = flag_by;
		int i, len;
		char *p = (flag + 3);
		by = atoi(p);
	}

	if (flagType == 0) {
		fatal = 1;
		printf("%s: %s command not found\n", programName, flag);
	}

out:
	if (fatal) {
		exit(EXIT_FAILURE);
	}
	return (1 << flagType);
}

int flagCheckFlags(int argc, char **argv)
{
	errno = 0;
	int i;
	int tmp;
	flags = 0;
	for (i = 1; i < argc; i += 1) {
		flags |= flagCheckFlag(argv[i]);
	}
	/*for (i = 1; i < flag_len; i += 1) {
		if (flags & (1 << i)) {
			printf("function here\n");
		}
	}*/
}

#endif /* FLAGS_H */
