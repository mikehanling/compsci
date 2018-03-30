/* SI204 Spring 2017
 * Lab 6: Green screening
 * Starter code from Dr. Roche
 */

#include <stdio.h>

typedef char cstring[128];

/****************************************************************
 * FUNCTION PROTOTYPES
 ****************************************************************/
void fwrite_int(int data, FILE* out);
void fwrite_byte(unsigned char data, FILE* out);

/****************************************************************
 * MAIN FUNCTION
 ****************************************************************/
int main() {
  // read output filename
  cstring filename;
  printf("Filename: ");
  fflush(stdout);
  scanf(" %s", filename);

  FILE* fout = fopen(filename, "wb");

  // compute image parameters
  int width = 80;
  int height = 160;
  int fhlen = 14;
  int ihlen = 40;
  int rowlen = width * 3;
  int pixlen = height * rowlen;

  // file header
  fwrite_byte('B', fout); // magic number part 1
  fwrite_byte('M', fout); // magic number part 2
  fwrite_int(fhlen + ihlen + pixlen, fout); // file size
  fwrite_int(0, fout); // unused 4 bytes
  fwrite_int(fhlen + ihlen, fout); // pixels offset

  // image header
  fwrite_int(ihlen, fout); // image header length
  fwrite_int(width, fout); // image width
  fwrite_int(height, fout); // image height
  fwrite_int(1 + (24 << 16), fout); // 1 image plane, 24 bits per pixel
  fwrite_int(0, fout); // compression type
  fwrite_int(0, fout); // image size (0 for uncompressed)
  fwrite_int(0, fout); // horiz resolution (0 for default)
  fwrite_int(0, fout); // vertical resolution (0 for default)
  fwrite_int(0, fout); // color map entries used
  fwrite_int(0, fout); // # of "important" colors (0 means all)

  // pixel data
  for (int ycoord=0; ycoord < height; ++ycoord) {
    for (int xcoord=0; xcoord < width; ++xcoord) {
      // yellow pixel = red+green
      int r = 255;
      int g = 255;
      int b = 0;
      // note: pixels written in reverse order (BGR)
      fwrite_byte(b, fout);
      fwrite_byte(g, fout);
      fwrite_byte(r, fout);
    }
  }

  // all done!
  fclose(fout);
  printf("Image saved to %s\n", filename);
  return 0;
}

/****************************************************************
 * FUNCTION DEFINITIONS
 ****************************************************************/

void fwrite_int(int data, FILE* out) {
  fwrite(&data, sizeof(int), 1, out);
}

void fwrite_byte(unsigned char data, FILE* out) {
  fwrite(&data, sizeof(char), 1, out);
}
