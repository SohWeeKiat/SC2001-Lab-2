import java.io.IOException;

public class Test {

    /**
     * @param args
     * @throws Exception
     */
    public static void main(String[] args) throws Exception {
        // *unncomment the following line to run the respective test program

        // testPrintGraph();
        //testDijkstraArray();
        //testDijkstraPQ();
        //testGenerateRandomGraph(5,10);
        //fixedEdgesTest(100,1000,1,1);
        //empiricalTest(150, 1000, 10, 1000);
        randomEdgesFixedVerticesTest(100,1000,2500,1000);
        randomVerticesFixedEdgesTest(50, 250, 2000, 1000, 1000, 1000);
    }

    /**
     * Test the printGraph method
     */
    private static void testPrintGraph() {
        Graph g = new Graph(5);
        g.addEdge(0, 1, 4);
        g.addEdge(0, 2, 2);
        g.addEdge(0, 3, 6);
        g.addEdge(0, 4, 8);
        g.addEdge(1, 3, 4);
        g.addEdge(1, 4, 3);
        g.addEdge(2, 3, 1);
        g.addEdge(3, 1, 1);
        g.addEdge(3, 4, 3);
        g.printGraph();
        System.out.println();
    }

    /**
     * Test the Dijkstra algorithm using an adjMatrix and Array
     */
    private static void testDijkstraArray() {
        System.out.println("teesDijkstraArray: ");
        Graph g = new Graph(5);
        g.addEdge(0, 1, 4);
        g.addEdge(0, 2, 2);
        g.addEdge(0, 3, 6);
        g.addEdge(0, 4, 8);
        g.addEdge(1, 3, 4);
        g.addEdge(1, 4, 3);
        g.addEdge(2, 3, 1);
        g.addEdge(3, 1, 1);
        g.addEdge(3, 4, 3);
        g.printGraphMatrix(g);
        g.printGraphList(g);
        DijkstraAlgo dijkstraTest = new DijkstraAlgo(5);
        dijkstraTest.dijkstraArrayStart(5, 0, g.adjMatrix);
    }

    /**
     * Test the Dijkstra algorithm using an adjList and a PriorityQueue
     */
    private static void testDijkstraPQ() {
        System.out.println("testDijkstraPQ: ");
        Graph g = new Graph(5);
        g.addEdge(0, 1, 4);
        g.addEdge(0, 2, 2);
        g.addEdge(0, 3, 6);
        g.addEdge(0, 4, 8);
        g.addEdge(1, 3, 4);
        g.addEdge(1, 4, 3);
        g.addEdge(2, 3, 1);
        g.addEdge(3, 1, 1);
        g.addEdge(3, 4, 3);
        /*g.addEdge(0, 1, 4);
        g.addEdge(0, 2, 2);
        g.addEdge(0, 3, 6);
        g.addEdge(0, 4, 8);
        g.addEdge(1, 3, 4);
        g.addEdge(1, 4, 3);
        g.addEdge(2, 3, 1);
        g.addEdge(3, 1, 1);
        g.addEdge(3, 4, 3);
        */
        g.printGraphList(g);
        DijkstraAlgo dijkstraTest = new DijkstraAlgo(5);
        dijkstraTest.dijkstraPQStart(5, 0, g.adjList);
    }

    /**
     * Test the generateRandomGraph method
     * 
     * @param maxVertices maximum number of vertices
     * @param maxEdges    maximum number of edges
     */
    private static void testGenerateRandomGraph(int maxVertices, int maxWeight) {
        Graph g = new Graph(maxVertices, maxWeight, 0);
        System.out.println("Random Graph generated, V = " + g.V + ", E = " + g.E);
        g.printGraphList(g);
        g.printGraphMatrix(g);
    }

