#include <stdio.h>
#include <stdlib.h>
struct Frame {
  int num;
  char str[20];
};
struct Frame frame[10];
int n;

void sort() /*Bubble sort */
{
  int i, j;
  struct Frame temp;
  for (i = 0; i < n - 1; i++)

    for (j = 0; j < n - i - 1; j++)

      if (frame[j].num > frame[j + 1].num) {
        temp = frame[j];
        frame[j] = frame[j + 1];
        frame[j + 1] = temp;
      }
}

int main() {
  int i;
  system("clear");
  printf("Enter the number of frames: ");
  scanf("%d", &n);
  printf("Enter the frame sequence number and frame contents:\n");
  for (i = 0; i < n; i++)
    scanf("%d%s", &frame[i].num, frame[i].str);
  sort();
  printf("The frame in sequences\n");
  for (i = 0; i < n; i++)
    printf("%d\t%s\n", frame[i].num, frame[i].str);
}
