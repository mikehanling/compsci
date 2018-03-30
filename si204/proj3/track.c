//Mike Hanling
//track.c
//use the following to compile:
//gcc -I/usr/include/libxml2 $(pkg-config --cflags gtk+-3.0) track.c gps.c
//-lxml2 $(pkg-config --libs gtk+-3.0) -o track -lm
    


#include "gps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include <math.h>
#include <libxml/parser.h>


typedef struct tm tm;

typedef struct{
  gpsco coord;
  tm time;
}waypt;

typedef struct{
  double x;
  double y;
}pt;

typedef struct node node;
struct node{
  waypt data;
  pt xyvals;
  node* next;
};

typedef struct{
  gpsco coord;
  double dist;
  char name[128];
}landmark;


node* open_new_file(int* numwaypts);
node* add2front(waypt data, node* list);
node* read_wps(FILE* fin, int numwaypts);
node* read_xml(xmlDoc* doc, int* numwaypts);
void get_stats(node* waypts, int numwaypts);
void to_landmarks(node* waypts, int numwaypts);
void get_fastest(node* waypts, int numwaypts);
void convert2relative(node* waypts, int numwaypoints);
void create_visual(node* waypts);
void activate(GtkApplication* app, gpointer user_data);
void draw_lines(GtkWidget* widget, cairo_t *cr, gpointer user_data);

void selectionSort(landmark* data, int size);
int before(double a, double b);
void free_list(node* L);

int main() {
  //open file and read in all data
  int numwp = 0;
  node* waypts = open_new_file(&numwp);

  //execute commands
  char cmd[128];
  while (1) {
    printf("command: ");
    scanf(" %s", cmd);

    if (strcmp(cmd, "quit") == 0) {
      break;
    }else if (strcmp(cmd, "stats") == 0) {
      get_stats(waypts, numwp);
    }else if (strcmp(cmd, "landmarks") == 0) {
      to_landmarks(waypts, numwp);
    }else if (strcmp(cmd, "fastest") == 0) {
      get_fastest(waypts, numwp);
    }else if (strcmp(cmd, "linked") == 0) {
      printf("yes\n");
    }else if(strcmp(cmd, "visual") == 0) {
      convert2relative(waypts, numwp);
      create_visual(waypts);
    }else if (strcmp(cmd, "file") == 0) {       //change source file
      waypts = open_new_file(&numwp);
    }else {
      printf("ERROR: command not recognized.\n");
      return 1;
    }
  }

  //free calloc calls
  free_list(waypts);
  return 0;
}


node* open_new_file(int* numwaypts) {
  //get file to read from
  char filename[128];
  printf("File: ");
  scanf(" %s", filename);
  node* wps;
  
  //check for .gpx
  if (strstr(filename, "gpx") != NULL) {
    //make Doc file
    xmlDoc* doc = xmlReadFile(filename, NULL, 0);
    //read all waypoints
    wps = read_xml(doc, numwaypts);
    xmlFreeDoc(doc);
  }else {
    //assume .txt and open
    FILE* fin = fopen(filename, "r");
    fscanf(fin, " %i", numwaypts);
    //read all waypoints
    wps = read_wps(fin, *numwaypts);
    fclose(fin);
  }
  printf("Opened %s with %i waypoints\n", filename, *numwaypts);

  //return the LL of all waypoints
  return wps;
}


node* add2front(waypt data, node* list) {
  node* temp = calloc(1, sizeof(node));
  temp->data = data;
  temp->next = list;
  return temp;
}

node* read_wps(FILE* fin, int numwaypts) {
  //make ending NULL
  node* list = calloc(1, sizeof(node));
  
  //for each of the data lines
  for (int i = 0; i < numwaypts; i++) {
    //store all info
    double lat, lon;
    double yr, mon, day;
    double hr, min, sec;
    fscanf(fin, " %lg %lg %lg-%lg-%lg %lg:%lg:%lg", 
                &lat, &lon, &yr, &mon, &day, &hr, &min, &sec);    
    
    //make the current waypoint
    waypt temp;
    temp.coord = make_gps(lat, lon);
    temp.time.tm_year = yr;
    temp.time.tm_mon = mon;
    temp.time.tm_mday = day;
    temp.time.tm_hour = hr;
    temp.time.tm_min = min;
    temp.time.tm_sec = sec;
   
    //add the waypoint to the LL
    list = add2front(temp, list);
  }  

  //return LL of all waypts
  return list;
}


