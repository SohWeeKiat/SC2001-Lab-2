#pragma once
#include "DijstraDef.hpp"

namespace Dijkstra {
	class Graph {

	public:
		Graph(int Vertices, int MinimumEdge);

		AdjList GetList();
	private:
		AdjMatrix adjMatrix;

		bool ExistEdge(int src, int dest)
		{
			return this->adjMatrix[src][dest] != 0;
		}

		int GetEdges(int src);
	};

	enum GraphGenerateMode {
		GGM_Random,//random edges, max edge = EdgeCount
		GGM_MinimumPerVertex,
		GGM_NoOfEdgesPerGraph
	};

	class GraphV2 {

	public:
		GraphV2(int Vertices, int EdgeCount, int MinWeight, int MaxWeight
			, GraphGenerateMode Mode);

		void removeEdge();
		AdjList GetList();
		AdjMatrix& GetMatrix() { return this->adjMatrix; }
		int GetEdgeCount() { return this->EdgeCount; }
		int GetMinimumEdgePerVertex() { return this->MinimumEdgePerVertex; }
	private:
		AdjMatrix adjMatrix;
		int EdgeCount;
		int Vertices;
		int MinimumEdgePerVertex = INT_MAX;

		void GenerateRandomGraph(int EdgeCount, int MinWeight, int MaxWeight);
		void GenerateXEdges(int EdgeCount, int MinWeight, int MaxWeight);
		bool ExistEdge(int src, int dest)
		{
			return this->adjMatrix[src][dest] != 0;
		}

		int GetEdges(int src);
	};
}