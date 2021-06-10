#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "asctl"

//This program was copletely based off a past code created by myself. At the time I was referencing to code provided by Sahiti.
int main(int args, char *argv[]) {
    int opt = 0;
    bool all, makeArcsin, makeArccos, makeArctan, makeLog = false;
    while ((opt = getopt(args, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            all = true;
            makeArcsin = true;
            makeArccos = true;
            makeArctan = true;
            makeLog = true;
            break;
        case 's': makeArcsin = true; break;
        case 'c': makeArccos = true; break;
        case 't': makeArctan = true; break;
        case 'l': makeLog = true; break;
        default: fprintf(stderr, "Usage %s -[asctl]", argv[0]);
        }
    }
    if (all == true) {
    }
    if (makeArcsin == true) {
        printf("  x            Arcsin           Library          Difference\n");
        printf("  -            ------           -------          ----------\n");
        double s = -1;
        while (s <= 1) {
            double sinAns = asin(s);
            double sinDiff = (arcSin(s) - sinAns);
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.8lf\n", s, arcSin(s), sinAns, sinDiff);
            s += 0.1;
        }
    }
    if (makeArccos == true) {
        printf("  x            Arccos           Library          Difference\n");
        printf("  -            ------           -------          ----------\n");
        double c = -1;
        while (c <= 1) {
            double cosAns = acos(c);
            double cosDiff = (cosAns - arcCos(c));
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.8lf\n", c, arcCos(c), acos(c), cosDiff);
            c += 0.1;
        }
    }
    if (makeArctan == true) {
        printf("  x            Arctan           Library          Difference\n");
        printf("  -            ------           -------          ----------\n");
        double t = 1;
        while (t <= 10) {
            double tanAns = atan(t);
            double tanDiff = atan(t) - arcTan(t);
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.8lf\n", t, arcTan(t), tanAns, tanDiff);
            t += 0.1;
        }
    }
    if (makeLog == true) {
        printf("  x            Log              Library          Difference\n");
        printf("  -            ---              -------          ----------\n");
        double l = 1;
        while (l <= 10) {
            double logAns = log(l);
            double logDiff = (Log(l) - logAns);
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.8lf\n", l, Log(l), log(l), logDiff);
            l += 0.1;
        }
    }
    return 0;
}
