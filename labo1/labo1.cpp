/*********************************************************************************************
 * labo1 TCO
 *
 *********************************************************************************************/
 
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include "randomc.h"

//nombre d'elements a trier
int Min_Elem_Count = 10;
int Max_Elem_Count = 1e6;
//nombre d'increments effectues par un appel a clock() par seconde
//clock compte donc les nanosecondes
double Clocks_Per_Sec = 1e6;

//tableau contenant les valeurs
double* values;
double* values_copy;

double randomGen(double min, double max){
  double range = max-min;
  double div = RAND_MAX - range;
  return min + (rand()/div);
}

void init(int elem_count){
  /*do{
    printf("entrez le nombre d'elements du tableau [1; 10M]: ");
    scanf("%d", &Elem_Count);
  }while((Elem_Count <= 0 || Elem_Count > 10000000) && printf("nombre d'elements errone. entrez un nombre entre 1 et 10 millions"));
  */
  
  //CRandomMother* ran = new CRandomMother(time(NULL));
  values = new double[elem_count];
  values_copy = new double[elem_count];
  for(int i = 0; i < elem_count; i++){
     //normal tests
    //values[i] = randomGen(0.0, 1.0);//*/ran->Random();
    //q_sort worst case
    //values[i] = 1.0-(i*1.0/elem_count);
    //qsort worst case
    values[i] = randomGen(0.0, 1.0);
    values_copy[i] = values[i];

  }
}

void exploding_qsort_init(int min, int max, double val, int elem_count){
   int mid = (max+min)/2 +1;
   /*printf("mid: %d ", mid);
   printf("min: %d ", min);
   printf("max: %d ", max);
   printf("max-min: %d ", max-min);
   printf("val: %f \n", val);*/
   values[mid] = val;
   values_copy[mid] = val;
   if(mid != min && min != max){
      exploding_qsort_init(min, mid-1, val+1.0/elem_count, elem_count);
      exploding_qsort_init(mid+1, max, val+1.0/elem_count, elem_count);
   }
   else if (values[mid+1] == 0){
      values[mid+1] = val+1.0/elem_count;
      values_copy[mid+1] = val+1.0/elem_count;
   }
}

void q_sort(double* values, int left, int right){
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
    q_sort(values, left, temp-1);
  if(right > temp)
    q_sort(values, temp+1, right);
}

int compare (const void * a, const void * b)
{
  if(*(double*)a < *(double*)b)
    return -1;
  else if(*(double*)a == *(double*)b)
    return 0;
  else
    return 1;
}

void sort(int elem_count){
   
   int qsort_start_time;
   int qsort_end_time;
   double qsort_time_diff;
   int q_sort_start_time;
   int q_sort_end_time;
   double q_sort_time_diff;
   
   //init(elem_count);
   values = new double[elem_count];
   values_copy = new double[elem_count];
   exploding_qsort_init(0, elem_count, 0, elem_count);
   
   printf("\ndebut du qsort avec %d elements: \n", elem_count);
   qsort_start_time = clock();
   qsort(values, elem_count, sizeof(double), compare);
   qsort_end_time = clock();

   qsort_time_diff = (double)(qsort_end_time - qsort_start_time)/Clocks_Per_Sec;
   printf("temps pris par le qsort: %f [s]\n", qsort_time_diff);


   printf("debut du q_sort\n");
   q_sort_start_time = clock();
   q_sort(values_copy, 0, elem_count-1);
   q_sort_end_time = clock();

   q_sort_time_diff = (double)(q_sort_end_time - q_sort_start_time)/Clocks_Per_Sec;
   printf("temps pris par le q_sort: %f [s]\n\n", q_sort_time_diff);

   delete[] values_copy;
   delete[] values;
   
}

int main(){

   int j;

  srand(time(NULL));

  for (int i = Min_Elem_Count ; i < Max_Elem_Count; i *= 10){
     //section 10*     
     sort(i);

     //section 30*
     j = 3*i;
     sort(j);
     
     printf("---------------------------------------------------------------\n");

  }
  system("PAUSE");
  return 0;
  
}


