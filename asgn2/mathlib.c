#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#define EPSILON 1e-10

// This is taken from previous code I wrote last quarter
double Abs(double x) {
    if (x < 0) {
        x = x * -1;
    }
    return x;
}

// This was taken from the code provided by Prof. Long on piazza
double Sqrt(double x) {
    long double new = 1.0;
    long double old = 0.0;
    while (fabsl(new - old) > EPSILON) {
        old = new;
        new = 0.5 * (new + x / new);
    }
    return new;
}

// Calculates the value to the power of 2
double Pow(double x) {
    return (x * x);
}

// This program was created using Newton's method, or inverse Method
double arcSin(double x) {
    double a = x;
    for (a = x; Abs(sin(x) - a) > EPSILON; x += 0) {
        double num = sin(x) - a;
        x -= num / cos(x);
    }
    return x;
}

// This utilizes the formula provided by the Prof on the assignment doc
double arcCos(double x) {
    x = fmod(x, (M_PI));
    double mult = M_PI / 2;
    return (mult - arcSin(x));
}

// This utilizes the formula provided by the Prof on the assignment doc
double arcTan(double x) {
    return arcSin(x / (Sqrt(Pow(x) + 1)));
}

// This code was taken from code I created last quarter
double Exp(double x) {
    double previndiv = 1;
    double currindiv = 1;
    double sum = 1;
    double k = 1;
    double absValue = Abs(previndiv);
    while ((absValue) > EPSILON) {
        currindiv = x / k;
        currindiv = currindiv * previndiv;
        sum += currindiv;
        previndiv = currindiv;
        k += 1;
        absValue = Abs(previndiv);
    }
    return sum;
}

// This code was taken from code I created last quarter
double Log(double x) {
    double prevY = 1;
    double currY = 1;
    double p = Exp(prevY);
    double absValue = Abs(p - x);
    for (double i = 0; absValue > EPSILON; i++) {
        currY = x - p;
        currY /= p;
        currY += prevY;
        p = Exp(currY);
        prevY = currY;
        absValue = Abs(p - x);
    }
    return currY;
}
