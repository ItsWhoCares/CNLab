#include <stdio.h>
int main() {
  int bcktsize, pkt[25], iter, rate, line, total = 0, i, j;
  printf("enter the bucket size and output rate");
  scanf("%d%d", &bcktsize, &rate);
  printf("enter the number of input lines\n");
  scanf("%d", &line);
  printf("enter input packet rate of %d lines\n", line);
  for (i = 0; i < line; i++)
    scanf("%d", &pkt[i]);
  for (j = 0; j < line; j++) {
    total += pkt[j];
    if (total <= bcktsize)
      printf("\n input from line %d with rate %d is added to the bucket\n "
             "current bucket size is %d\n",
             j + 1, pkt[j], total);
    else {
      total -= pkt[j];
      printf("\n input from line %d with rate %d is thrown out of bucket\n "
             "current bucket size is %d\n",
             j + 1, pkt[j], total);
    }
  }
  if (total <= rate) {
    printf("packet sent to output line at rate %d", total);
    total = 0;
    printf("current bucket size is %d", total);
  } else {
    total -= rate;
    printf("\n      \n");
    printf("\n packet sent to output line at rate %d\n current bucket size is "
           "%d\n",
           rate, total);
    printf("\n     \n");
  }
  return 0;
}
