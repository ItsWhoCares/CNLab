// // Character stuffing
// #include <stdio.h>
// #include <string.h>
// #define FLAG "dlestx"
// void main() {
//   int i = 0, j = 0, n;
//   char a[100], b[100];
//   printf("\nEnter the original string: ");
  
//   scanf("%s", a);
//   n = strlen(a);
//   while (i < n) {
//     if (a[i] == 'd' && a[i + 1] == 'l' && a[i + 2] == 'e') {
//       b[j] = 'd';
//       b[j + 1] = 'l';
//       b[j + 2] = 'e';
//       j = j + 3;
//     }
//     b[j] = a[i];
//     i++;
//     j++;
//   }
//     b[j] = '\0';
//   printf("\nAfter character stuffing: ");
//   printf("%s%s%s\n", FLAG,b, FLAG);
// }


// Bit stuffing
#include <stdio.h>
void main() {
  int i = 0, count = 0;
  char a[100];
  printf("\nEnter the frame: ");
  scanf("%s", a);
  printf("\nAfter bit stuffing: ");
  printf("01111110");
  for (i = 0; a[i]; i++) {
    if (a[i] == '1')
      count++;
    else
      count = 0;
    printf("%c", a[i]);
    if (count == 5) {
      printf("0");
      count = 0;
    }
  }
  printf("01111110\n");
}
