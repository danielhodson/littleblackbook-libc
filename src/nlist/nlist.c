#include <stdlib.h>
#include <nlist.h>

int test1(char *f)
{
        struct nlist scratch = {0};

	if(nlist(NULL, &scratch) != -1)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int test2(char *f)
{
        struct nlist scratch = {0};

	if(nlist(f, NULL) != -1)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int test3(char *f)
{
        struct nlist scratch = {0};

	if(nlist(f, &scratch) == -1)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int run_tests(char *f) {
	int ret = EXIT_FAILURE;

	if(test1(f) != EXIT_SUCCESS)
	  goto End;

//	if(test2(f) != EXIT_SUCCESS)
//	  goto End;

	if(test3(f) != EXIT_SUCCESS)
	  goto End;

	ret = EXIT_SUCCESS;

End:
	return ret;
}