node* read_xml(xmlDoc* doc, int* numwaypts) {
  //reset to restart size at zero for new file
  *numwaypts = 0;
  node* list = calloc(1, sizeof(node));
  
  //get root for file
  xmlNode* root = xmlDocGetRootElement(doc);

  //skip child "metadata" and "text" and go to "trk"
  xmlNode* trk = root->children->next->next->next;

  //within "trk", skip "name" and "text" and go to "trkseg"
  xmlNode* trkseg = trk->children->next->next->next;

  //get all children (trkpts) to go through
  xmlNode* trkpts = trkseg->children->next;

  //run though each of the children
  while (trkpts) {
    waypt temp;

    //read in attributes (lat, lon)
    xmlAttr* attr = trkpts->properties;

    //read in "lat" and "lon"
    double lat;
    sscanf((char*)attr->children->content, " %lg", &lat);
    double lon;
    sscanf((char*)attr->next->children->content, " %lg", &lon);
    temp.coord = make_gps(lat, lon);

    //skip "elevation" and "text" and go to "time"
    xmlNode* time = trkpts->children->next->next->next;

    //read in time
    double yr, mon, day;
    double hr, min, sec;
    sscanf((char*)time->children->content, " %lg-%lg-%lgT%lg:%lg:%lgZ", 
                  &yr, &mon, &day, &hr, &min, &sec);
    temp.time.tm_year = yr;
    temp.time.tm_mon = mon;
    temp.time.tm_mday = day;
    temp.time.tm_hour = hr;
    temp.time.tm_min = min;
    temp.time.tm_sec = sec;

    //copy to list
    list = add2front(temp, list);

    //skip "text" and go to next "trkpt"
    trkpts = trkpts->next->next;
    *numwaypts += 1;
  }

  //return LL of all waypts
  return list;
}


void get_stats(node* waypts, int numwaypts) {
  int time = 0;
  double dist = 0;
  
  //use a copy of the LL
  node* temp = waypts;

  //for every node
  for (int i = 0; i < numwaypts-1; i++) {
    //update time and distance it takes to get to the next node
    time += difftime(mktime(&temp->data.time), mktime(&temp->next->data.time));
    dist += gps_dist(temp->data.coord, temp->next->data.coord);
    temp = temp->next;
  }
 
  //calculate stats
  int secs = time % 60;
  int mins = (time/60) % 60;
  int hrs = time / 3600;
  double speed = dist/time*3600;         //conversion to go from secs to hrs
  int pmin = time/dist/60;               //minutes for pace
  double psec = (time/dist) - (pmin*60); //seconds for pace

  //print out stats (accounting for how big the time is)
  if (hrs > 0) {
    printf("Total time: %i hours, %i minutes, %i seconds\n", hrs, mins, secs);
  }else printf("Total time: %i minutes, %i seconds\n", mins, secs);
  printf("Total distance: %g miles\n", dist);
  printf("Average speed: %g mph\n", speed);
  printf("Average pace: %i minutes, %g seconds per mile\n", pmin, psec);
}


void to_landmarks(node* waypts, int numwaypts) {
  //get file
  char file[128];
  scanf(" %s", file);
  FILE* fin = fopen(file, "r");

  //get number of landmarks
  int lnum;
  fscanf(fin, " %i", &lnum);

  //read in landmarks
  landmark lms[lnum];
  for (int i = 0; i < lnum; i++) {
    landmark temp;
    double lat, lon;
    char name[128];
    fscanf(fin, " %lg %lg %s", &lat, &lon, name);
    temp.coord = make_gps(lat, lon);
    strcpy(temp.name, name);
    
    //calculate shortest distance
    temp.dist = gps_dist(waypts->data.coord, temp.coord);
    node* list = waypts->next;
    for (int k = 1; k < numwaypts; k++) {
      //keep this time if it is shorter than the stored one
      if (gps_dist(list->data.coord, temp.coord) < temp.dist) {
        temp.dist = gps_dist(list->data.coord, temp.coord);
      }
      list = list->next;
    }

    lms[i] = temp;
  }

  //close file
  fclose(fin);

  //sort by dist least to greatest
  selectionSort(lms, lnum);

  //print out
  for (int i = 0; i < lnum; i++) {
    printf("%s %g miles\n", lms[i].name, lms[i].dist);
  }
}


