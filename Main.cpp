#include "Dijkstra.hpp"
#include <iostream>
#include <chrono>
#include <Windows.h>
#include "CSVGenerator.hpp"

#define MIN_WEIGHT 1
#define MAX_WEIGHT 50

std::vector<Dijkstra::AdjList> GenerateVertices(int count)
{
	std::vector<Dijkstra::AdjList> AdjListOfDiffEdge;
	Dijkstra::AdjList list(count);
	for (unsigned int v = 0; v < count - 1; v++)
		list[v].push_back(Dijkstra::Edge(v + 1, MIN_WEIGHT + rand() % MAX_WEIGHT));
	AdjListOfDiffEdge.push_back(list);
	unsigned int max_edges = std::pow(count, 2) - 1;
	unsigned int min_edge = min(100, count - 1);

	for (int edge = 2; edge <= min_edge; edge++) {
		for (unsigned int v = 0; v < count; v++) {
			if (list[v].size() < edge) {
				while (list[v].size() < edge) {
					unsigned int rand_vertex = rand() % count;
					while (rand_vertex == v || std::find(list[rand_vertex].begin(), 
						list[rand_vertex].end(),Dijkstra::Edge(v,0)) != list[rand_vertex].end())
						rand_vertex = rand() % count;
					list[v].push_back(Dijkstra::Edge(rand_vertex, MIN_WEIGHT + rand() % MAX_WEIGHT));
				}
			}
		}
		AdjListOfDiffEdge.push_back(list);
	}
	return AdjListOfDiffEdge;
}

void Test_APQ(int vertex_count, std::vector<Dijkstra::AdjList>& AdjListOfDiffEdge, CSVGenerator& csv)
{
	std::cout << "----------Starting Dijkstra_APQ----------" << std::endl;

	for (int i = 0; i < AdjListOfDiffEdge.size(); i++) {
		std::cout << "Edges: " << i + 1 << std::endl;
		auto list = AdjListOfDiffEdge[i];
		Dijkstra::Dijkstra_APQ apq(vertex_count, list, 0);
		unsigned int edge_count = 0;
		for (auto& i : list)
			edge_count += i.size();
		auto start_time = std::chrono::high_resolution_clock::now();
		apq.Solve();
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<
			std::chrono::microseconds>(end_time - start_time);
		std::cout << "Time taken by Dijkstra_APQ: " << duration.count() << " microseconds" << std::endl;

		csv.get() << vertex_count << "," << i + 1 << "," << duration.count() << "," << edge_count << "\n";
	}
}

void Test_MHPQ(int vertex_count, std::vector<Dijkstra::AdjList>& AdjListOfDiffEdge, CSVGenerator& csv)
{
	std::cout << "----------Starting Dijkstra_MHPQ----------" << std::endl;

	for (int i = 0; i < AdjListOfDiffEdge.size(); i++) {
		std::cout << "Edges: " << i + 1 << std::endl;
		auto list = AdjListOfDiffEdge[i];
		Dijkstra::Dijkstra_MHPQ mhpq(vertex_count, list, 0);
		unsigned int edge_count = 0;
		for (auto& i : list)
			edge_count += i.size();
		auto start_time = std::chrono::high_resolution_clock::now();
		mhpq.Solve();
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<
			std::chrono::microseconds>(end_time - start_time);
		std::cout << "Time taken by Dijkstra_MHPQ: " << duration.count() << " microseconds" << std::endl;

		csv.get() << vertex_count << "," << i + 1 << "," << duration.count()  << "," << edge_count << "\n";
	}
}

int main()
{
	srand(GetTickCount());

	CSVGenerator APQ_CSV("APQ.csv", "Vertex,MinimumEdge,Time,TotalEdge");
	CSVGenerator MHPQ_CSV("MHPQ.csv", "Vertex,MinimumEdge,Time");
	for (int i = 1; i <= 4; i++) {
		int vertex_count = std::pow(10, i);
		std::vector<Dijkstra::AdjList> AdjListOfDiffEdge = GenerateVertices(vertex_count);
		Test_APQ(vertex_count, AdjListOfDiffEdge, APQ_CSV);
		Test_MHPQ(vertex_count, AdjListOfDiffEdge, MHPQ_CSV);
	}
}