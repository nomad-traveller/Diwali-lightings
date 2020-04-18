// April 18 2020
// https://code.google.com/codejam/contest/5264487/dashboard
// This file will be commented in due curse

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef uint64_t u64;
typedef uint8_t u8;

#define U64 uint64_t
#define U8 char

typedef struct {
    char s[100];
    u64 testcase;
    u64 start, end, size, span, sm, em, es, ss;
    u64 n;
} TESTCASE;

// BBRB BBRB BBRB BBRB
// 0123 4567 8901 2345
// 1234 5678 9012 3456 7
// 0123 0123 0123 0123
#define SMAX 100

u64 count(char *);
void printTestCases(TESTCASE* t, u64 nCases);
u64 doTheWork(char* str, u64 b, u64 a);
u64 readTestCases(TESTCASE *);

int main() {

    u64 n = 0, i = 0, nCases;
    TESTCASE t[SMAX];

    nCases = readTestCases(t);

    for ( u64 i = 0; i < nCases; i++ ) {

        n = 0;

        if ( t[i].ss == t[i].es ) {
            n += doTheWork(t[i].s,t[i].em,t[i].sm);
        }

        if (t[i].es > t[i].ss  ) {
            n += doTheWork(t[i].s,t[i].size,t[i].sm);
            n += doTheWork(t[i].s,t[i].em,0);
        }
        if ( t[i].es > t[i].ss+1) {
            u64 ia = (t[i].es-t[i].ss);
            n+= (ia-1)*t[i].span;
        }
        t[i].n = n;

    }
    printTestCases(t,nCases);

    return 0;
}
u64 readTestCases(TESTCASE *t) {
    u64 start, end, nCases;
    FILE *fp = fopen("large.in","r");
    fscanf(fp,"%I64u",&nCases);
    for ( int i = 0; i < nCases; i++ ) {
        fscanf(fp,"%s %I64u %I64u",t[i].s,&t[i].start,&t[i].end);
        t[i].size = strlen(t[i].s);
        t[i].span = count(t[i].s);
        t[i].start--;
        t[i].end--;
        t[i].ss = t[i].start/t[i].size;
        t[i].es = t[i].end/t[i].size;
        t[i].sm = t[i].start%t[i].size;
        t[i].em = t[i].end%t[i].size;
        t[i].n = 0;
        printf("rt span %i %i %i \n",t[i].span,t[i].sm, t[i].em);
    }
    fclose(fp);
    return nCases;
}


void printTestCases(TESTCASE *t,u64 nCases) {

    FILE *fp = fopen("result.out","w");
    for ( int i = 1; i <= nCases; i++) {
        fprintf(fp,"Case #%i: %I64u\n",i,t[i-1].n);
    }
    fclose(fp);
}

u64 doTheWork(char *str,u64 b, u64 a) {
    char buffer[100];
    memset(buffer,0,100);
    strncpy(buffer,str+a,b-a+1);
    printf("buffer %s %s %i %i %i\n",str+a,buffer,a,b,count(buffer));
    return count(buffer);
}

u64 count(char *s) {
    u64 n = 0;
    char *p = s;
    while( *p ) {
        if ( *p == 'B' ) {
            n++;
        }
        p++;
    }
    return n;
}
