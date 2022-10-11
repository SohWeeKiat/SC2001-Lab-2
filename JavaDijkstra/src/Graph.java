import java.util.LinkedList;
import java.util.Random;

public class Graph {

    int V;
    int E;
    LinkedList<Edge>[] adjList;
    int adjMatrix[][];

    public Graph(int V) {
        this.V = V;
        adjList = new LinkedList[V];
        for (int i = 0; i < V; i++) {
            adjList[i] = new LinkedList<>();
        }
        adjMatrix = new int[V][V];
    }

    /**
     * Constructor to generate random graph
     * 
     * @param maxVertices maximum number of vertices in the graph
     * @param maxWeight   maximum weight of an edge
     */

    public Graph(int maxVertices, int maxWeight, int edges, int sparseFactor){
        Random rand = new Random();
        this.V = maxVertices;
        adjList = new LinkedList[V];
        for (int i = 0; i < V; i++) {
            adjList[i] = new LinkedList<>();
        }
        adjMatrix = new int[V][V];


        for (int i = 0; i < edges; i++) {
            int src = rand.nextInt(V);
            int dest = rand.nextInt(V);
            if (src != dest && !existEdge(src, dest)) {
                int weight = rand.nextInt(maxWeight) + 1;
                addEdge(src, dest, weight);
            } else
                i--;
        }
    }

    public Graph(int maxVertices, int maxWeight, int sparseFactor) {

        if (sparseFactor == 0) {
            Random rand = new Random();
            this.V = maxVertices;
            adjList = new LinkedList[V];
            for (int i = 0; i < V; i++) {
                adjList[i] = new LinkedList<>();
            }
            adjMatrix = new int[V][V];

            /*
             * For a randomly chosen number of vertices V,
             * the maximum number of possible edges is
             * V*(V – 1)(with no multiple edges and self-loops).
             */

            int maxEdges = V * (V - 1);
            int randEdges = maxEdges;
            for (int i = 0; i < randEdges; i++) {
                int src = rand.nextInt(V);
                int dest = rand.nextInt(V);
                if (src != dest && !existEdge(src, dest)) {
                    int weight = rand.nextInt(maxWeight) + 1;
                    addEdge(src, dest, weight);
                } else
                    i--;
            }
        }
        if (sparseFactor == 1) {
            Random rand = new Random();
            this.V = maxVertices;
            adjList = new LinkedList[V];
            for (int i = 0; i < V; i++) {
                adjList[i] = new LinkedList<>();
            }
            adjMatrix = new int[V][V];

            /*
             * For a randomly chosen number of vertices V,
             * the maximum number of possible edges is
             * V*(V – 1)(with no multiple edges and self-loops).
             */

            int maxEdges = V * (V - 1);
            int minEdges = V - 1;
            int randEdges = rand.nextInt(maxEdges-minEdges) + minEdges;
            for (int i = 0; i < randEdges; i++) {
                int src = rand.nextInt(V);
                int dest = rand.nextInt(V);
                if (src != dest && !existEdge(src, dest)) {
                    int weight = rand.nextInt(maxWeight) + 1;
                    addEdge(src, dest, weight);
                } else
                    i--;
            }
        }
        else{   
            // generate sparse graph
            Random rand = new Random();
            this.V = rand.nextInt(maxVertices) + 2;
            adjList = new LinkedList[V];
            for (int i = 0; i < V; i++) {
                adjList[i] = new LinkedList<>();
            }
            adjMatrix = new int[V][V];

            /*
             * For a randomly chosen number of vertices V,
             * the maximum number of possible edges is
             * V*(V – 1)(with no multiple edges and self-loops).
             */

            int edgeCount = V-1; //minimum E for a connected graph
            for (int i = 0; i < edgeCount; i++) {
                int src = rand.nextInt(V);
                int dest = rand.nextInt(V);
                if (src != dest && !existEdge(src, dest)) {
                    int weight = rand.nextInt(maxWeight) + 1;
                    addEdge(src, dest, weight);
                } else
                    i--;
            }

        }
    }

    public void addEdge(int src, int dest, int weight) {
        Edge edge = new Edge(src, dest, weight);
        adjList[src].addFirst(edge);
        adjMatrix[src][dest] = weight;
        E++;
    }

    public void printGraph() {
        for (int i = 0; i < V; i++) {
            LinkedList<Edge> list = adjList[i];
            for (int j = 0; j < list.size(); j++) {
                System.out.println("vertex " + i + " is connected to " + list.get(j).dest + " with weight "
                        + list.get(j).weight);
            }
        }
    }

    public void printGraphMatrix(Graph g)
    {
        int i,j;
        System.out.println("Print graph matrix \n");

        for(i=0;i<V;i++){
            System.out.print("Vertex " + i + ":\t");
            for(j=0;j<V;j++)
                System.out.print(g.adjMatrix[i][j] + "\t");
            System.out.print("\n");
        }
        System.out.print("\n");

    }

    public void printGraphList(Graph g){
        int i;
        LinkedList<Edge> temp;
        System.out.println("Print graph list");
    
        for(i=0;i<V;i++)
        {
            System.out.print(i + "\t");
            temp = g.adjList[i];

            for (int j = 0; j < temp.size(); j++) {
                System.out.print(temp.get(j).dest +" w " +temp.get(j).weight + "-> ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public boolean existEdge(int src, int dest) {
        // check if there is alreeady an edge between src and dest
        if (adjMatrix[src][dest] != 0) {
            return true;
        }
        return false;
    }

}
