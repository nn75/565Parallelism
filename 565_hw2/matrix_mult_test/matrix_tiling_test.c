#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

const int N = 1024;

double **array_a;
double **array_b;
double **array_c;

double calc_time(struct timespec start, struct timespec end) {
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;

  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}

void init_array(){
  double init_num = 1.0;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      array_a[i][j] = init_num;
      array_b[i][j] = init_num;
      array_c[i][j] = init_num;
    }
  }
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Syntax Error: matrix_test <loop type> \n");
    exit(EXIT_FAILURE);
  }

  char * loop_type = argv[1];
  if (strcmp(loop_type, "ijk") && 
      strcmp(loop_type, "jki") &&
      strcmp(loop_type, "ikj")) {
    printf("No such loop type: ijk, jki, ikj\n");
    exit(EXIT_FAILURE);
  }

  struct timespec start_time, end_time;

  array_a = (double**)malloc(N * sizeof(double*));
  array_b = (double**)malloc(N * sizeof(double*));
  array_c = (double**)malloc(N * sizeof(double*));
  for(int i = 0; i < N; i++) {
    array_a[i] = (double*)malloc(N * sizeof(double));
    array_b[i] = (double*)malloc(N * sizeof(double));
    array_c[i] = (double*)malloc(N * sizeof(double));
  }

  init_array();

  double sum;
  double tmp;
  if (!strcmp(loop_type, "ijk")) {                //same as jik
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int i = 0 ; i < N ; i++) {
      for (int kk = 0 ; kk < N ; kk = kk + 64) {
        for (int j = 0 ; j < N ; j++) {
          sum = 0;
          for (int k = kk ; k < kk + 64 ; k++) {
            sum += array_a[i][k] * array_b[k][j];
          }
          array_c[i][j] = sum;
        }
      }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("summary array_c[1023][1023]:%f\n",array_c[1023][1023]);
  } else if (!strcmp(loop_type, "jki")) {        //same as 
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int j = 0 ; j < N ; j++) {
      for (int k = 0 ; k < N ; k++) {
        tmp = array_b[k][j];
        for (int i = 0 ; i < N ; i++) {
          array_c[i][j] += array_a[i][k]* tmp ;
        }
      }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
  } else if (!strcmp(loop_type, "ikj")) {         //same as kij
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int k = 0 ; k < N ; k++) {
      for (int i = 0 ; i < N ; i++) {
        tmp = array_a[i][k];
        for (int j = 0 ; j < N ; j++) {
          array_c[i][j] += tmp * array_b[k][j];
        }
      }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
  } 


  double elapsed_ns = calc_time(start_time, end_time);
  printf("Time=%f\n", elapsed_ns);

  for(int i = 0; i < N; i++) {
    free(array_a[i]);
    free(array_b[i]);
    free(array_c[i]);
  }

  free(array_a);
  free(array_b); 
  free(array_c);
 
}
