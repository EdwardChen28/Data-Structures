/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <map>
/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
	
	std::map<Vertex,Vertex> m;
	vector<Vertex> V = graph.getVertices();	
	//assign every vertex
	for(int i =0; i < V.size();i++){
		graph.setVertexLabel(V[i], "unvisited");
	
	}
	
		queue<Vertex> Q;
		graph.setVertexLabel(start,"visited");
		Q.push(start);
		
		while(!Q.empty() && graph.getVertexLabel(end) != "visited"){
			Vertex pre = Q.front();
			Q.pop();
			vector<Vertex> adj = graph.getAdjacent(pre);
			for(int j = 0; j < adj.size(); j++){
				if(graph.getVertexLabel(adj[j]) == "unvisited"){
					m[adj[j]] = pre;
					Q.push(adj[j]);
					graph.setVertexLabel(adj[j],"visited");		
				}
			 			 		
			}
		}
		int count=0;
		while(end != start){
			count++;
			graph.setEdgeLabel(end, m[end], "MINPATH");
			end = m[end];
		
	} 
	
    return count;
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph & graph)
{
	//get all the vertices and edges
	//loop all of them and label unvisited
	//get a start vertex and find its adjacent vertics
	//keep track of the min weight
	
	vector<Vertex> V = graph.getVertices();

	for(int i =0; i < V.size();i++){
		graph.setVertexLabel(V[i], "unvisited");
		vector<Vertex> adj = graph.getAdjacent(V[i]);
			for( int j =0; j < adj.size();j++)
				graph.setEdgeLabel(V[i],adj[j],"unvisited");
		
	}
	Vertex sv,ev;
	int min = 99999999;
	for(int i = 0; i < V.size();i++){
		queue<Vertex> Q;
		graph.setVertexLabel(V[i],"visited");
		Q.push(V[i]);
		while(!Q.empty()){
			Q.pop();
			vector<Vertex> adj = graph.getAdjacent(V[i]);
			for(int j = 0; j < adj.size(); j++){
				if(graph.getVertexLabel(adj[j]) == "unvisited"){
					graph.setVertexLabel(adj[j], "visited");
					if( graph.getEdgeWeight(V[i],adj[j]) < min){
						min = graph.getEdgeWeight(V[i],adj[j]);
						sv = V[i];
						ev = adj[j];
					}	
					graph.setEdgeLabel(V[i],adj[j], "visited");
					Q.push(adj[j]);
				}
			 	else if(graph.getEdgeLabel(V[i], adj[j]) =="unvisited"){
			 		if( graph.getEdgeWeight(V[i],adj[j]) < min){
						min = graph.getEdgeWeight(V[i],adj[j]);
						sv = V[i];
						ev = adj[j];
					}
					graph.setEdgeLabel(V[i], adj[j],"visited");
				}
			 		
			}
		}
	} 
	graph.setEdgeLabel(sv,ev,"MIN");
	
    return min;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{
	DisjointSets dj;
	vector<Vertex> v = graph.getVertices();
	dj.addelements(v.size());
	
	queue<Edge> q;
	vector<Edge> e = graph.getEdges();
	sort(e.begin(),e.end());
	for(int i = 0; i < e.size();i++)
		q.push(e[i]);
	while(!q.empty()){
		if(dj.find(q.front().source) != dj.find(q.front().dest)){
			graph.setEdgeLabel(q.front().source, q.front().dest, "MST");
			dj.setunion(q.front().source, q.front().dest);
			}
		q.pop();
	}
	


}