void get_fastest(node* waypts, int numwaypts) {
  //read in distance
  double target = 0;
  scanf(" %lg", &target);

  double sec = 0;       //current seconds
  double besttime = 0;  //lowest seconds found
  double dist = 0;      //current distance traversed
  node* front = waypts; //keeping track of forward most value
  node* back = waypts;  //keeping track of back most value

  //from first way point, count up time until target mileage
  //this is the initial window
  do {
    sec += difftime(mktime(&front->data.time), mktime(&front->next->data.time));
    dist += gps_dist(front->data.coord, front->next->data.coord);
    front = front->next;
  } while (dist < target && front->next);
  besttime = sec;

  //slide the window one waypt at a time
  //for (int i = 0; front->next; i++) {
  while (front->next) {
    //subtract front most dist/time
    sec -= difftime(mktime(&back->data.time), mktime(&back->next->data.time));
    dist -= gps_dist(back->data.coord, back->next->data.coord);
    back = back->next;
    
    //add one as many more waypoints are necessary
    while (dist < target && front->next) {
      sec += difftime(mktime(&front->data.time), mktime(&front->next->data.time));
      dist += gps_dist(front->data.coord, front->next->data.coord);
      front = front->next;
    }

    //check if this window has a better time
    if (sec < besttime) besttime = sec;
  }
  
  //print result
  int bt = besttime;  //cast to int for conversions
  if (bt < 60) printf("%i seconds\n", bt);
  else if (bt < 3600) {
    printf("%i minutes, %i seconds\n", bt/60, bt%60);
  }else {
    printf("%i hours, %i minutes, %i seconds\n", bt/3600, 
                                                 (bt/60)%60, 
                                                 bt%60);
  }
}


void convert2relative(node* waypts, int numwaypoints) {
  //use first node in LL for baseline
  double north = gps_latdeg(waypts->data.coord);
  double south = gps_latdeg(waypts->data.coord);
  double east = gps_londeg(waypts->data.coord);
  double west = gps_londeg(waypts->data.coord);
  
  //get farthest lat/lon
  for (node* temp = waypts->next; temp->next; temp = temp->next) {
    gpsco coord = temp->data.coord;
    if (gps_latdeg(coord) > north) {
      north = gps_latdeg(coord);
    }
    if (gps_latdeg(coord) < south) {
      south = gps_latdeg(coord);
    }
    if (gps_londeg(coord) < west) {
      west = gps_londeg(coord);
    }
    if (gps_londeg(coord) > east) {
      east = gps_londeg(coord);
    }
  }

  //calulate scale to use
  double nsdiff = north - south;
  double nsscale = 799 / nsdiff;
  double ewdiff = east - west;
  double ewscale = 799 / ewdiff;

  //calculate pixel locations for visual and store within struct
  for (node* temp = waypts; temp->next; temp = temp->next) {
    temp->xyvals.x = (gps_londeg(temp->data.coord) - west) * ewscale;
    temp->xyvals.y = (north - gps_latdeg(temp->data.coord)) * nsscale;
  }

}    


void create_visual(node* waypts) {
  
  //set up file for visual
  GtkApplication* app = gtk_application_new("my.map.app", G_APPLICATION_FLAGS_NONE);
  
  //call the activate function to draw the lines between waypts
  g_signal_connect(app, "activate", G_CALLBACK(activate), (gpointer)waypts);

  //display visual
  g_application_run(G_APPLICATION (app), 0, NULL);

  //destroy file
  g_object_unref(app);
}


void activate(GtkApplication* app, gpointer user_data) {
  //create the window
  GtkWidget* window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), "Map");

  //make the drawing canvas
  GtkWidget* drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, 800, 800);
  gtk_container_add(GTK_CONTAINER(window), drawing_area);

  //call drawing function
  g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_lines), user_data);

  //display it
  gtk_widget_show_all(window);
}


void draw_lines(GtkWidget* widget, cairo_t *cr, gpointer user_data) {
  //cast user_data
  node* waypts = user_data;

  //blue, 2-pt line
  cairo_set_source_rgb(cr, 0, 0, 255);
  cairo_set_line_width(cr, 2.0);

  //set inital point
  cairo_move_to(cr, round(waypts->xyvals.x), round(waypts->xyvals.y));

  //draw lines (making sure there is one more plus the last node
  while (waypts->next->next) {
    cairo_line_to(cr, round(waypts->next->xyvals.x), round(waypts->next->xyvals.y));
    waypts = waypts->next;
  }

  //display path
  cairo_stroke(cr);

}


void selectionSort(landmark* data, int size) {
  for(int length = size; length > 1; --length) {
    // Find imax, the index of the largest
    int imax = 0;
    for(int i = 1; i < length; ++i) {
      if (before(data[imax].dist, data[i].dist)) {
        imax = i;
      }
    }
    // Swap data[imax] & the last element
    landmark temp = data[imax];
    data[imax] = data[length - 1];
    data[length - 1] = temp;
  }
}

//this is make array sorted least to greatest
int before(double a, double b) {
  return a < b;
}


void free_list(node* L) {
  if (L) {
    free_list(L->next);
    free(L);
  }
}
