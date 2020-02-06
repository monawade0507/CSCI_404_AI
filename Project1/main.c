#include "uniformedSearch.h"

int main (int argc, char *argv[]) {

  // boolean checks to make sure all Parameters were passed in
  bool passedParameterCheck = false;

  // read in command line arguments and set variables used in find_route
  UniformedSearch obj;
  if (argv[1] != NULL) {
    obj.setFileName(argv[1]);
    printf("Store File Name: %s\n", obj.getFileName());
    passedParameterCheck = true;
  } else {
    printf("File Input Name Parameter Not Given\n");
    passedParameterCheck = false;
  }
  if (argv[2] != NULL) {
    obj.setOrginCity(argv[2]);
    printf("Store Origin City: %s\n", obj.getOriginCity());
    passedParameterCheck = true;
  } else {
    printf("Origin City Name Parameter Not Given\n");
    passedParameterCheck = false;
  }
  if (argv[3] != NULL) {
    obj.setDestinationCity(argv[3]);
    printf("Store Destination City: %s\n", obj.getDestinationCity());
    passedParameterCheck = true;
  } else {
    printf("Origin City Name Parameter Not Given\n");
    passedParameterCheck = false;
  }


  if (passedParameterCheck) {
    obj.readFile();
  } else {
    printf("Parameter Check Failed");
  }

  return 0;
}
