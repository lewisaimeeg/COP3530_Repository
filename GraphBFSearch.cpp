#include <iostream>
#include <queue>

using namespace std;

class My_Graph
{
	const static int MAXNUMVERTICES = 100;
	int theGraph[MAXNUMVERTICES][MAXNUMVERTICES];
	bool undirected;
public:

	My_Graph()
	{
		undirected = true;
	}

	void insertEdge(int to, int from, int weight)
	{
		theGraph[to][from] = weight;
		theGraph[from][to] = weight;
	}
	void breadthFirstSearch(int start) {

		int s = 100;
		// Create a "visited" array to see if we visited a vertex
		bool visited[s] = { false };

		// queue of vertices visited
		queue<int> verticesVisited;

		// first, add the start node and mark it visited
		verticesVisited.push(start);
		visited[start] = true;

		while (verticesVisited.empty() == false) {
			int vertex = verticesVisited.front();
			verticesVisited.pop();

			cout << vertex << " ";

			for (int i = 0; i < 100; i++) {

				int neighbor = i;
				int edge = theGraph[vertex][i];

				// not a neighbor
				if (edge == 0) {
					continue;
				}
				// add to queue, mark as visited
				if (visited[neighbor] == false) {
					verticesVisited.push(neighbor);
					visited[neighbor] = true;
				}
			}
		}

	}
};

int main()
{
	My_Graph *theGraph = new My_Graph();
	int numEdges, inVert, outVert;
	int lowestVert = 999;
	std::cin >> numEdges;
	for (int i = 0; i<numEdges; i++)
	{
		std::cin >> inVert;
		std::cin >> outVert;
		theGraph->insertEdge(inVert, outVert, 1);
		if (inVert < lowestVert)
			lowestVert = inVert;
		if (outVert < lowestVert)
			lowestVert = outVert;
	}
	theGraph->breadthFirstSearch(lowestVert);
}