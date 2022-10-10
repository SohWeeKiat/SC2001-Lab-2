#include "Dijkstra.hpp"
#include <iostream>
#include <chrono>
#include <Windows.h>
#include "CSVGenerator.hpp"
#include "Graph.hpp"

#define MIN_WEIGHT 1
#define MAX_WEIGHT 50

std::vector<Dijkstra::AdjList> GenerateVertices(int count)
{
	std::vector<Dijkstra::AdjList> AdjListOfDiffEdge;
	Dijkstra::AdjList list(count);
	for (unsigned int v = 0; v < count - 1; v++)
		list[v].push_back(Dijkstra::Edge(v + 1, 1));
	AdjListOfDiffEdge.push_back(list);
	unsigned int max_edges = std::pow(count, 2) - 1;
	unsigned int min_edge = min(1000, count - 1);

	for (int edge = 2; edge <= min_edge; edge++) {
		for (unsigned int v = 0; v < count; v++) {
			if (list[v].size() < edge) {
				while (list[v].size() < edge) {
					unsigned int rand_vertex = rand() % count;
					while (rand_vertex == v || std::find(list[rand_vertex].begin(),
						list[rand_vertex].end(), Dijkstra::Edge(v, 0)) != list[rand_vertex].end()) {
						rand_vertex = rand() % count;
					}
					list[v].push_back(Dijkstra::Edge(rand_vertex, 1));
				}
			}
		}
		AdjListOfDiffEdge.push_back(list);
	}
	return AdjListOfDiffEdge;
}

Dijkstra::GraphV2 GenerateVerticesV2(int count)
{
	return Dijkstra::GraphV2(count, (count * count) - 1, MIN_WEIGHT, MAX_WEIGHT, 
		Dijkstra::GraphGenerateMode::GGM_NoOfEdgesPerGraph);
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
			std::chrono::nanoseconds>(end_time - start_time);
		std::cout << "Time taken by Dijkstra_APQ: " << duration.count() << " microseconds" << std::endl;

		csv.get() << vertex_count << "," << i + 1 << "," << duration.count() << "," << edge_count << "\n";
	}
}

void Test_APQV2(int vertex_count, Dijkstra::GraphV2& AdjListOfDiffEdge, CSVGenerator& csv, int AverageTimes)
{
	std::cout << "----------Starting Dijkstra_APQ----------" << std::endl;

	//for (int i = 0; i < AdjListOfDiffEdge.size(); i++) {
		//std::cout << "Edges: " << i + 1 << std::endl;

		unsigned __int64 avgTotal = 0;
		for (int x = 0; x < AverageTimes; x++) {
			//auto list = AdjListOfDiffEdge[i];
			Dijkstra::Dijkstra_APQ apq(vertex_count, AdjListOfDiffEdge.GetMatrix(), 0);
			auto start_time = std::chrono::high_resolution_clock::now();
			apq.Solve();
			auto end_time = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<
				std::chrono::nanoseconds>(end_time - start_time);
			avgTotal += duration.count();
		}
		avgTotal /= AverageTimes;

		std::cout << "Time taken by Dijkstra_APQ: " << avgTotal << " microseconds" << std::endl;

		csv.get() << vertex_count << "," << AdjListOfDiffEdge.GetEdgeCount() << "," << avgTotal << "," << AdjListOfDiffEdge.GetEdgeCount() << "\n";
	//}
}

void Test_APQV3(int vertex_count, int MinimumEdgePerVertex, Dijkstra::GraphV2& g, CSVGenerator& csv)
{
	std::cout << "----------Starting Dijkstra_APQ----------" << std::endl;

	Dijkstra::Dijkstra_APQ apq(vertex_count, g.GetMatrix(), 0);
	auto start_time = std::chrono::high_resolution_clock::now();
	apq.Solve();
	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<
		std::chrono::nanoseconds>(end_time - start_time);
	std::cout << "Time taken by Dijkstra_APQ: " << duration.count() << " microseconds" << std::endl;

	csv.get() << vertex_count << "," << g.GetMinimumEdgePerVertex() << "," <<
		duration.count() << "," << g.GetEdgeCount() << "\n";
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
			std::chrono::nanoseconds>(end_time - start_time);
		std::cout << "Time taken by Dijkstra_MHPQ: " << duration.count() << " microseconds" << std::endl;

		csv.get() << vertex_count << "," << i + 1 << "," << duration.count()  << "," << edge_count << "\n";
	}
}

