#include "uniformedSearch.h"

void UniformedSearch::setOrginCity (char city[40]) {
  strncpy(this->originCity, city, 40);
}

//--
void UniformedSearch::setDestinationCity (char city[40]) {
  strncpy(this->destinationCity, city, 40);
}

//--
void UniformedSearch::setFileName (char file[40]){
  strncpy(this->fileName, file, 40);
}

//--
char* UniformedSearch::getFileName() {
  return this->fileName;
}

//--
char* UniformedSearch::getDestinationCity() {
  return this->destinationCity;
}

//--
char* UniformedSearch::getOriginCity() {
  return this->originCity;
}

//-- Read contents of input file and create search tree
void UniformedSearch::readFile() {
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(this->fileName, "r");
  if (fp == NULL) {
    printf("Failed to open file: %s\n", this->fileName);
    exit(EXIT_FAILURE);
  }
  else {
    //printf("Successfully opened: %s\n", this->fileName);
  }

  // file is open
  int begin = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    // end of file detected
    if (strstr(line, "END OF INPUT") != NULL) {
      //printf("End of File Found\n");
      return;
    } else {
      
      // input city into the tree
      if (begin == 0) {
        // seperate the cities
        char * token = strtok(line, " ");
        int count = 0;

        char start[40];
        char end[40];
        char dist[40];
        while(token != NULL) {
            if (count == 0) {
              strcpy(start, token);
            }
            else if (count == 1) {
              strcpy(end, token);
            }
            else if (count == 2){
              strcpy(dist, token);
            }
            token = strtok(NULL, " ");
            count ++;
        }
        

        // create the beginning node
        strcpy(this->treeMap->name, start);
        this->treeMap->distance = 0;
        for (int i = 0; i < 10; i++) {
          this->treeMap->child[i] = NULL;
        }

        // add node to child array
        this->treeMap->child[0] = this->createNode(end, atoi(dist));

        // increment begin
        begin++;

        
      }
      // else not the beginning city for the map
      else {

        // seperate the cities
        char * token = strtok(line, " ");
        int count = 0;

        char otherStart[40];
        char otherEnd[40];
        char otherDist[40];
        while(token != NULL) {
            if (count == 0) {
              strcpy(otherStart, token);
            }
            else if (count == 1) {
              strcpy(otherEnd, token);
            }
            else if (count == 2){
              strcpy(otherDist, token);
            }
            token = strtok(NULL, " ");
            count ++;
        }
        
        this->insertChild(this->treeMap, otherStart, otherEnd, atoi(otherDist));
	            
        begin++;
      }
    }

  }
  fclose(fp);   // close file
}



// -- create Node
struct node* UniformedSearch::createNode(char* name, int dist) {

  struct node* newNode = (struct node *) malloc( sizeof(struct node));
  strcpy(newNode->name, name);
  newNode->distance = dist;

  // init all child potenial nodes to NULL
  for (int i = 0; i < 10; i++) {
    newNode->child[i] = NULL;
  }

  newNode->amountOfChildren = -1;

  return newNode;
}

// -- add Child node
void UniformedSearch::insertChild(struct node *root, char start[40], char end[40], int dist) {

  if (root == NULL)
    return;

  for (int i = 0; i < 10; i++) {
    if (root->child[i] != NULL) {
      if(strstr(root->child[i]->name, start) != NULL) {   // found
        root->child[i]->amountOfChildren++;
        int t = root->child[i]->amountOfChildren;
        root->child[i]->child[t] = createNode(end, dist);
      } else {
        insertChild(root->child[i], start, end, dist);
      }
    }
  }
}

// searching for an end node; testing existance
void UniformedSearch::searchTreeMap(struct node* testRoot, char start[40]) {

  for (int i = 0; i < 10; i++) {
    if (testRoot->child[i] != NULL) {
      if (strcmp(testRoot->name, start) == 0){
        this->found = true;  // found the test city in the current treeMap
      } else {
        searchTreeMap(testRoot->child[i], start);
      }
    }
  }

}

void UniformedSearch::showTreeMap(struct node* root) {
  if (root == NULL) {
    return;
  }
  printf("Current city ( %s ) has the following connected cities ... ", root->name);
  for (int i = 0; i < 10; i++) {
    if (root->child[i] != NULL && root->child[i]->name != NULL)
      printf (" %s ;", root->child[i]->name);
  }
 
  // need to look at each vaild child
  for (int i = 0; i < 10; i++) {
    if (root->child[i] != NULL && root->child != NULL) {
      this->showTreeMap(root->child[i]);
    } 
  }
}

void UniformedSearch::printPath (struct node* root, struct node* cont) {
  if (strcmp(root->name,this->originCity) == 0) {
    this->foundOrigin = true;
    strcpy(cont->name, this->originCity);
    cont->distance = root->distance;
    //printf("found Origin city ( %s  ) in tree \n", root->name);
  }
  if (strcmp(root->name, this->destinationCity) == 0) {
    this->foundDestination = true;
    // add the desination city to the path
    strcpy(cont->name, this->destinationCity);
    cont->distance = root->distance;
    //printf("Found destination city ( %s ) in tree \n", cont->name);
    return;
  }

  // need to look through treeMap
  for (int i = 0; i < 10; i++) {
    if (root->child[i] != NULL) {
      // two ways to move through tree
      if (this->foundDestination) {
        strcpy(cont->name, root->name);
        cont->distance = root->distance;
        return;
      }
      if (this->foundOrigin) {
        strcpy(cont->name, root->name);
        cont->distance = root->distance;
        cont->child[0] = (struct node*) malloc(sizeof(struct node));
        printPath(root->child[i], cont->child[0]);
      } else {
        printPath(root->child[i], cont);
      }
    }
  }
}

void UniformedSearch::calculate (struct node* root) {
  if (root == NULL) return;
 
  this->total += root->distance;
  this->calculate(root->child[0]);
}

void UniformedSearch::showPath (struct node* root) {
  if (root == NULL) return;
  
  printf("% s , %d km \n", root->name, root->distance);
  this->showPath(root->child[0]);
}
  
void UniformedSearch::start() {
  //showTreeMap(this->treeMap);
  // find the orgin and destination city in treeMap
  bool origin;
  bool dest;
  
  this->found = false;
  this->searchTreeMap(this->treeMap, this->originCity);
  origin = this->found;
  
  this->found = false;
  this->searchTreeMap(this->treeMap, this->destinationCity);
  dest = this->found;

  if (!origin || !dest) {
    printf("distance: infinity \n");
    printf("route: \n");
    printf("none \n");
    return;
  } 
  
  this->foundOrigin = false;
  this->foundDestination = false;
  this->action = 0;
  this->found = false;
  this->printPath(this->treeMap, this->path);

  if (!this->foundOrigin || !this->foundDestination) {
    printf("distance: infinity\n");
    printf("route: \n");
    printf("none \n");
    return;
  }

  // if all the above conditions fail, that means a path exist
  //printf("Path starts with ... %s \n", this->path->name);
  this->calculate(this->path);
  printf("distance: %d km \nroute: \n", this->total);
  this->showPath(this->path);
}
