#include <iostream>
#include <vector>
#include <sys/time.h>
#include <stdlib.h>
#include <stdint.h>

double calc_time(struct timeval start, struct timeval end) {
  double start_sec = (double)start.tv_sec*1000000.0 + (double)start.tv_usec;
  double end_sec = (double)end.tv_sec*1000000.0 + (double)end.tv_usec;

  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}

int do_loops(const std::vector<std::vector<int>> &a, int N)  {
  int sum = 0 ;
  int threshold = 6; 
  if (threshold < 4) {   
    for (int j=0; j<N; j = j + 64) {
      for (int i = j ; i < (j + 64) ; i++) {
        sum = sum + a[i][0];
        sum = sum + a[i][1];
        sum = sum + a[i][2];
        sum = sum + a[i][3];
      }
    }
  } else {
    for (int j=0; j<N; j = j + 64) {
      for (int i = j ; i < (j + 64) ; i++) {
        sum = sum + a[i][0] + 1;
        sum = sum + a[i][1] + 1;
        sum = sum + a[i][2] + 1;
        sum = sum + a[i][3] + 1;
      }
    }
  }
  return sum;
}

int main(int argc, char *argv[])
{
  int i, sum, N;

  if (argc < 2) {
    std::cout << "Usage: ./func_inlining <array_size>" << std::endl;
    return -1;
  }

  N = atoi(argv[1]);

  if (N != 1000000) {
    std::cout << "Program argument must be 10,000,00." << std::endl;
    return -1;
  }

  std::vector<std::vector<int> > a(N, std::vector<int> (4));

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 4; j++){
      a[i][j] = 1;
    }
  }

  struct timeval start_time, end_time;
  gettimeofday(&start_time, NULL);
  sum = do_loops(a, N);
  gettimeofday(&end_time, NULL);

  std::cout << "Sum = " << sum << std::endl;

  double elapsed_us = calc_time(start_time, end_time);
  double elapsed_ms = elapsed_us / 1000.0;
  std::cout << "Time=" << elapsed_ms << " milliseconds" << std::endl;

  return 0;
}