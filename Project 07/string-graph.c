

/* This program will implement graph. This graph will be directed and weighted
   graph. This program will use linked list and adjacency list to create graph
*/

#include <stdio.h>
#include "string-graph.h"
#include <string.h>
#include <stdlib.h>

/* Prototype of find_vertex */
/* Helper function that will find the vertex that is matching with
   parameter name and return the matching vertex pointer*/
static Vertex * find_vertex(const String_graph *const graph, const char name[]);

/* This function gets graph pointer as a parameter and initialize it's graph
by creating a graph with empty vertices and edges. If the given graph is Null
it will do nothing */
void graph_init(String_graph *const graph) {
  if (graph != NULL) {
    graph -> vertex_count = 0;
    graph -> verticies = NULL;
  }
}

/*This function will add a vertice to the graph. It will get graph and 
vertex name as new_vertex. If any parameter is NULL it should not work and
return 0, otherwise it will create space in the verticies and save vertex
pointer, after succesfully saving, it will return 1 */
short add_vertex_to_graph(String_graph *const graph, const char new_vertex[]) {
  int valid = 1; /* Check validity of parameter and existence of same name*/
  int i = 0; /* will be used for forloop */
  Vertex * temp_vertex; /*used to save the pointer of vertex */

  /* Check whether the parameter is Null or not*/
  if (graph == NULL || new_vertex == NULL) {
    valid = 0;
  }

  /* If the parameter is not null, check where if the same name of vertex
     already exists. If exists, it will not save vertex */
  if (valid) {
    for (i = 0; i < graph -> vertex_count; i++) {
      if (strcmp(new_vertex, graph -> verticies[i] -> name) == 0)
        valid = 0;
    }
  }

  /* If the parameter is not null ,and same name does not exist, it will 
     enlarge the size of the vertex storage */
  if (valid) {
    /* If the vertex storage is null, where there is no verticies exist
       enlarge the size using malloc */
    if (graph -> verticies == NULL) {
      graph -> verticies = malloc(sizeof(Vertex * ));
    }
    /*If there is saved verticies, resize the vertex storage using 
      realloc*/
    else {
      graph -> verticies = realloc(graph -> verticies,
		           (graph -> vertex_count + 1) * sizeof(Vertex * ));
    }

    /*Initalize temporary vertex */
    temp_vertex = malloc(sizeof(Vertex));
    /*Initalize the name in the vertex and copy the name in*/
    temp_vertex -> name = malloc((strlen(new_vertex) + 1));
    strcpy(temp_vertex -> name, new_vertex);
    /*Initalize edges and edge count */
    temp_vertex -> edges = NULL;
    temp_vertex -> edge_count = 0;
    /*save vertex in the verticies storage and increase the count */
    graph -> verticies[graph -> vertex_count] = temp_vertex;
    graph -> vertex_count++;
  }

  /*return 1 or 0 based on the validity */
  return valid;
}

/* This function will return the number of verticies in the vertex storage */
short vertex_count(const String_graph *const graph) {
  int count = 0; /*use to save the number of verticies */

  /* Check whether it is null and if not get the number of count */
  if (graph != NULL)
    count = graph -> vertex_count;

  return count;
}

/* This function will check wheter the vertex with the mane exist 
   If the graph gets graph and name as a parameter and 
 if it is null or the graph does not exist it will return 0 */
short isa_vertex(const String_graph *const graph,const char name[]) {
  int valid = 1; /* state the validity */
  int exist = 0; /* state of the existence */
  int i = 0; /* use for the for loop */

  /* Check whether the parameter is Null or not*/
  if (graph == NULL || name == NULL) {
    valid = 0;
  }
  /*Check whether there is the same vertices name */
  if (valid) {
    for (i = 0; i < graph -> vertex_count; i++) {
      if (strcmp(name, graph -> verticies[i] -> name) == 0)
        exist = 1;
    }
  }

  return exist;
}

