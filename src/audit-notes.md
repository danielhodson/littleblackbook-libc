```c++
static int
inet_net_pton_ipv4(const char *src, u_char *dst, size_t size)
{
    static const char
        xdigits[] = "0123456789abcdef",
        digits[] = "0123456789";
    int n, ch, tmp, dirty, bits;
    const u_char *odst = dst;

    ch = *src++;
    if (ch == '0' && (src[0] == 'x' || src[0] == 'X')
        && isascii(src[1]) && isxdigit(src[1])) {
        /* Hexadecimal: Eat nybble string. */
        if (size <= 0)
            goto emsgsize;
        *dst = 0, dirty = 0;
        src++;	/* skip x or X. */
        while ((ch = *src++) != '\0' &&
               isascii(ch) && isxdigit(ch)) {
            if (isupper(ch))
                ch = tolower(ch);
            n = strchr(xdigits, ch) - xdigits;
            assert(n >= 0 && n <= 15);
            *dst |= n;
            if (!dirty++)
                *dst <<= 4;
            else if (size-- > 0)
                *++dst = 0, dirty = 0;
            else
                goto emsgsize;
        }
        if (dirty)
            size--;
```

This mktemp is not random compared to linux ones:
https://github.com/danielhodson/wdk-urt/blob/a24e10a9497f96d59d31303b8fcf240efa0f4bef/10.0.17763.0/ucrt/lowio/mktemp.cpp


I want to show an examble of fmtmsg() from libctf which assist in exploitation.