    /**
     * Test the Dijkstra algorithm on a random graph in two ways: adjMatrix+Array
     * and adjList+PQ. During the test, runtime (in nanoseconds) is recorded and
     * stored.
     * This test shall generate 4 .csv files, containing the results of the
     * empirical test: verticeArr.csv, edgeArr.csv,
     * timeArr(test1).csv, timeArr(test2).csv
     * 
     * @param maxVertices  maximum number of vertices for random graph generation
     * @param maxWeight    maximum weight for random graph generation
     * @param graphCount   number of graphs to be generated
     * @param averageTimes number of times to run the algorithm for each graph
     * @throws IOException
     */

    private static void fixedEdgesTest(int maxVertices, int maxWeight, int graphCount, int averageTimes) throws Exception{
        long[] verticeArr = new long[maxVertices*(maxVertices-1)], edgeArr = new long[maxVertices*(maxVertices-1)], timeArr1 = new long[maxVertices*(maxVertices-1)],
                timeArr2 = new long[maxVertices*(maxVertices-1)];
        
        for(int i = maxVertices-1; i <= maxVertices*(maxVertices-1); i++){
            System.out.println("Generating edges: " + i);
            Graph g = new Graph(maxVertices, maxWeight, i, 0);

            verticeArr[i-(maxVertices-1)] = g.V;
            edgeArr[i-(maxVertices-1)] = g.E;
            long timeTotal1 = 0;
            long timeTotal2 = 0;
            for (int j = 0; j < averageTimes; j++) {
                DijkstraAlgo dijkstraTest = new DijkstraAlgo(g.V);
                long startTime = System.nanoTime();
                dijkstraTest.dijkstraArrayStart(g.V, 0, g.adjMatrix);
                long endTime = System.nanoTime();
                timeTotal1 += endTime - startTime;

                startTime = System.nanoTime();
                dijkstraTest.dijkstraPQStart(g.V, 0, g.adjList);
                endTime = System.nanoTime();
                timeTotal2 += endTime - startTime;
            }
            timeArr1[i-(maxVertices-1)] = timeTotal1 / averageTimes;
            timeArr2[i-(maxVertices-1)] = timeTotal2 / averageTimes;
        }
        MakeCSV combinedCSV = new MakeCSV("fixedEdgesTest.csv");
        combinedCSV.WriteLine("VerticeArr,EdgeArr,TimeArr1,TimeArr2");
        for(int i = 0;i < verticeArr.length;i++){
            combinedCSV.WriteLine(verticeArr[i] + "," + edgeArr[i] + "," + timeArr1[i] + "," + timeArr2[i]);
        }
    }