/* This function will get the list of the vertex in dynamically allocated array
if the given parameter is null or verticies does not exist it will return null
Otherwise, it will be return in dictionary order and return the list of it.
and for the convinency the last element will be always null. */
char ** get_vertex_list(const String_graph *const graph) {
  int valid = 1; /* will check validity of paramter */
  char ** vertex_names = NULL; /*array that will save names */
  int i = 0, j = 0; /* will be used in for loop */
  char * temp; /*Temporary string that saves vertex name */

  /* Check validity whether the paremeter is NULL */
  if (graph == NULL)
    valid = 0;

  /*Save Characters to the pointers to the array based on the
    dictionary order*/
  if (valid) {
    vertex_names = malloc((graph -> vertex_count) * sizeof(char * ));

    /*Copies the list of names from the vertex */
    for (i = 0; i < graph -> vertex_count; i++) {
      temp = malloc(strlen(graph -> verticies[i] -> name) + 1);
      strcpy(temp, graph -> verticies[i] -> name);
      vertex_names[i] = temp;
    }

    /* Using bubblesort to sort the array */
    for(i = 0; i < graph -> vertex_count; i++) {
      for(j = 0; j < graph -> vertex_count - 1 - i; j++) {
	if(strcmp(vertex_names[j], vertex_names[j + 1]) > 0) {
	  /* Swap if the first string ascci value is higher than second one */
	    temp = vertex_names[j];
	    vertex_names[j] = vertex_names[j + 1];
	    vertex_names[j + 1] = temp;
	}
      }
    }
    
    /* Reallocate the size list of vertex_name by +1 to add NULL at the 
       back */
    vertex_names = realloc(vertex_names, (graph -> vertex_count + 1) *
      sizeof(char * ));
    /*last emelent to be NULL */
    vertex_names[graph -> vertex_count + 1] = NULL;
  }

  return vertex_names;
}

/* Helper function that will find the vertex that is matching with
   parameter name and return the matching vertex pointer*/
static Vertex * find_vertex(const String_graph *const graph,const char name[]) {
  int i = 0;
  Vertex * temp_vertex = NULL;

  /*Dynamically allocate temporary vertex*/
  temp_vertex = malloc(sizeof(Vertex * ));

  /*using for loop find the matching vertex */
  for (i = 0; i < graph -> vertex_count; i++) {
    if (strcmp(graph -> verticies[i] -> name, name) == 0)
      temp_vertex = graph -> verticies[i];
  }

  return temp_vertex;
}

