#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

char fulltext[21000];
char text[21000];

char *pal;
int pallen;

void
findpal(void)
{
    char *p, *fwd, *bkwd, *etext;
    int len;

    etext = text+strlen(text);
    for(p=text; *p; p++) {
	/* try palindrome with *p as center character */
	for(fwd=bkwd=p; bkwd >= text && fwd < etext && *fwd == *bkwd;
				fwd++, bkwd--)
			;
	bkwd++;
	len = fwd - bkwd;
	if(len > pallen) {
	    pal = bkwd;
	    pallen = len;
	}

	/* try palindrome with *p as left middle character */
	for(bkwd=p, fwd=p+1;
	          bkwd >= text && fwd < etext && *fwd == *bkwd; fwd++, bkwd--)
			;
	bkwd++;
	len = fwd - bkwd;
	if(len > pallen) {
	    pal = bkwd;
	    pallen = len;
	}
    }
}

void
main(void)
{
    FILE *fin, *fout;
    char *p, *q;
    int c, i, n;

    fin = fopen("calfflac.in", "r");
    fout = fopen("calfflac.out", "w");
    assert(fin != NULL && fout != NULL);

    /* fill fulltext with input, text with just the letters */
    p=fulltext;
    q=text;
    while((c = getc(fin)) != EOF) {
	if(isalpha(c))
	    *q++ = tolower(c);
	*p++ = c;
    }
    *p = '\0';
    *q = '\0';

    findpal();

    fprintf(fout, "%d\n", pallen);

    /* find the string we found in the original text
       by finding the nth character */
	n = pal - text;
    for(i=0, p=fulltext; *p; p++)
	if(isalpha(*p))
	    if(i++ == n)
		break;
    assert(*p != '\0');

    /* print out the next pallen characters */
    for(i=0; i<pallen && *p; p++) {
	fputc(*p, fout);
	if(isalpha(*p))
	    i++;
    }
    fprintf(fout, "\n");

    exit(0);
}

