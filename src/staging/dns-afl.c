#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int __dns_parse(const unsigned char *r, int rlen, int (*callback)(void *, int, const void *, int, const void *), void *ctx)
{
	int qdcount, ancount;
	const unsigned char *p;
	int len;

	if (rlen<12) return -1;
	if ((r[3]&15)) return 0;
	p = r+12;
	qdcount = r[4]*256 + r[5];
	ancount = r[6]*256 + r[7];
	if (qdcount+ancount > 64) return -1;
	while (qdcount--) {
		while (p-r < rlen && *p-1U < 127) p++;
		if (*p>193 || (*p==193 && p[1]>254) || p>r+rlen-6)
			return -1;
		p += 5 + !!*p;
	}
	while (ancount--) {
		while (p-r < rlen && *p-1U < 127) p++;
		if (*p>193 || (*p==193 && p[1]>254) || p>r+rlen-6)
			return -1;
		p += 1 + !!*p;
		len = p[8]*256 + p[9];
		if (p+len > r+rlen) return -1;
		if (callback(ctx, p[1], p+10, len, r) < 0) return -1;
		p += 10 + len;
	}
	return 0;
}

int __dn_expand(const unsigned char *base, const unsigned char *end, const unsigned char *src, char *dest, int space)
{
        const unsigned char *p = src;
        char *dend, *dbegin = dest;
        int len = -1, i, j;
        if (p==end || space <= 0) return -1;
        dend = dest + (space > 254 ? 254 : space);
        /* detect reference loop using an iteration counter */
        for (i=0; i < end-base; i+=2) {
                /* loop invariants: p<end, dest<dend */
                if (*p & 0xc0) {
                        if (p+1==end) return -1;
                        j = ((p[0] & 0x3f) << 8) | p[1];
                        if (len < 0) len = p+2-src;
                        if (j >= end-base) return -1;
                        p = base+j;
                } else if (*p) {
                        if (dest != dbegin) *dest++ = '.';
                        j = *p++;
                        if (j >= end-p || j >= dend-dest) return -1;
                        while (j--) *dest++ = *p++;
                } else {
                        *dest = 0;
                        if (len < 0) len = p+1-src;
                        return len;
                }
        }
        return -1;
}

#define RR_PTR 12

static int dns_parse_callback(void *c, int rr, const void *data, int len, const void *packet)
{
        if (rr != RR_PTR) return 0;
        if (__dn_expand(packet, (const unsigned char *)packet + 512,
            data, c, 256) <= 0)
                *(char *)c = 0;
        return 0;

}

int getnameinfo(const uint8_t *Data, size_t Size) {
  char buf[256] = {0};
  unsigned char reply[512] = {0};
  int rlen = Size % sizeof(reply);
  memcpy(reply, Data, rlen);
  return __dns_parse(reply, rlen, dns_parse_callback, buf);
}

int main(int argc, char **argv){
        int ret = EXIT_FAILURE;
        int fd = -1;
	size_t sz = 0;
	char buffer[512] = {0};

        if((fd = open(argv[1], O_RDONLY)) == -1)
          goto End;

	sz = read(fd, &buffer, sizeof(buffer));

        close(fd);

        ret = getnameinfo(&buffer, sz);

End:
        return ret;
}

