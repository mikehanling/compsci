//Mike Hanling
//replace.c

#include <stdio.h>
#include <assert.h>

typedef char cstring[128];

/****************************************************************
 * FUNCTION PROTOTYPES
 ****************************************************************/
int fread_int(FILE* in);
int fread_byte(FILE* in);
void fwrite_int(int data, FILE* out);
void fwrite_byte(unsigned char data, FILE* out);

void read_bmp_head(int* wptr, int* hptr, FILE* in);
void write_bmp_head(int width, int height, FILE* out);
void read_color(int* rptr, int* gptr, int*bptr, FILE* in);
void write_color(int red, int green, int blue, FILE* out);

/****************************************************************
 * MAIN FUNCTION
 ****************************************************************/
int main() {
  // read output filename
  cstring filein;
  printf("Input file: ");
  fflush(stdout);
  scanf(" %s", filein);
  cstring fileout;
  printf("Output file: ");
  fflush(stdout);
  scanf(" %s", fileout);

  FILE* fin = fopen(filein, "rb");
  if (! fin) {
    printf("ERROR: file not found\n");
    return 1;
  }
  FILE* fout = fopen(fileout, "wb");
  
  //replacement values
  int repR;
  int repG;
  int repB;
  printf("Replacement color values (RGB): ");
  fflush(stdout);
  if (scanf(" %i %i %i", &repR, &repG, &repB) != 3) {
    printf("ERROR: needs to be three ints");
    return 2;
  }
  
  // variables for important image parameters
  int width;
  int height;
  int fhlen = 14;
  int ihlen = 40;
  int fsize;
  int temp;

  //read and write file/image header
  read_bmp_head(&width, &height, fin);
  write_bmp_head(width, height, fout);

  /*//check file size
  int rowlen = width * 3;
  int pixlen = height * rowlen;
  assert (fsize == fhlen + ihlen + pixlen);*/
  
  //read and write each pixel
  for (int ycoord=0; ycoord < height; ++ycoord) {
    for (int xcoord=0; xcoord < width; ++xcoord) {
      int r;
      int g;
      int b;
      read_color(&r, &g, &b, fin);
      //change green to replacement value
      if (r == 0 && g == 255 && b == 0) {
        b = repB;
        g = repG;
        r = repR;
      }
      
      write_color(r, g, b, fout);
    }
  }
  
  // all done!
  fclose(fin);
  fclose(fout);
  printf("Image saved to %s\n", fileout);
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
}

void fwrite_int(int data, FILE* out) {
  fwrite(&data, sizeof(int), 1, out);
}

void fwrite_byte(unsigned char data, FILE* out) {
  fwrite(&data, sizeof(char), 1, out);
}

void read_bmp_head(int* wptr, int* hptr, FILE* in) {
  int temp;
  int fsize;
  int fhlen = 14;
  int ihlen = 40;

  // *READ* file header
  temp = fread_byte(in); // magic number part 1
  assert (temp == 'B');
  temp = fread_byte(in); // magic number part 2
  assert (temp == 'M');
  fsize = fread_int(in); // file size
  fread_int(in); // unused 4 bytes
  temp = fread_int(in); // pixels offset
  assert (temp == fhlen + ihlen);

  // *READ* image header
  temp = fread_int(in); // image header length
  assert (temp == ihlen);
  *wptr = fread_int(in); // image width
  *hptr = fread_int(in); // image height
  temp = fread_int(in); // 1 image plane, 24 bits per pixel
  assert (temp == 1 + (24 << 16));
  temp = fread_int(in); // compression type
  assert (temp == 0);
  fread_int(in); // image size (ignored)
  fread_int(in); // horiz resolution (ignored)
  fread_int(in); // vertical resolution (ignored)
  temp = fread_int(in); // color map entries used
  assert (temp == 0);
  fread_int(in); // # of "important" colors (ignored)
}

void write_bmp_head(int width, int height, FILE* out) {
  int fhlen = 14;
  int ihlen = 40;
  int rowlen = width * 3;
  int pixlen = height * rowlen;

  // *WRITE* file header
  fwrite_byte('B', out); // magic number part 1
  fwrite_byte('M', out); // magic number part 2
  fwrite_int(fhlen + ihlen + pixlen, out); // file size
  fwrite_int(0, out); // unused 4 bytes
  fwrite_int(fhlen + ihlen, out); // pixels offset

  // *WRITE* image header
  fwrite_int(ihlen, out); // image header length
  fwrite_int(width, out); // image width
  fwrite_int(height, out); // image height
  fwrite_int(1 + (24 << 16), out); // 1 image plane, 24 bits per pixel
  fwrite_int(0, out); // compression type
  fwrite_int(0, out); // image size (0 for uncompressed)
  fwrite_int(0, out); // horiz resolution (0 for default)
  fwrite_int(0, out); // vertical resolution (0 for default)
  fwrite_int(0, out); // color map entries used
  fwrite_int(0, out); // # of "important" colors (0 means all)
}


void read_color(int* rptr, int* gptr, int*bptr, FILE* in) {
  // *READ* pixel data
  *bptr = fread_byte(in);
  *gptr = fread_byte(in);
  *rptr = fread_byte(in);
}

void write_color(int red, int green, int blue, FILE* out) {
  // *WRITE* pixel data
  // note: pixels written in reverse order (BGR)
  fwrite_byte(blue, out);
  fwrite_byte(green, out);
  fwrite_byte(red, out);
}
