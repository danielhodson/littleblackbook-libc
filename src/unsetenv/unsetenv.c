#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define EV_NAME "TEST"
#define EV_VAL  "TRUE"
#define EV EV_NAME "=" EV_VAL

extern char **environ;

int test1(void)
{
	// NULL unset
	if(unsetenv(NULL) != -1 || errno != EINVAL)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int test2(void)
{
	// vanilla unset
	if(unsetenv(EV_NAME) != 0)
		return EXIT_FAILURE;

	// make sure its gone
	if(getenv(EV_NAME))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int test3(void)
{
	// unset a non-existant variable
	if(unsetenv("fake") != 0)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int run_tests(void)
{
	int ret = (EXIT_FAILURE << 0);

	// create a fake environment
	environ = calloc(3, sizeof(char *));
	if(NULL == environ)
          goto End;

	// set the first environment variable
	environ[0] = malloc(strlen(EV));
	if(NULL == environ[0])
		goto End;
	strcpy(environ[0], EV);

	// set it again with same KV pair
	environ[1] = malloc(strlen(EV));
	if(NULL == environ[1])
		goto End;
	strcpy(environ[1], EV);

	// explicit null
	environ[2] = NULL;

	ret |= ((!!test1()) << 1);
	ret |= ((!!test2()) << 2);
	ret |= ((!!test3()) << 3);

	// run_tests success
	ret &= ~(EXIT_FAILURE << 0);

End:
	return ret;
}
