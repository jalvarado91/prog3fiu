#include <stdio.h>
#include <sys/time.h>

/* Return 1 if 'i'th bit of 'n' is 1; 0 otherwise */
#define EXTRACT_BIT(n,i) ((n&(1<<i))?1:0)

int check_circuit (int z) {
  int v[16];        /* Each element is a bit of z */
  int i;

  for (i = 0; i < 16; i++) v[i] = EXTRACT_BIT(z,i);
  if ((v[0] || v[1]) && (!v[1] || !v[3]) && (v[2] || v[3])
      && (!v[3] || !v[4]) && (v[4] || !v[5])
      && (v[5] || !v[6]) && (v[5] || v[6])
      && (v[6] || !v[15]) && (v[7] || !v[8])
      && (!v[7] || !v[13]) && (v[8] || v[9])
      && (v[8] || !v[9]) && (!v[9] || !v[10])
      && (v[9] || v[11]) && (v[10] || v[11])
      && (v[12] || v[13]) && (v[13] || !v[14])
      && (v[14] || v[15])) {
    printf ("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",
	    v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],
	    v[10],v[11],v[12],v[13],v[14],v[15]);
    return 1;
  } else return 0;
}

int main (int argc, char *argv[]) 
{
  int count, i;
  struct timeval t1, t2;

  gettimeofday(&t1, 0);
  count = 0;
  for (i = 0; i < 65536; i++)
    count += check_circuit (i);
  gettimeofday(&t2, 0);

  printf ("Execution time %fs\n", (t2.tv_sec-t1.tv_sec)+(t2.tv_usec-t1.tv_usec)*1e-6);
  printf ("There are %d solutions\n", count);
  return 0;
}
