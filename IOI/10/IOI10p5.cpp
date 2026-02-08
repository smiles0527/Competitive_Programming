#include "memory.h"
#include <bits/stdc++.h>
using namespace std;

void play() {
  int idx[25][2];
  for (int i = 0; i < 25; i++)
    idx[i][0] = idx[i][1] = 0;

  /*
    round 1: just read everything once and remember where letters are
    (after every 2 flips grader resets them, so 1..50 sequentially is always
    legal)
  */
  for (int i = 1; i <= 50; i++) {
    char r = faceup(i);
    int t = r - 'A';
    int k = idx[t][0] ? 1 : 0;
    idx[t][k] = i;
  }

  /*
    round 2: now we know the exact pair positions, flip each pair once -> candy
    for sure 25 pairs => 50 calls, total 100
  */
  for (int t = 0; t < 25; t++) {
    faceup(idx[t][0]);
    faceup(idx[t][1]);
  }
}
