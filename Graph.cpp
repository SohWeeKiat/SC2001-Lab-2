#include "Graph.hpp"

namespace Dijkstra {
	Graph::Graph(int Vertices, int MinimumEdge) : adjMatrix(Vertices)
	{
		printf("Generating %d %d", Vertices, MinimumEdge);
		for (int i = 0; i < Vertices; i++) {
			this->adjMatrix[i].resize(Vertices);
			memset(this->adjMatrix[i].data(), 0, sizeof(int) * this->adjMatrix[i].size());

			if (i + 1 < Vertices)
				this->adjMatrix[i][i + 1] = 1 + rand() % 50;//temp
		}
		for (int i = 0; i < Vertices; i++) {
			int EdgeCount = this->GetEdges(i);
			if (EdgeCount >= MinimumEdge) continue;
			int EdgeNeeded = MinimumEdge - EdgeCount;
			//if (EdgeNeeded == 1 && i == Vertices - 1) continue;
			for (int v = EdgeNeeded; v > 0;) {
				for (int ed = 0; ed < this->adjMatrix[i].size(); ed++) {
					if (!this->adjMatrix[i][ed]) {
						this->adjMatrix[i][ed] = 1 + rand() % 50;
						v--;
					}
				}
			}
		}
	}

	AdjList Graph::GetList()
	{
		AdjList list(this->adjMatrix.size());
		int vertices = this->adjMatrix.size();
		for (int i = 0; i < this->adjMatrix.size(); i++) {
			for (int x = 0; x < vertices; x++) {
				if (this->adjMatrix[i][x])
					list[i].push_back(Edge(x, this->adjMatrix[i][x]));
			}
		}
		return list;
	}

	int Graph::GetEdges(int src)
	{
		int Count = 0;
		for (int i = 0; i < this->adjMatrix[src].size(); i++) {
			if (this->adjMatrix[src][i])
				Count++;
		}
		return Count;
	}

	/****************************************************************/

	GraphV2::GraphV2(int Vertices, int EdgeCount, int MinWeight, int MaxWeight
		, GraphGenerateMode Mode) : adjMatrix(Vertices), Vertices(Vertices)
	{
		for (int i = 0; i < Vertices; i++) {
			this->adjMatrix[i].resize(Vertices);
			for (int x = 0; x < Vertices; x++)
				this->adjMatrix[i][x] = 0;
		}
		if (Mode == GGM_Random) {//random edges, max edge = EdgeCount
			this->GenerateRandomGraph(EdgeCount, MinWeight, MaxWeight);
			return;
		}
		else if (Mode == GGM_MinimumPerVertex) {
			for (unsigned int v = 0; v < Vertices; v++) {//base , vertex 1 > 2 > 3
				if (v + 1 < Vertices)
					this->adjMatrix[v][v+1] = MinWeight + rand() % MaxWeight;
			}
			int ActualNeeded = std::min(this->Vertices - 1, EdgeCount);
			for (unsigned int v = 0; v < Vertices; v++) {
				int Edges = this->GetEdges(v);
				if (Edges >= ActualNeeded) {
					this->EdgeCount += Edges;
					continue;
				}
				else if (this->EdgeCount >= EdgeCount)
					continue;
				int EdgesNeeded = ActualNeeded - Edges;
				this->EdgeCount += ActualNeeded;
				this->MinimumEdgePerVertex = std::min(ActualNeeded, this->MinimumEdgePerVertex);
				for (int i = 0; i < EdgesNeeded; ) {
					int dest = rand() % Vertices;
					if (v != dest && !this->ExistEdge(v, dest)) {
						int weight = MinWeight + rand() % MaxWeight;
						this->adjMatrix[v][dest] = weight;
						i++;
					}
				}
			}
		}
		else if (Mode == GGM_NoOfEdgesPerGraph) {
			this->GenerateXEdges(EdgeCount, MinWeight, MaxWeight);
		}
	}

	void GraphV2::GenerateRandomGraph(int EdgeCount, int MinWeight, int MaxWeight)
	{
		int maxEdges = Vertices * (Vertices - 1);
		this->EdgeCount = rand() % (maxEdges - Vertices + 1) + 1;
		for (int i = 0; i < this->EdgeCount; ) {
			int src = rand() % Vertices;
			int dest = rand() % Vertices;
			if (src != dest && !this->ExistEdge(src, dest)) {
				int weight = MinWeight + rand() % MaxWeight;
				this->adjMatrix[src][dest] = weight;
				i++;
			}
		}
	}

	void GraphV2::GenerateXEdges(int EdgeCount, int MinWeight, int MaxWeight)
	{
		int maxEdges = Vertices * (Vertices - 1);
		this->EdgeCount = std::min(EdgeCount, maxEdges);//rand() % (maxEdges - Vertices + 1) + 1;
		for (int i = 0; i < this->EdgeCount; ) {
			int src = rand() % Vertices;
			int dest = rand() % Vertices;
			if (src != dest && !this->ExistEdge(src, dest)) {
				int weight = MinWeight + rand() % MaxWeight;
				this->adjMatrix[src][dest] = weight;
				i++;
			}
		}
	}

	AdjList GraphV2::GetList()
	{
		AdjList list(this->adjMatrix.size());
		int vertices = this->adjMatrix.size();
		for (int i = 0; i < this->adjMatrix.size(); i++) {
			for (int x = 0; x < vertices; x++) {
				if (this->adjMatrix[i][x])
					list[i].push_back(Edge(x, this->adjMatrix[i][x]));
			}
		}
		return list;
	}

	int GraphV2::GetEdges(int src)
	{
		int Count = 0;
		for (int i = 0; i < this->adjMatrix[src].size(); i++) {
			if (this->adjMatrix[src][i])
				Count++;
		}
		return Count;
	}

	void GraphV2::removeEdge()
	{
		bool finished = false;
		for (int i = 0; i < this->adjMatrix.size(); i++) {
			for (int x = 0; x < this->adjMatrix[i].size(); x++) {
				if (this->adjMatrix[i][x]) {
					this->adjMatrix[i][x] = 0;
					this->EdgeCount--;
					finished = true;
					break;
				}
			}
			if (finished) break;
		}
	}
}