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
    printf("Successfully opened: %s\n", this->fileName);
  }

  // file is open
  int begin = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    // end of file detected
    if (strstr(line, "END OF INPUT") != NULL) {
      printf("End of File Found\n");
      return;
    } else {
      // printf("line: %s\n", line);
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
        // printf("Start city: %s\n", start);
        // printf("End city: %s\n", end);
        // printf("Distance: %s\n", dist);

        // create the beginning node
        strcpy(this->treeMap[this->amountOfTreeMaps]->name, start);
        this->treeMap[this->amountOfTreeMaps]->distance = 0;
        for (int i = 0; i < 10; i++) {
          this->treeMap[this->amountOfTreeMaps]->child[i] = NULL;
        }

        // add node to child array
        this->treeMap[this->amountOfTreeMaps]->child[0] = this->createNode(end, atoi(dist));

        // increment begin
        begin++;

        // check treeMap
        printf("TreeMap conains the top city: %s ; The distance associated with the top city %d ; The child city: %s ; The distance between the child city and the parent: %d \n", this->treeMap[this->amountOfTreeMaps]->name, this->treeMap[this->amountOfTreeMaps]->distance, this->treeMap[this->amountOfTreeMaps]->child[0]->name, this->treeMap[this->amountOfTreeMaps]->child[0]->distance);
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
        printf("\n");
        // printf("Other Start city: %s\n", otherStart);
        // printf("Other End city: %s\n", otherEnd);
        // printf("Other Distance: %s\n", otherDist);

        // need to look for 'otherStart' in treeMap before doing insertion
        if (searchTreeMap(this->treeMap[this->amountOfTreeMaps], otherStart) ||
            searchTreeMap(this->treeMap[this->amountOfTreeMaps], otherEnd)) {
          this->insertChild(this->treeMap[this->amountOfTreeMaps], otherStart, otherEnd, atoi(otherDist));
        } else {
          this->amountOfTreeMaps++;
        }
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
        printf("Found matching child location and starting location :: path { %s -> %s } to { %s -> %s } \n",
                root->name, root->child[i]->name, start, end);
        root->child[i]->amountOfChildren++;
        printf("Root city %s has this amount of childrent cities: %d \n",
                root->name, root->child[i]->amountOfChildren);
        int t = root->child[i]->amountOfChildren;
        root->child[i]->child[t/*root->child[i]->amountOfChildren*/] = createNode(end, dist);
      } else {
        // printf("NO matching child location and starting location :: path { %s -> %s } to { %s -> %s } \n",
        //         root->name, root->child[i]->name, start, end);
        insertChild(root->child[i], start, end, dist);
      }
    }
  }
}

// searching for an end node; testing existance
bool UniformedSearch::searchTreeMap(struct node* testRoot, char start[40]) {
  if(testRoot == NULL) {
    return false;
  }

  for (int i = 0; i < 10; i++) {
    if (testRoot->child[i] == NULL) {
      continue;
    } else {
      if (strstr(testRoot->child[i]->name, start) != NULL) {
        return true;
      } else {
        searchTreeMap(testRoot->child[i], start);
      }
    }
  }
}