    private static void empiricalTest(int maxVertices, int maxWeight, int graphCount, int averageTimes)
            throws IOException {
        
        // for connected graph w varying vertices
        long[] verticeArr = new long[maxVertices], edgeArr = new long[maxVertices], timeArr1 = new long[maxVertices],
                timeArr2 = new long[maxVertices];
                        
        for(int i = 1; i <= maxVertices; i++){
            System.out.println("Generating max vertex: " + i);
            Graph g = new Graph(i, maxWeight, 0);
            verticeArr[i-1] = g.V;
            edgeArr[i-1] = g.E;
            long timeTotal1 = 0;
            long timeTotal2 = 0;
            for (int j = 0; j < averageTimes; j++) {
                DijkstraAlgo dijkstraTest = new DijkstraAlgo(g.V);
                long startTime = System.nanoTime();
                dijkstraTest.dijkstraArrayStart(g.V, 0, g.adjMatrix);
                long endTime = System.nanoTime();
                timeTotal1 += endTime - startTime;

                startTime = System.nanoTime();
                dijkstraTest.dijkstraPQStart(g.V, 0, g.adjList);
                endTime = System.nanoTime();
                timeTotal2 += endTime - startTime;
            }
            timeArr1[i-1] = timeTotal1 / averageTimes;
            timeArr2[i-1] = timeTotal2 / averageTimes;
        }
        MakeCSV combinedCSV = new MakeCSV("MergedCSV.csv");
        combinedCSV.WriteLine("VerticeArr,EdgeArr,TimeArr1,TimeArr2");
        for(int i = 0;i < maxVertices;i++){
            combinedCSV.WriteLine(verticeArr[i] + "," + edgeArr[i] + "," + timeArr1[i] + "," + timeArr2[i]);
        }
    }
    private static void randomVerticesFixedEdgesTest(int startVertex, int endVertex, int maxEdges, int maxWeight, int graphCount, int averageTimes) throws Exception{
        int n = endVertex - startVertex + 1;
        long[] verticeArr = new long[n], edgeArr = new long[n], timeArr1 = new long[n],
                timeArr2 = new long[n];
        int counter = 0;
        for(int i = startVertex; i <= endVertex; i++, counter++){
            System.out.println("Generating graph with vertex " + (i) + "...");
            Graph g = new Graph(i, maxWeight, maxEdges, 1);

            verticeArr[counter] = g.V;
            edgeArr[counter] = g.E;
            long timeTotal1 = 0;
            long timeTotal2 = 0;
            for(int j = 0; j < averageTimes; j++) {
                DijkstraAlgo dijkstraTest = new DijkstraAlgo(g.V);
                long startTime = System.nanoTime();
                dijkstraTest.dijkstraArrayStart(g.V, 0, g.adjMatrix);
                long endTime = System.nanoTime();
                timeTotal1 += endTime - startTime;

                startTime = System.nanoTime();
                dijkstraTest.dijkstraPQStart(g.V, 0, g.adjList);
                endTime = System.nanoTime();
                timeTotal2 += endTime - startTime;
            }
            timeArr1[counter] = timeTotal1 / averageTimes;
            timeArr2[counter] = timeTotal2 / averageTimes;

        }
        MakeCSV combinedCSV = new MakeCSV("randomVerticesFixedEdgesTest.csv");
        combinedCSV.WriteLine("VerticeArr,EdgeArr,TimeAdjMatrix,TimeAdjList");
        for(int i = 0;i < verticeArr.length;i++){
            combinedCSV.WriteLine(verticeArr[i] + "," + edgeArr[i] + "," + timeArr1[i] + "," + timeArr2[i]);
        }
    }
    private static void randomEdgesFixedVerticesTest(int maxVertices, int maxWeight, int graphCount, int averageTimes)
            throws IOException {
        long[] verticeArr = new long[graphCount], edgeArr = new long[graphCount], timeArr1 = new long[graphCount], timeArr2 = new long[graphCount];
        for (int i = 0; i < graphCount; i++) {
            System.out.println("Generating graph " + (i + 1) + "...");
            Graph g = new Graph(maxVertices, maxWeight, 1);
            verticeArr[i] = g.V;
            edgeArr[i] = g.E;
            long timeTotal1 = 0;
            long timeTotal2 = 0;
            for (int j = 0; j < averageTimes; j++) {
                DijkstraAlgo dijkstraTest = new DijkstraAlgo(g.V);
                long startTime = System.nanoTime();
                dijkstraTest.dijkstraArrayStart(g.V, 0, g.adjMatrix);
                long endTime = System.nanoTime();
                timeTotal1 += endTime - startTime;

                startTime = System.nanoTime();
                dijkstraTest.dijkstraPQStart(g.V, 0, g.adjList);
                endTime = System.nanoTime();
                timeTotal2 += endTime - startTime;
            }
            timeArr1[i] = timeTotal1 / averageTimes;
            timeArr2[i] = timeTotal2 / averageTimes;

        }
        MakeCSV combinedCSV = new MakeCSV("randomEdgesFixedVertices.csv");
        combinedCSV.WriteLine("VerticeArr,EdgeArr,TimeAdjMatrix,TimeAdjList");
        for(int i = 0;i < verticeArr.length;i++){
            combinedCSV.WriteLine(verticeArr[i] + "," + edgeArr[i] + "," + timeArr1[i] + "," + timeArr2[i]);
        }
    }

}