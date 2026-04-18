#include <stdio.h>
int add(int a, int b){
return a + b;
}
int main(){
int x;
x = add(add(2, 3), 4);
printf("%d\n", x);
return 0;
}
