/*
 * This program uses sieve method to find prime numbers between
 * 3 and 2(N - 1) + 3 inclusive.
 */
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define N 10000000
#define NOT_A_PRIME 0
#define IS_A_PRIME 1
#define IS_PRIME(X) is_prime(sieve, N, X)

/*
 * @param sieve an array used to indicate if 2 * index + 3 is a prime
 *  number or not.
 * @param n, the number of elements of the array.
 */
void
get_primes(char* sieve, int n) {
  assert(n <= N);
  int i;
  for (i = 0; i < n; i++) {
    sieve[i] = IS_A_PRIME;
  }

  /* take some example to see why floor(n / 2) can be use to bound. */
  /* or do the math to see that. */
  int j;
  int prime;
  int half_n = n >> 1;
  for (i = 0; i < half_n; i++) {
    if (sieve[i] == IS_A_PRIME) {
      /* remove the multiples of sieve[i], do the math to see why
       * the indexes are those used.
       */
      prime = i + i + 3;
      for (j = prime + i; j < n; j += prime) {
        sieve[j] = NOT_A_PRIME;
      }
    }
  }
}

int
is_prime(char* sieve, int n, int num) {
  if (num < 2) {
    return NOT_A_PRIME;
  }
  if (num == 2) {
    return IS_A_PRIME;
  }
  if ((num & 0x1) == 0) {
    return NOT_A_PRIME;
  }
  if (num <= ((n - 1) << 1) + 3) {
    return sieve[(num - 3) >> 1];
  }
  int sq_root = (int)sqrt((double)num);
  int prime;
  int i;
  for (i = 0; i < n; i++) {
    prime = i + i + 3;
    if (prime > sq_root) {
      break;
    }
    if (sieve[i] == IS_A_PRIME) {
      if (num % prime == 0) {
        return NOT_A_PRIME;
      }
    }
  }
  return IS_A_PRIME;
}

int
main(int argc, char** argv) {
  char sieve[N];
  get_primes(sieve, N);
  int count = 0;
  int i;
  for (i = 0; i < N; i++) {
    if (sieve[i] == IS_A_PRIME) {
      //printf("%d\n", i + i + 3);
      count++;
    }
  }
  /* plus 2, which is not indicated with the array. */
  printf("num of primes: %d\n", count + 1);

  printf("is 2333 a prime number? %d\n", IS_PRIME(2333));

  return 0;
}
