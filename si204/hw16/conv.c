//Mike Hanling

#include <stdio.h>
#include <string.h>

typedef char cstring[128];

// lenUnitCF(fromUnit,toUnit) - this function returns
// conversion factors between different units of length
// for units it understands, and returns 0.0 for units
// it does not understand.
// It understands: feet, inches, yards, miles, millimeters,
// centimeters, meters, kilometers, nautical-miles and light-years.
double lenUnitCF(cstring fromUnit, cstring toUnit);

double toFeet(cstring fromUnit); // This just helps with lenUnitCF

int main()
{
  //---- YOUR CODE GOES HERE ---------------//

  double init = 0.0;  //the value inputted by user
  double final = 0.0;  //the value in the new unit
  cstring trash;  //for useless words
  cstring from;  //stores original unit
  cstring to;  //stores desired unit
  
  //scan in the user input
  scanf(" %s %lg %s %s %s", trash, &init, from, trash, to);

  //calculate the new value
  final = init*lenUnitCF(from, to);
  
  //print out the results
  printf("%g %s\n", final, to);


  return 0;
}

double lenUnitCF(cstring fromUnit, cstring toUnit) {
  return toFeet(fromUnit)/toFeet(toUnit);
}

double toFeet(cstring fromUnit) {
  if (strcmp(fromUnit, "feet") == 0) {
    return 1.0;
  } else if (strcmp(fromUnit, "inches") == 0) {
    return 1.0/12.0;
  } else if (strcmp(fromUnit, "yards") == 0) {
    return 3.0;
  } else if (strcmp(fromUnit, "miles") == 0) {
    return 5280;
  } else if (strcmp(fromUnit, "millimeters") == 0) {
    return 0.00328084;
  } else if (strcmp(fromUnit, "centimeters") == 0) {
    return 0.0328084;
  } else if (strcmp(fromUnit, "meters") == 0) {
    return 3.28084;
  } else if (strcmp(fromUnit, "kilometers") == 0) {
    return 3280.84;
  } else if (strcmp(fromUnit, "nautical-miles") == 0) {
    return 6076.12;
  } else if (strcmp(fromUnit, "light-years") == 0) {
    return 3.1038479e16;
  } else {
    return 0.0;
  }
}
