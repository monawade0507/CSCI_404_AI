#include "uniformedSearch.h"

int main (int argc, char *argv[]) {

  // boolean checks to make sure all Parameters were passed in
  bool passedParameterCheck = false;

  // read in command line arguments and set variables used in find_route
  /*
    The order of the argumenrs are required. The code will report if the arguments
    are not given. It does not verify if a text file is given vs a city name.
  */

  /* The below obj links to the other 2 C files: uninformedSearch.c and uninformedSearch.h .
     The class structure exist on uniformedSearch.h while the implementation of each function
     and method exist on uninformedSearch.c
  */
  UniformedSearch obj;
  if (argv[1] != NULL) {
    obj.setFileName(argv[1]);
    //printf("Store File Name: %s\n", obj.getFileName());
    passedParameterCheck = true;
  } else {
    printf("File Input Name Parameter Not Given\n");
    passedParameterCheck = false;
  }
  if (argv[2] != NULL) {
    obj.setOrginCity(argv[2]);
    //printf("Store Origin City: %s\n", obj.getOriginCity());
    passedParameterCheck = true;
  } else {
    printf("Origin City Name Parameter Not Given\n");
    passedParameterCheck = false;
  }
  if (argv[3] != NULL) {
    obj.setDestinationCity(argv[3]);
    //printf("Store Destination City: %s\n", obj.getDestinationCity());
    passedParameterCheck = true;
  } else {
    printf("Origin City Name Parameter Not Given\n");
    passedParameterCheck = false;
  }

  /* 
     Depending on if all the parameters where provided, the code will continue to read the
     provided input file and build the dependent data structure
  */
  if (passedParameterCheck) {
    obj.readFile();
  } else {
    printf("Parameter Check Failed");
  }

  /* 
    After the input file information had been injested, the start function looks for the 
    origin and destination cities. Once those are confirmed to exist inside the built tree
    data structure, the program will continue to evaluate a path
  */
  obj.start();

  return 0;
}
