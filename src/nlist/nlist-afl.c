#include <stdio.h>
#include "nlist.h"

int main(int argc, char **argv)
{
        if(argc <= 1) {
                fprintf(stderr, "%s <bin>\n", argv[0]);
                return -1;
        }

	return run_tests(argv[1]);
}
