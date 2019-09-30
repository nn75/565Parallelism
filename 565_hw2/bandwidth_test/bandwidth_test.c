#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t *array_a;
uint64_t *array_b;
uint64_t *array_c;

double calc_time(struct timespec start, struct timespec end) {
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;

  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}

void init_array_a(uint64_t size_a){
  uint64_t num_a = 0;
  array_a = (uint64_t*)malloc(size_a * sizeof(uint64_t));
  for(int i = 0 ; i < size_a ; i++) {
    array_a[i] = num_a;
  }
} 

void init_array_b(uint64_t size_b){
  uint64_t num_b = 0;
  array_b = (uint64_t*)malloc(size_b * sizeof(uint64_t));
  for(int i = 0 ; i < size_b ; i++) {
    array_b[i] = num_b;
  }
} 

void init_array_c(uint64_t size_c){
  uint64_t num_c = 0;
  array_c = (uint64_t*)malloc(size_c * sizeof(uint64_t));
  for(int i = 0 ; i < size_c ; i++) {
    array_c[i] = num_c;
  }
} 


int main(int argc, char *argv[]) {
  
  if (argc != 4) {
    printf("Syntax Error: bandwidth_test <pattern type> <array_size> <num_tranversal>\n");
    exit(EXIT_FAILURE);
  }
  
  int pattern_type = 0;
  int array_size = 0;
  int num_traversal = 0;
  pattern_type = atoi(argv[1]);
  array_size = atoi(argv[2]);
  num_traversal = atoi(argv[3]);
  if (pattern_type != 1 && pattern_type != 2 && pattern_type != 3 ){
    printf("Pattern Type Error: input 1 or 2 or 3\n");
    exit(EXIT_FAILURE);
  }

  struct timespec start_time, end_time;

  //uint64_t element = 1;
  if (pattern_type == 1) {
    init_array_a(array_size);
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int j = 0; j < num_traversal ; j++) {
      for (int i=0; i < array_size ; i++) {
        array_a[i] = 1;
      }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    free(array_a);
  } else if (pattern_type == 2) {
    init_array_a(array_size/2);
    init_array_b(array_size/2);
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int j = 0; j < num_traversal ; j++) {
      for (int i = 0; i < array_size/2 ; i++) {
        array_a[i] = array_b[i];
      }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    free(array_a);
    free(array_b);
  } else if (pattern_type == 3) {
    init_array_a(array_size/3);
    init_array_b(array_size/3);
    init_array_c(array_size/3);
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int j = 0; j < num_traversal ; j++) {
      for (int i = 0; i < array_size/3 ; i++) {
        array_a[i] = array_b[i] + array_c[i];
      }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    free(array_a);
    free(array_b);
    free(array_c);
  }

  double elapsed_ns = calc_time(start_time, end_time);
  double byte_num = array_size * num_traversal * sizeof(uint64_t);

  printf("Time=%f\n", elapsed_ns);
  printf("Data size = %f\n", byte_num);
  printf("Bandwidth=%f\n", 1000000000 * (byte_num/elapsed_ns) / (1024 * 1024 * 1024));
  
}
