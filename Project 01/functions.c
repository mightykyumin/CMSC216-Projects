#include "functions.h"
short compare_rectangles(int l1, int w1, int l2, int w2) {
  int area1 = 0;
  int area2 = 0;

  if(l1 <0 || w1 <0 || l2 <0 || w2<0)
    return -2;
  area1 = l1 *w1;
  area2 = l2 *w2;

  if(area1 == area2 ){
    return 0;
  }
  else if(area1< area2){
    return -1;
  }
  else 
    return 1;
  
 
}

int ith_factor(int a, int b, int i) {
  int small=0;
  int count =0;
  int k =0;
  if(i<=0)
    return -1;
  if(a<0)
    a = a *(-1);
  if(b<0)
    b= b *(-1);
  if(a<b)
    small = a;
  else
    small =b;

  for(k=1;k<=small;k++)
  {
    if(a % k ==0 && b % k ==0)
      count++;
    if(count == i)
      return k;
  }
  return -1;
}

long pell(short n) {
  if(n<0){
    return -1;
  }
  if(n ==0)
    return 0;
  if(n==1)
    return 1;
  else
    return 2*pell(n-1) +pell(n-2);

}
