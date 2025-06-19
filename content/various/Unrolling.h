/**
 * Author: Simon Lindholm
 * Date: 2015-03-19
 * License: CC0
 * Source: me
 * Description:
 */
#pragma once

#define F {...; ++i;}
int i = from;
while (i&3 && i < to) F // for alignment, if needed
while (i + 4 <= to) { F F F F }
while (i < to) F

int n32 = n / 32;
while (n32--) {
#define F(i) a[i] = a[i] == x ? y : a[i];
#define FP(i) F(i+0) F(i+1) F(i+2) F(i+3)
  FP(0); FP(4); FP(8); FP(12);
  FP(16); FP(20); FP(24); FP(28);
  a += 32;
}
