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
              this->total = 0;
	      // allocate space for each treeMap
	      this->treeMap = (struct node*) malloc( sizeof(struct node));
              this->path = (struct node*) malloc (sizeof(struct node));
	  }

	  // Setters for the parameters that were passed in
	  void setOrginCity (char city[40]);
	  void setDestinationCity (char city[40]);
	  void setFileName (char file[40]);
	  // getters for the parameters that were passed in
  char* getFileName();
  char* getDestinationCity();
  char* getOriginCity();
  // read the input file and load treeMap
  void readFile();
  // used to assist creating new nodes to add to the treeMap
  struct node* createNode(char* name, int dist);
  // used to insert nodes into treeMap; this function calles createNode
  void insertChild(struct node *root, char start[40], char end[40], int dist);
  // determines wether or not a city can be found in treeMap
  void searchTreeMap (struct node* testRoot, char start[40]);
  // used to display the tree and determine if created correctly
  void showTreeMap (struct node* root);
  // used to call on the printPath function and any other helper functions necessary. 
  void start();
  // determines a path from the origin city to the destination city
  void printPath (struct node* root, struct node* cont);
  // print path that was store in node* path
  void showPath (struct node* root);
  // calculate the path distance
  void calculate (struct node* root);

private:
  bool found;
  char lastCheckedCity [40];
  char location = 0;
  char fileName[40];
  char originCity[40];
  char destinationCity[40];
  bool foundOrigin;
  bool foundDestination;
  int amountOfTreeMaps;
  node* treeMap;
  node* path;
  int action;
  int total;

};
