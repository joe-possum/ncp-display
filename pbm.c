#include <pbm.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

void load_file(const char *name, uint8_t *screen) {
  FILE *fh;
  assert((fh = pm_openr(name)));
  int cols, rows;
  unsigned char **bits;
  assert((bits = pbm_readpbm(fh, &cols, &rows)));
  assert(cols = 128);
  assert(rows = 128);
  for(int i = 0; i < rows; i++) {
    uint8_t byte = 0;
    for(int j = 0; j < cols; j++) {
      uint8_t bit = 1 << (j & 7);
      if(!bits[i][j]) byte |= bit;
      if(bit == 128) {
	screen[16*i+j/8] = byte;
	byte = 0;
      }
    }
  }
}

#ifdef TEST
int main (int argc, char *argv[]) {
  load_file(argv[1]);
  return;
}
#endif
