#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int size=0;

void printMatrix(int coloumn, int (*ptr_arr)[coloumn]){
  int i,j;
  for (i = 0; i < coloumn; ++i)
  {
    for ( j = 0; j < coloumn; ++j)
      {
        if(ptr_arr[i][j]>=999){
        printf("%7s","INF");
        }else{
        printf("%7d",ptr_arr[i][j]);
        }
        
      }
      printf("\n");
  }
  
}

void printMST(int parent[], int V, int (*graph)[V]){

   //printf("Edge   Weight\n");
   int i;
   for ( i = 1; i < V; i++){

      if(graph[i][parent[i]]!=999){
      printf("edge %d,%d Weight=%d \n", parent[i]+1, i+1, graph[i][parent[i]]); // changed incremented parent and i 
   }
 }

}


int findMinimum(int size, int key[],int status[]){
  int min=999, minIndex,i;
  for ( i = 0; i < size; ++i)
  {
      if(status[i]==0 && key[i]< min){
          min=key[i];
          minIndex=i;
      }
  }
  return minIndex;
}

void prim(int coloumn,int (*graph)[coloumn]){
    int parent[coloumn];
    int key[coloumn];
    int status[coloumn];
    int i,v,z;
    for (i = 0; i < coloumn; ++i) // initializing key with infi and status 0 (not included)
    {
        key[i]=999;
        status[i]=0;
        parent[i]=-1;   
    }
    key[0]=0;
    parent[0]=-1;

    

    for ( i = 0; i < coloumn-1; ++i)
    {
        int u = findMinimum(coloumn,key,status);
        status[u]=1;

        for (v = 0; v < coloumn; ++v)
        {
            if(graph[u][v] && status[v]==0 && graph[u][v]<key[v]){
                parent[v]=u;
                key[v]=graph[u][v];
            }
        
        }
        // for ( z = 0; z < coloumn; ++z)
        // {
        //   printf("(%d-%d)\t",key[z],status[z]);
        // }
        // printf("\n");
    }
   printMST(parent, coloumn, graph);
}


int main(int argc, char *args[]){
	
	FILE * file_ptr = fopen(args[1], "r");
  	char * line = NULL;  	const char *s = ",";
  	size_t len = 0;
  	ssize_t read;
  	
  	int i=0,j=0,k=0;
	if (file_ptr == NULL)
    {
    	printf("\nError opening\n");
    	
    	exit(EXIT_FAILURE);
    }else{
	    while ((read=getline(&line, &len, file_ptr)) != -1){
	    	//printf("Line %s\n",line);
	     	size++;	
	    }
	}
	fclose(file_ptr); // closing the file

     int graph[size][size];

     for (i = 0; i < size; ++i) // intializing grpah with 0
      {
      	for (j = 0; j < size; ++j)
      	{
      		graph[i][j]=0;
      	}
      } 
    size_t len_two=0;
    ssize_t read_two;
    char *token=NULL; 
     i=0;
     j=0;
     FILE * file_ptr_two = fopen(args[1], "r");
     while((read_two=getline(&token, &len_two, file_ptr_two))!=-1){
     	char *value;
     	for(value=strtok(token,",");value;value=strtok(NULL,",")){
     		
     		graph[i][j]=atoi(value);
     		//printf("%d %d - %d\n",i,j,atoi(value));
     		j++;

     	}	
     	j=0;
     	i++;
     }

	//printMatrix(size,graph);
  prim(size,graph);
	fclose(file_ptr_two);
}