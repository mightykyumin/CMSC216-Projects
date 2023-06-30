

/* This header file will contain the data structure of the graph, that will
   be used to save the graph components. It contains vertex structure and edge
   structure and finally the String_graph structure. The data structrue is 
   only made of dynamically allocated storage */

/*structure of vertex that contains the name of the vertex, and lists of edges
  pointer that the vertex is connected to(directed) and the number of 
  the edge that is connected to */
typedef struct vertex {
   char * name;
   struct edge ** edges;
   int edge_count;
}
Vertex;

/* Edge structure that will contain weight, destination and next edge*/
typedef struct edge {
   /*This destination will points conatain pointer of the vertex
     that the edge will point*/
   Vertex * dest;
   int weight; /*saves edge's weight*/
   /*Linked list to the edge that saves the next edge which is saved in the 
     vertex structure "edges". */
   struct edge * next_edge;
}
Edge;

/* A graph structrue that contains the number of vertex and list of all
   verticies's pointer */
typedef struct String_graph {
   int vertex_count;
   Vertex ** verticies;
}
String_graph;
