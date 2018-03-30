/* SI204 Spring 2017
 * Lab 6: Green screening
 * Starter code from Dr. Roche
 */

#include <stdio.h>
#include <assert.h>

typedef char cstring[128];

/****************************************************************
 * FUNCTION PROTOTYPES
 ****************************************************************/
int fread_int(FILE* in);
int fread_byte(FILE* in);

/****************************************************************
 * MAIN FUNCTION
 ****************************************************************/
int main() {
  // read input filename
  cstring filename;
  printf("Filename: ");
  fflush(stdout);
  scanf(" %s", filename);

  FILE* fin = fopen(filename, "rb");
  if (! fin) {
    printf("ERROR: file not found\n");
    return 1;
  }

  // variables for important image parameters
  int width;
  int height;
  int fhlen = 14;
  int ihlen = 40;
  int fsize;
  int temp;

  // read file header
  temp = fread_byte(fin); // magic number part 1
  assert (temp == 'B');
  temp = fread_byte(fin); // magic number part 2
  assert (temp == 'M');
  fsize = fread_int(fin); // file size
  fread_int(fin); // unused 4 bytes
  temp = fread_int(fin); // pixels offset
  assert (temp == fhlen + ihlen);

  // read image header
  temp = fread_int(fin); // image header length
  assert (temp == ihlen);
  width = fread_int(fin); // image width
  height = fread_int(fin); // image height
  temp = fread_int(fin); // 1 image plane, 24 bits per pixel
  assert (temp == 1 + (24 << 16));
  temp = fread_int(fin); // compression type
  assert (temp == 0);
  fread_int(fin); // image size (ignored)
  fread_int(fin); // horiz resolution (ignored)
  fread_int(fin); // vertical resolution (ignored)
  temp = fread_int(fin); // color map entries used
  assert (temp == 0);
  fread_int(fin); // # of "important" colors (ignored)

  // check file size
  int rowlen = width * 3;
  int pixlen = height * rowlen;
  assert (fsize == fhlen + ihlen + pixlen);

  // count yellow pixels
  int allpix = 0;
  int yellowpix = 0;

  // pixel data
  for (int ycoord=0; ycoord < height; ++ycoord) {
    for (int xcoord=0; xcoord < width; ++xcoord) {
      // note: pixels written in reverse order (BGR)
      int b = fread_byte(fin);
      int g = fread_byte(fin);
      int r = fread_byte(fin);
      ++allpix;
      // yellow pixel = red+green
      if (r == 255 && g == 255 && b == 0) {
        ++yellowpix;
      }
    }
  }

  // all done!
  fclose(fin);
  printf("%i out of %i pixels in %s are yellow.\n",
         yellowpix, allpix, filename);
  return 0;
}

/****************************************************************
 * FUNCTION DEFINITIONS
 ****************************************************************/

int fread_int(FILE* in) {
  int ans;
  fread(&ans, sizeof(int), 1, in);
  return ans;
}

int fread_byte(FILE* in) {
  unsigned char ans;
  fread(&ans, sizeof(char), 1, in);
  return ans;
};
