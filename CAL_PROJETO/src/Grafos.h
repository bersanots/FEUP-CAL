/*
 * Grafos.h
 *
 */

#ifndef GRAFOS_H_
#define GRAFOS_H_


#include <vector>
#include <queue>
#include <limits>
#include "MutablePriorityQueue.h"
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	bool processing;       // auxiliary field used by isDAG
	int indegree;          // auxiliary field used by topsort

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	T getInfo() const;
	friend class Graph<T>;
};

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v) const;
public:
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;
	Vertex<T> *initSingleSource(const T &origin);
	bool relax(Vertex<T> *v, Vertex<T> *w, double weight);
	void dijkstraShortestPath(const T &origin);
	vector<T> getPath(const T &origin, const T &dest) const;
	//bool biDirSearch(int s, int t)

};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
T Vertex<T>::getInfo() const{
	return info;
}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}



/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	return v1->removeEdgeTo(v2);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	for (auto it = adj.begin(); it != adj.end(); it++)
		if (it->dest  == d) {
			adj.erase(it);
			return true;
		}
	return false;
}




/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
	for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
		if ((*it)->info  == in) {
			auto v = *it;
			vertexSet.erase(it);
			for (auto u : vertexSet)
				u->removeEdgeTo(v);
			delete v;
			return true;
		}
	return false;
}




/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
	vector<T> res;
	for (auto v : vertexSet)
		v->visited = false;
	for (auto v : vertexSet)
		if (! v->visited)
			dfsVisit(v, res);
	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	v->visited = true;
	res.push_back(v->info);
	for (auto & e : v->adj) {
		auto w = e.dest;
		if ( ! w->visited)
			dfsVisit(w, res);
	}
}



/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
	vector<T> res;
	auto s = findVertex(source);
	if (s == NULL)
		return res;
	queue<Vertex<T> *> q;
	for (auto v : vertexSet)
		v->visited = false;
	q.push(s);
	s->visited = true;
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		res.push_back(v->info);
		for (auto & e : v->adj) {
			auto w = e.dest;
			if ( ! w->visited ) {
				q.push(w);
				w->visited = true;
			}
		}
	}
	return res;
}



/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {
	vector<T> res;

	for (auto v : vertexSet)
		v->indegree = 0;
	for (auto v : vertexSet)
		for (auto & e : v->adj)
			e.dest->indegree++;

	queue<Vertex<T>*> q;
	for (auto v : vertexSet)
		if (v->indegree == 0)
			q.push(v);

	while( !q.empty() ) {
		Vertex<T>* v = q.front();
		q.pop();
		res.push_back(v->info);
		for(auto & e : v->adj) {
			auto w = e.dest;
			w->indegree--;
			if(w->indegree == 0)
				q.push(w);
		}
	}

	if ( res.size() != vertexSet.size() ) {
		cout << "Ordenacao Impossivel!" << endl;
		res.clear();
		return res;
	}

	return res;
}


/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex and the number of new children.
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
	auto s = findVertex(source);
	if (s == NULL)
		return 0;
	queue<Vertex<T> *> q;
	int maxChildren = 0;
	inf = s->info;
	for (auto v : vertexSet)
		v->visited = false;
	q.push(s);
	s->visited = true;
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		int nChildren=0;
		for (auto & e : v->adj) {
			auto w = e.dest;
			if ( ! w->visited ) {
				w->visited = true;
				q.push(w);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren = nChildren;
			inf = v->info;
		}
	}
	return maxChildren;
}



/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
	for (auto v : vertexSet) {
		v->visited = false;
		v->processing = false;
	}
	for (auto v : vertexSet)
		if (! v->visited)
			if ( ! dfsIsDAG(v) )
				return false;
	return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
	v->visited = true;
	v->processing = true;
	for (auto & e : v->adj) {
		auto w = e.dest;
		if (w->processing)
			return false;
		if (! w->visited)
			if (! dfsIsDAG(w))
				return false;
	}
	v->processing = false;
	return true;

}


/**
 * Initializes single-source shortest path data (path, dist).
 * Receives the content of the source vertex and returns a pointer to the source vertex.
 * Used by all single-source shortest path algorithms.
 */
template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) {
	for (auto v : vertexSet) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findVertex(origin);
	s->dist = 0;
	return s;
}
/**
 * Analyzes an edge in single-source shortest path algorithm.
 * Returns true if the target vertex was relaxed (dist, path).
 * Used by all single-source shortest path algorithms.
 */
template<class T>
bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
	if (v->dist + weight < w->dist) {
		w->dist = v->dist + weight;
		w->path = v;
		return true;
	}
	else
		return false;
}


/**
 * Dijkstra algorithm.
 */
template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex<T>> q;
	q.insert(s);
	while ( ! q.empty() ) {
		auto v = q.extractMin();
		for (auto e : v->adj) {
			auto oldDist = e.dest->dist;
			if (relax(v, e.dest, e.weight)) {
				if (oldDist == INF)
					q.insert(e.dest);
				else
					q.decreaseKey(e.dest);
			}
		}
	}
}


template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const {
	vector<T> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist == INF) // missing or disconnected
		return res;
	for ( ; v != nullptr; v = v->path)
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	return res;
}

// To do the bidirectional Dijkstra algorith i have the check if the vertex are intersecting
/*
int Graph<T>::isIntersecting(bool *s_visited, bool *t_visited){
	int intersectNode = -1;
	for(int i=0;i<vertexSet.size();i++)
	{
		// if a vertex is visited by both front
		// and back BFS search return that node
		// else return -1
		if(s_visited[i] && t_visited[i])
			return i;
	}
	return -1;
}

// Method for bidirectional searching
bool Graph::biDirSearch(int s, int t)
{
	// boolean array for BFS started from
	// source and target(front and backward BFS)
	// for keeping track on visited nodes
	bool s_visited[vertexSet.size()], t_visited[vertexSet.size()];

	// Keep track on parents of nodes
	// for front and backward search
	int s_parent[vertexSet.size()], t_parent[vertexSet.size()];

	// queue for front and backward search
	list<int> s_queue, t_queue;

	int intersectNode = -1;

	// necessary initialization
	for(int i=0; i<vertexSet.size(); i++)
	{
		s_visited[i] = false;
		t_visited[i] = false;
	}

	s_queue.push_back(s);
	s_visited[s] = true;

	// parent of source is set to -1
	s_parent[s]=-1;

	t_queue.push_back(t);
	t_visited[t] = true;

	// parent of target is set to -1
	t_parent[t] = -1;

	while (!s_queue.empty() && !t_queue.empty())
	{
		// Do BFS from source and target vertices
		//bfs(&s_queue);
		bfs(&t_queue);

		// check for intersecting vertex
		intersectNode = isIntersecting(s_visited, t_visited);

		// If intersecting vertex is found
		// that means there exist a path
		if(intersectNode != -1)
		{
			return true;
		}
	}
	return false;
}*/



#endif /* GRAFOS_H_ */
