/*********************************************************************************************
 * labo1 TCO
 *
 *********************************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//nombre d'elements a trier
int Elem_Count = 1e7;
double Clocks_Per_Sec = 1e6;

//tableau contenant les valeurs
double* values;
double* values_copy;

double randomGen(double min, double max){
  double range = max-min;
  double div = RAND_MAX - range;
  return min + (rand()/div);
}

void init(){
  /*do{
    printf("entrez le nombre d'elements du tableau [1; 10M]: ");
    scanf("%d", &Elem_Count);
  }while((Elem_Count <= 0 || Elem_Count > 10000000) && printf("nombre d'elements errone. entrez un nombre entre 1 et 10 millions"));
  */
  int i;
  values = calloc(Elem_Count, sizeof(double));
  values_copy = calloc(Elem_Count, sizeof(double));
  for(i = 0; i < Elem_Count; i++){
    values[i] = randomGen(0.0, 1.0);
    values_copy[i] = values[i];
  }
}

void cumstomQSort(double* values, int left, int right){
  double pivot;
  int l_hold, r_hold, temp;
  l_hold = left;
  r_hold = right;
  pivot = values[left];
  while(left < right){
    while((values[right] >= pivot) && (left < right))
      right--;
    if (left != right){
      values[left] = values[right];
      left++;
    }
    while((values[left] <= pivot) && (left < right))
      left++;
    if(left != right){
      values[right] = values[left];
      right--;
    }
  }
  values[left] = pivot;
  temp = left;
  left = l_hold;
  right = r_hold;
  if(left < temp)
    cumstomQSort(values, left, temp-1);
  if(right > temp)
    cumstomQSort(values, temp+1, right);
}

int compare (const void * a, const void * b)
{
  if(*(double*)a < *(double*)b)
    return -1;
  else if(*(double*)a == *(double*)b)
    return 0;
  
  return 1;
}

int main(){
  int qsort_start_time;
  int qsort_end_time;
  double qsort_time_diff;
  int cqsort_start_time;
  int cqsort_end_time;
  double cqsort_time_diff;
  init();
  //int i;
  //for(i = 0; i < Elem_Count; i++)
    //printf("%f, ", values[i]);
  printf("debut du qsort\n");
  qsort_start_time = clock();
  qsort(values, Elem_Count, sizeof(double), compare);
  qsort_end_time = clock();
  //for(i = 0; i < Elem_Count; i++)
    //printf("%f, ", values[i]);
    
  qsort_time_diff = (double)(qsort_end_time - qsort_start_time)/Clocks_Per_Sec;
  printf("temps pris par le qsort: %f [s]\n", qsort_time_diff);
    
  printf("debut du custom qsort\n");
  cqsort_start_time = clock();
  cumstomQSort(values_copy, 0, Elem_Count-1);
  cqsort_end_time = clock();
  
  cqsort_time_diff = (double)(cqsort_end_time - qsort_start_time)/Clocks_Per_Sec;
  printf("temps pris par le custom qsort: %f [s]\n", cqsort_time_diff);
  
  system("PAUSE");
  return 0;
  
}


