//Mike Hanling
//imgmod.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


typedef struct{
  int red;
  int green;
  int blue;
} pixel;

typedef struct{
  int width;
  int height;
  pixel** pixels;
} img;


int fread_int(FILE* in);
int fread_byte(FILE* in);
void fwrite_int(int data, FILE* out);
void fwrite_byte(unsigned char data, FILE* out);

void read_bmp_head(int* wptr, int* hptr, FILE* in);
void write_bmp_head(int width, int height, FILE* out);
void read_color(int* rptr, int* gptr, int*bptr, FILE* in);
void write_color(int red, int green, int blue, FILE* out);

void write_file(img input);
void flip_file(img* input);
void blood_file(img* input);
void mirror_file(img* input);
void blur_file(img* input);


int main() {
  //read and open input file
  char filename[128];
  printf("Input file: ");
  scanf(" %s", filename);
  FILE* fin = fopen(filename, "rb");

  //create the image in memory
  img input;
  read_bmp_head(&input.width, &input.height, fin);
  input.pixels = calloc(input.height, sizeof(pixel*));
  for (int y=0; y < input.height; ++y) {
    input.pixels[y] = calloc(input.width, sizeof(pixel));
    for (int x=0; x < input.width; ++x) {
      read_color(&input.pixels[y][x].red, 
                 &input.pixels[y][x].green, 
                 &input.pixels[y][x].blue, fin);
    }
  }


  //receive and execute commands
  char cmd[128];
  while (1) {
    printf("command: ");
    scanf(" %s", cmd);
    
    //delegate command to proper
    if (strcmp(cmd, "write") == 0) {
      write_file(input);
    }else if (strcmp(cmd, "flip") == 0) {
      flip_file(&input);
    }else if (strcmp(cmd, "blood") == 0) {
      blood_file(&input);
    }else if (strcmp(cmd, "mirror") == 0) {
      mirror_file(&input);
    }else if (strcmp(cmd, "blur") == 0) {
      blur_file(&input);
    }else break;
  }

  //free
  for (int i = 0; i < input.height; i++) {
    free(input.pixels[i]);
  }
  free(input.pixels);


  return 0;
}


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


void write_file(img input) {
  //read file out name
  char file[128];
  scanf(" %s", file);
  FILE* fout = fopen(file, "wb");

  //write file head
  write_bmp_head(input.width, input.height, fout);

  //write all of the pixels
  for (int y = 0; y < input.height; y++) {
    for (int x = 0; x < input.width; x++) {
      pixel pix = input.pixels[y][x];
      write_color(pix.red, pix.green, pix.blue, fout);
    }
  }
}


void flip_file(img* input) {
  //reverse the rows
  for (int i = 0; i < (input->height)/2; i++) {
    pixel* temp = input->pixels[input->height-1-i];
    input->pixels[input->height-1-i] = input->pixels[i];
    input->pixels[i] = temp;
  }
  //reverse the each row itself
  for (int y = 0; y < input->height; y++) {
    for (int x = 0; x < (input->width)/2; x++) {
      pixel temp = input->pixels[y][input->width-1-x];
      input->pixels[y][input->width-1-x] = input->pixels[y][x];
      input->pixels[y][x] = temp;
    }
  }
}


void blood_file(img* input) {
  for (int y = 0; y < input->height; y++) {
    for (int x = 0; x < input->width; x++) {
      
      //get total color value
      pixel pix = input->pixels[y][x];
      int sum = pix.red + pix.green + pix.blue;
      
      //check if pixel should become red or black
      if (sum > 255) {
        input->pixels[y][x].red = 255;
      }
      else {
        input->pixels[y][x].red = 0;
      }
      input->pixels[y][x].green = 0;
      input->pixels[y][x].blue = 0;

    }
  }
}


void mirror_file(img* input) {
  //double the height
  int oldheight = input->height;
  input->height *= 2;
  input->pixels = realloc(input->pixels, input->height * sizeof(pixel*));

  //double to image on top of each other
  for (int y = 0; y < oldheight; y++) {
    input->pixels[y+oldheight] = calloc(input->width, sizeof(pixel));
    for (int x = 0; x < input->width; x++) {
      input->pixels[y+oldheight][x] = input->pixels[y][x];
    }
  }

  //mirror the bottom half
  for (int i = 0; i < oldheight/2; i++) {
    pixel* temp = input->pixels[oldheight-1-i];
    input->pixels[oldheight-1-i] = input->pixels[i];
    input->pixels[i] = temp;
  }
}


void blur_file(img* input) {
  for (int y = 0; y < input->height; y++) {
    for (int x = 0; x < input->width; x++) {
      //initial variables
      int newr = 0;
      int newg = 0;
      int newb = 0;
      int ystart = -2;
      int yfin = 2;
      int xstart = -2;
      int xfin = 2;
      //checking and correctly for edge cases
      if (y < 2) {
        ystart = -y;
      }else if (y > input->height-3) {
        yfin = input->height-y-1;
      }
      if (x < 2) {
        xstart = -x;
      }else if (x > input->width-3) {
        xfin = input->width-x-1;
      }
      
      //create the blur
      for (int i = ystart; i <= yfin; i++) {
        for (int k = xstart; k <= xfin; k++) {
          newr += input->pixels[y+i][x+k].red;
          newg += input->pixels[y+i][x+k].green;
          newb += input->pixels[y+i][x+k].blue;
        }
      }
      newr /= (yfin-ystart+1)*(xfin-xstart+1);
      newg /= (yfin-ystart+1)*(xfin-xstart+1);
      newb /= (yfin-ystart+1)*(xfin-xstart+1);

      input->pixels[y][x].red = newr;
      input->pixels[y][x].green = newg;
      input->pixels[y][x].blue = newb;
    }
  }
}
