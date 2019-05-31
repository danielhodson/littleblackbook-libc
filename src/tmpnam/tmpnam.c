#include <stdio.h>
#include <stdlib.h>

int test1(void)
{
	unsigned int i = 0;
	for(i = 0; i < 10000000; i++) {
		printf("%s\n", tmpnam(NULL));
	}
	return EXIT_SUCCESS;
}

int test2(void)
{
	return EXIT_SUCCESS;
}

int test3(void)
{
	return EXIT_SUCCESS;
}

int run_tests(void)
{
	int ret = (EXIT_FAILURE << 0);

	ret |= ((!!test1()) << 1);
	ret |= ((!!test2()) << 2);
	ret |= ((!!test3()) << 3);

	// run_tests success
	ret &= ~(EXIT_FAILURE << 0);

End:
	return ret;
}