/* This function would create edge on the graph. However, there is some 
special cases: If the given source or dest vertex does not exist, it will
create the vertex. If there is already an edge it will just modify the 
weight. If the paramters are Null or the weight is negative it would 
do nothing and return 0 otherwise it will return 1. */
short create_graph_edge(String_graph *const graph, const char source[],
			const char dest[], int weight) {
  int valid = 1; /* Save the validity */
  Edge ** new_edges; /*  list of edges that will be used to store edges */
  Edge * new_edge; /* Temporary edge */
  Vertex * source_vertex; /* Vertex that will be used to save source vertex */
  Edge * find_edge = NULL; /*Temporary edge that will be used to do linkedlist*/
  int exist = 0; /* Integer variable that will be used the state the existence*/

  /*Check Some cases that will return 0 */
  if (weight < 0 || graph == NULL || source == NULL || dest == NULL)
    valid = 0;

  if (valid) {
    /*Case when there is no source vertex exists that is in paramter
      create one */
    if (isa_vertex(graph, source) == 0) {
      add_vertex_to_graph(graph, source);
    }

    /*Case when there is no destination vertex exists that is in paramter
      create one */
    if (isa_vertex(graph, dest) == 0) {
      add_vertex_to_graph(graph, dest);
    }
    /*Find matching  source vertex */
    source_vertex = find_vertex(graph, source);

    /* Bring the first edge from the edge list */
    if (source_vertex -> edges != NULL)
      find_edge = source_vertex -> edges[0];

    /* Using linked list Check whether the edge already exists 
       and if is already exists, change only the weight*/
    while (find_edge != NULL) {
      if (strcmp(dest, find_edge -> dest -> name) == 0) {
        exist = 1;
        find_edge -> weight = weight;
      }
      find_edge = find_edge -> next_edge;
    }

    /*If there is no edge exist  */
    if (exist == 0) {
      /*Create Edge node*/
      new_edge = malloc(sizeof(Edge));
      new_edge -> dest = find_vertex(graph, dest);
      new_edge -> next_edge = NULL;
      new_edge -> weight = weight;

      /* If there is no any edges in the vertex
       Add dynamically alocate edges */
      if (source_vertex == NULL) {
        source_vertex -> edges = malloc(sizeof(Edge * ));
      } else {
        /* If there is already edges in the vertex reallocate it */
        new_edges = realloc(source_vertex -> edges, 
			    (source_vertex -> edge_count + 1) * 
			    sizeof(Edge * ));
        /* let edges to point new_edges */
        source_vertex -> edges = new_edges;
      }

      /*Save edge to edges list */
      source_vertex -> edges[source_vertex -> edge_count] = new_edge;
      source_vertex -> edge_count++;

      /* Connect edges in the vertex in linked list */
      if (source_vertex -> edge_count >= 2) {
        source_vertex -> edges[source_vertex -> edge_count - 2] -> next_edge =
          new_edge;
        new_edge -> next_edge = NULL;
      }
    }
  }

  return valid;
}

/*This function will return the weight of the edge in its paramter graph that
goes from vertex source from destination. If the parameters are null or 
there is no matching source or dest, it would do nothing and should return -1
otherwise, it will return weight of the edge */
short get_graph_edge_weight(const String_graph *const graph,
			    const char source[],const char dest[]) {
  int valid = 1; /* represent the state of validity */
  int source_edge_count = 0; /* save the number of edge in one vertex */
  int answer_weight = -1; /* use to save the return value */
  int i = 0; /* use for for loop */

  /*Validity check */
  if (graph == NULL || source == NULL || dest == NULL)
    valid = 0;

  /* Check whether there is source or dest in the graph */
  if (valid) {
    if (isa_vertex(graph, source) == 0 || isa_vertex(graph, dest) == 0)
      valid = 0;
  }

  /*Check whether there is edge between it */
  if (valid) {
    source_edge_count = find_vertex(graph, source) -> edge_count;
    for (i = 0; i < source_edge_count; i++) {
      /* If there is matching edge saves the weight in to the answer_weight */
      if (strcmp(find_vertex(graph, source) -> 
		 edges[i] -> dest -> name, dest) == 0) {
        answer_weight = find_vertex(graph, source) -> edges[i] -> weight;
      }
    }
  }

  return answer_weight;
}

/* This function should return the number of neighbors in the vertex 
   if the paramter is null or if there is no vertex, should return -1 */
short neighbor_count(const String_graph * const graph,const char vertex[]) {
  int valid = 1; /* saves validity state */
  int count = 0; /* use to count the neighbor*/
  Vertex * temp_vertex; /* temporary vertex that will points matching name of 
			    vertex */

  /*check whether the parameter is NULL */
  if (graph == NULL || vertex == NULL)
    valid = 0;

  /*check whether there is no vertex with name "vertex" in graph*/
  if (valid) {
    if (isa_vertex(graph, vertex) == 0)
      valid = 0;
  }

  /*Bring matching vertex  */
  if (valid) {
    temp_vertex = find_vertex(graph, vertex);
  }

  /*count number of edges in the vertex */
  if (valid) {
    count = temp_vertex -> edge_count;
  }

  /* Return count */
  if (valid == 0)
    count = -1;
  return count;
}
