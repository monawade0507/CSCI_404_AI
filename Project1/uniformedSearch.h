/*
  Implement a search algorithm that can find a route between any two cities.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// small node class to build tree structure
typedef struct node {
  char name[40];
  struct node *child[10];
  int distance;
  int amountOfChildren;
} node;



class UniformedSearch {

public:
  // read input.txt and build
  UniformedSearch () {
      char temp[40] = "No Information Stored";
      strncpy(this->fileName, temp, sizeof(temp));
      strncpy(this->originCity, temp, sizeof(temp));
      strncpy(this->destinationCity, temp, sizeof(temp));
      this->amountOfTreeMaps = 0;

      // allocate space for each treeMap
      for (int i = 0; i < 10; i++) {
        this->treeMap[i] = (struct node*) malloc( sizeof(struct node));
      }
  }

  void setOrginCity (char city[40]);
  void setDestinationCity (char city[40]);
  void setFileName (char file[40]);
  char* getFileName();
  char* getDestinationCity();
  char* getOriginCity();
  void readFile();
  struct node* createNode(char* name, int dist);
  void insertChild(struct node *root, char start[40], char end[40], int dist);
  bool searchTreeMap (struct node* testRoot, char start[40]);

private:
  char lastCheckedCity [40];
  char location = 0;
  char fileName[40];
  char originCity[40];
  char destinationCity[40];
  int amountOfTreeMaps;
  node* treeMap[10];
};
