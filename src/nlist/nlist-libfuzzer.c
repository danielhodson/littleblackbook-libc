#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "nlist.h"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
	int ret = EXIT_FAILURE;
	int fd = -1;
	char *f = NULL;
	size_t count = 0;

	if((f = tmpnam(NULL)) == NULL)
  	  goto End;

	if((fd = open(f, O_CREAT | O_EXCL | O_WRONLY, 0755)) == -1)
	  goto End;

	do {
		count = write(fd, Data, Size);
		if(count == -1)
		  goto End;
		Size = Size - count;
	} while(Size > 0);

	close(fd);

	ret = run_tests(f);

End:
	if(fd >= 0)
	  close(fd);

	if(f != NULL)
	  unlink(f);

	return ret;
}
