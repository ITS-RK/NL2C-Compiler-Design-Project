#include <stdio.h>
int add(int a, int b){
return a + b;
}
int main(){
int i;
int total;
float average;
i = 0;
total = add(2, 3 * 4);
while (i < 3) {
total = total + i;
i = i + 1;
}
for (i = 1; i <= 2; i += 1) {
total = total + i;
}
if (total > 10) {
average = (float)(float)(total) / (float)2.0;
printf("%f\n", average);
} else {
printf("%d\n", total);
}
if (i == 3) {
printf("%d\n", i);
} else {
printf("%d\n", total);
}
return 0;
}
