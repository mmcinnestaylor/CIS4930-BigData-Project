#include <iostream>
#include <cstdlib>
using namespace std;

int main(){
int num, SIZE = 1000000;

cout << SIZE << " ";

for(int i=0;i<SIZE;i++){
  num = rand();
  if(num % 3 == 0)
    num *= -1;
  cout << num << " ";
}
return 0;
}