void Test_MHPQV2(int vertex_count, Dijkstra::GraphV2& AdjListOfDiffEdge, CSVGenerator& csv, int averageTimes)
{
	std::cout << "----------Starting Dijkstra_MHPQ----------" << std::endl;

	//for (int i = 0; i < AdjListOfDiffEdge.size(); i++) {
		//std::cout << "Edges: " << i + 1 << std::endl;

		unsigned __int64 avgTotal = 0;
		for (int x = 0; x < averageTimes; x++) {
			Dijkstra::Dijkstra_MHPQ mhpq(vertex_count, AdjListOfDiffEdge.GetList(), 0);
			auto start_time = std::chrono::high_resolution_clock::now();
			mhpq.Solve();
			auto end_time = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<
				std::chrono::nanoseconds>(end_time - start_time);
			avgTotal += duration.count();
		}
		avgTotal /= averageTimes;

		std::cout << "Time taken by Dijkstra_MHPQ: " << avgTotal << " microseconds" << std::endl;

		csv.get() << vertex_count << "," << AdjListOfDiffEdge.GetEdgeCount() << "," << avgTotal << "," << AdjListOfDiffEdge.GetEdgeCount() << "\n";
	//}
}

void Test_MHPQV3(int vertex_count, int MinimumEdgePerVertex, Dijkstra::GraphV2& g, CSVGenerator& csv)
{
	std::cout << "----------Starting Dijkstra_MHPQ----------" << std::endl;
	Dijkstra::Dijkstra_MHPQ mhpq(vertex_count, g.GetList(), 0);
	auto start_time = std::chrono::high_resolution_clock::now();
	mhpq.Solve();
	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<
		std::chrono::nanoseconds>(end_time - start_time);
	std::cout << "Time taken by Dijkstra_MHPQ: " << duration.count() << " microseconds" << std::endl;

	csv.get() << vertex_count << "," << g.GetMinimumEdgePerVertex() << "," << duration.count() << "," << g.GetEdgeCount() << "\n";
}

void TestV2()
{
	CSVGenerator APQ_CSV("APQ.csv", "Vertex,MinimumEdge,Time,Edges");
	CSVGenerator MHPQ_CSV("MHPQ.csv", "Vertex,MinimumEdge,Time,Edges");
	for (int i = 1; i <= 2; i++) {
		int vertex_count = std::pow(10, i);
		Dijkstra::GraphV2 AdjListOfDiffEdge = GenerateVerticesV2(vertex_count);
		for (int i2 = 0; i2 < vertex_count * vertex_count - 1; i2++) {
			Test_APQV2(vertex_count, AdjListOfDiffEdge, APQ_CSV, 1000);
			Test_MHPQV2(vertex_count, AdjListOfDiffEdge, MHPQ_CSV, 1000);
			AdjListOfDiffEdge.removeEdge();
			APQ_CSV.get().flush();
			MHPQ_CSV.get().flush();
		}
	}
}

void TestV1()
{
	CSVGenerator APQ_CSV("APQ_V1.csv", "Vertex,MinimumEdge,Time,Edges");
	CSVGenerator MHPQ_CSV("MHPQ_V1.csv", "Vertex,MinimumEdge,Time,Edges");
	for (int i = 1; i <= 3; i++) {
		int vertex_count = std::pow(10, i);
		std::vector<Dijkstra::AdjList> AdjListOfDiffEdge = GenerateVertices(vertex_count);
		Test_APQ(vertex_count, AdjListOfDiffEdge, APQ_CSV);
		Test_MHPQ(vertex_count, AdjListOfDiffEdge, MHPQ_CSV);
	}
}

void TestV3()
{
	CSVGenerator APQ_CSV("APQ.csv", "Vertex,MinimumEdge,Time,Edges");
	CSVGenerator MHPQ_CSV("MHPQ.csv", "Vertex,MinimumEdge,Time,Edges");

	int EdgeCount = 2000;
	for (int VerticesCount = 50; VerticesCount <= 1001; VerticesCount += 10) {
		Dijkstra::GraphV2 g(VerticesCount, EdgeCount, MIN_WEIGHT, MAX_WEIGHT, 
			Dijkstra::GraphGenerateMode::GGM_NoOfEdgesPerGraph);
		Test_APQV3(VerticesCount, EdgeCount, g, APQ_CSV);
		Test_MHPQV3(VerticesCount, EdgeCount, g, MHPQ_CSV);
	}
}

int main()
{
	srand(GetTickCount());
	TestV1();
	TestV3();
}