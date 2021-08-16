#                    DataStructure Project 

## Title: Encryption Algorithm Using Graph Theory
### Aim :

To generate an Algorithm for data encryption and decryption using Graph Theory.
To implement knowledge of how new symmetric  encryption  algorithm  uses  the  concepts  of cycle  graph,  complete  graph  and Kruskal’s minimum spanning tree to generate a complex cipher text using a shared key 




 
### Objectives and learning Outcomes :
       
At the end of project :
We will get acquainted with different concepts of  Graphs such as complete Graph, Minimum Spanning Tree, Depth first Search, and more Graphs concepts.
We will be familiar with programming graphs in C++,               eg: Adding Vertices, Adding Edges, Adding Weights.
Representation of Graphs using Adjacency Matrix and Adjacency list.



### Proposed Algorithm :

The  first  step  in  this  algorithm  is  to  represent  data  as  vertices  in  a  graph,  each  character represented by a vertex  while  all  adjacent  characters  in the  data  will  be  represented  as adjacent  vertices  in  the  graph,  we  keep adding  vertices  until  we  form  a  cycle  graph.
Every edge in the graph has its own weight representing the distance of these two characters in the encoding  table.

Graph will  join with edges to make the graph a complete  graph,  while  every  new  added edge  has  a weight  starting  from  the  27 and adding 1 to it . Adjacency Matrix  is  constructed  for  the  complete  graph.  After  that  Minimum  Spanning  Tree  (MST)  is computed  from  the  complete  graph  and  represented  as an adjacency matrix  that  keeps  data characters  ordered  in  its  diagonal. The resultant matrix multiplied to the key matrix. The final matrix is the encryption data to be sent to the recipient.

     	   
 
### Encryption Algorithm:
 
1. Add a special character to indicate the starting character (Let A).
2. Add vertex for each character in the plain text to the graph.
3. Link  vertices  together  by  adding  an  edge  between  each  sequential  character  in  the plain text until we form a cycle graph.
4. Weight  each  edge  using  the  encoding  table.  Each  edge's  weight
5. represents  the distance between the connected two vertices from the encoding table.
6. Adding  more  edges  to  form  a  complete  graph  M1,  each  new  added  edge  has  a sequential weight starting from the maximum weight in the encoding table.
7. Then find the Minimum Spanning Tree M2.
8. Then store the vertices order in the M2 matrix in the diagonal places.
9. Then we multiply matrices M1 by M2 to get M3.
10. After that we multiply M3 by a predefined Shared-Key K to form C.
11. Then the cipher text contains Matrix C and Matrix M1 line-by-line in a linear format.
 
### Decryption Algorithm:
 
1. The receiver computes M3 by using the inverse form of the Shared-Key K-1.
2. Then compute M2 by using the inverse form of M1.
3. Then compute the original text by decoding M1 using the encoding table.

