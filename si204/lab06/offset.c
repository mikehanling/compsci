// Mike Hanling
// offset.c

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

void xcrop_file(int xoffset, FILE* in);
void ycrop_file(int yoffset, int width, FILE* in);
void overlap(int width, FILE* forein, FILE* backin, FILE* fout);
void copy_background(int width, FILE* backin, FILE* fout);

void greenscreen_GO(FILE* forein, FILE* backin, FILE* fout, int xoff, int yoff);

/****************************************************************
 * MAIN FUNCTION
 ****************************************************************/
int main() {

  // read input and output filenames
  cstring fore;
  printf("Foreground file: ");
  fflush(stdout);
  scanf(" %s", fore);
  cstring back;
  printf("Background file: ");
  fflush(stdout);
  scanf(" %s", back);
  
  // read offset
  int xoff;
  int yoff;
  printf("Enter offset (XY): ");
  fflush(stdout);
  if (scanf(" %i %i", &xoff, &yoff) != 2) {
    printf("ERROR: neds to be two ints");
    return 1;
  }
  
  //read output file
  cstring fileout;
  printf("Output file: ");
  fflush(stdout);
  scanf(" %s", fileout);
  
  //open files to read from and write to
  FILE* forein = fopen(fore, "rb");
  if (! forein) {
    printf("ERROR: file not found\n");
    return 2;
  }
  FILE* backin = fopen(back, "rb");
  if (! backin) {
    printf("ERROR: file not found\n");
    return 3;
  }
  FILE* fout = fopen(fileout, "wb");


  /***Main Function***/
  greenscreen_GO(forein, backin, fout, xoff, yoff);


  // all done!
  fclose(forein);
  fclose(backin);
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

void xcrop_file(int xoffset, FILE* in) {
  //check for negative xoffset and reads in until starting column
  int trash = 0;
  while (xoffset < 0) {
    fread_byte(in); //B
    fread_byte(in); //G
    fread_byte(in); //R
    xoffset++;
  }
}

void ycrop_file(int yoffset, int width, FILE* in) {
  //check for negative yoffset and reads in until starting row
  int trash = 0;
  while (yoffset < 0) {
    xcrop_file(-width, in);  //negative width bc xcrop takes a neg
    yoffset++;
  }
}

void overlap(int width, FILE* forein, FILE* backin, FILE* fout) {
  for (int xcoord=0; xcoord < width; ++xcoord) {
    int rfore;
    int gfore;
    int bfore;
    int rback;
    int gback;
    int bback;
    read_color(&rfore, &gfore, &bfore, forein);
    read_color(&rback, &gback, &bback, backin);

    //change green to replacement value
    if (rfore == 0 && gfore == 255 && bfore == 0) {
      bfore = bback;
      gfore = gback;
      rfore = rback;
    }
    
    write_color(rfore, gfore, bfore, fout);
  }
}

void copy_background(int width, FILE* backin, FILE* fout) {
  if (width <= 0) {
    return;
  }else {
    for (int xcoord=0; xcoord < width; ++xcoord) {
      int rfore;
      int gfore;
      int bfore;
      int rback;
      int gback;
      int bback;
      read_color(&rfore, &gfore, &bfore, backin);
      write_color(rfore, gfore, bfore, fout);
    }
  }
}

void greenscreen_GO(FILE* forein, FILE* backin, FILE* fout, int xoff, int yoff) {

  // variables for important image parameters
  int forewidth;
  int foreheight;
  int backwidth;
  int backheight;
  int fhlen = 14;
  int ihlen = 40;
  int fsize;
  int temp;

  //read and write file/image header
  read_bmp_head(&forewidth, &foreheight, forein);
  read_bmp_head(&backwidth, &backheight, backin);
  write_bmp_head(backwidth, backheight, fout);


  //format foreground if part is out of view (y direction)
  ycrop_file(yoff, forewidth, forein);


  //read and write each pixel
  
  for (int ycoord=0; ycoord < backheight; ++ycoord) {
    
    //if line with foreground image
    if (ycoord >= (yoff) && ycoord < (yoff+foreheight)) {
      
      //crop if need be
      xcrop_file(xoff, forein);

      //up until foreground image just take the background
      copy_background(xoff, backin, fout);
      
      //if the foreground goes beyond the background width
      if (backwidth < (xoff+forewidth)) {

        //just overlap for remaining width
        overlap(backwidth-xoff, forein, backin, fout);

        //read in the unused pixel info from the foreground
        xcrop_file(-forewidth-xoff+backwidth, forein); //needs to be neg
      
      //otherwise...
      }else {
        //take foreground; swap green pixels for background
        overlap(forewidth, forein, backin, fout);

        //for the rest of the line take the background
        copy_background(backwidth-(xoff+forewidth), backin, fout);
      }

    //otherwise just take the background image for the line  
    }else {
      copy_background(backwidth, backin, fout);
    }
  }
}
