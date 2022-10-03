#include "Dijkstra.hpp"

namespace Dijkstra {

	PriorityQueueArr::PriorityQueueArr(int source, int size) : 
		Queue::PriorityQueueImp<Edge>(source, size)
	{
	}

	int PriorityQueueArr::GetElement()
	{
		int last_valid_vertex = 0;
		for (; last_valid_vertex < this->arr.size(); last_valid_vertex++) {
			if (this->arr[last_valid_vertex].vertex != -1)
				break;
		}
		Edge min = this->arr[last_valid_vertex];

		for (int i = last_valid_vertex + 1; i < this->arr.size(); i++)
		{
			if (this->arr[i].vertex != -1 && 
				this->arr[i].weight < min.weight)
			{
				min = this->arr[i];
			}
		}
		this->arr[this->index[min.vertex]].vertex = -1;
		this->index[min.vertex] = -1;

		return min.vertex;
	}

	void PriorityQueueArr::Update(const Edge& Obj)
	{
		this->arr[this->index[Obj.vertex]].weight = Obj.weight;
	}

	/***********************************************************************/

	PriorityQueueHeap::PriorityQueueHeap(int source, int size) :
		Queue::PriorityQueueImp<Edge>(source, size)
	{
	}

	int PriorityQueueHeap::GetElement()
	{
		int temp = this->arr[0].vertex;
		this->Swap(0, this->artificial_size - 1);
		this->index[this->arr[this->artificial_size - 1].vertex] = -1;
		this->artificial_size--;
		this->FixHeap(0);

		return temp;
	}

	void PriorityQueueHeap::Update(const Edge& Obj)
	{
		this->arr[this->index[Obj.vertex]].weight = Obj.weight;
		this->Bubble(this->index[Obj.vertex]);
	}

	void PriorityQueueHeap::Bubble(int index)
	{
		if (!index) return;
		if (this->arr[index].weight < this->arr[this->Parent(index)].weight) {
			this->Swap(index, this->Parent(index));
			this->Bubble(this->Parent(index));
		}
	}

	void PriorityQueueHeap::FixHeap(int index)
	{
		if (this->LeftChild(index) >= this->artificial_size && 
			this->RightChild(index) >= this->artificial_size)//no child, base case
			return;

		if (this->RightChild(index) < this->artificial_size &&
			this->arr[this->RightChild(index)].weight <= this->arr[this->LeftChild(index)].weight &&
			this->arr[this->RightChild(index)].weight < this->arr[index].weight)
		{
			this->Swap(index, this->RightChild(index));
			this->FixHeap(this->RightChild(index));
		}
		else if (this->arr[this->LeftChild(index)].weight < 
			this->arr[index].weight)
		{
			this->Swap(index, this->LeftChild(index));
			this->FixHeap(this->LeftChild(index));
		}
	}

	int PriorityQueueHeap::Parent(int index)
	{
		return (index + 1) / 2 - 1;// account for 0 index, hence +1 & -1
	}

	int PriorityQueueHeap::LeftChild(int index)
	{
		return 2 * (index + 1) - 1;// account for 0 index, hence +1 & -1
	}

	int PriorityQueueHeap::RightChild(int index)
	{
		return 2 * (index + 1);// account for 0 index, but since -1 + 1 = 0
	}

	/***********************************************************************/

	Dijkstra_APQ::Dijkstra_APQ(int vertex_count, AdjList& edges, int start_vertex) : 
		DijkstraImp<AdjMatrix>(start_vertex, vertex_count),
		pq(start_vertex, vertex_count)
	{
		this->edgeLinkages.resize(vertex_count);
		for (int i = 0; i < vertex_count; i++) {
			this->edgeLinkages[i].resize(vertex_count);
			memset(this->edgeLinkages[i].data(), 0, sizeof(int) * this->edgeLinkages[i].size());

			for (auto& e : edges[i])
				this->edgeLinkages[i][e.vertex] = e.weight;
		}
	}

	void Dijkstra_APQ::Solve()
	{
		int remaining = this->pq.GetSize();
		while (remaining > 0) {
			int u = this->pq.GetElement();
			this->S[u] = true;
			for (int i = 0; i < this->vertex_count; i++) {
				if (this->edgeLinkages[u][i] == 0)
					continue;//no linkage
				Edge v(i, this->edgeLinkages[u][i]);
				if (!this->S[v.vertex] && this->dist[v.vertex] > this->dist[u] + v.weight) {
					this->dist[v.vertex] = this->dist[u] + v.weight;
					this->pred[v.vertex] = u;
					this->pq.Update(Edge(v.vertex, this->dist[v.vertex]));
				}
			}
		}
	}

	/***********************************************************************/

	Dijkstra_MHPQ::Dijkstra_MHPQ(int vertex_count, AdjList& edges, int start_vertex) :
		DijkstraImp<AdjList>(start_vertex, vertex_count),
		pq(start_vertex, vertex_count)
	{
		this->edgeLinkages = edges;
	}

	void Dijkstra_MHPQ::Solve()
	{
		while (this->pq.GetSize()) {
			int u = this->pq.GetElement();
			this->S[u] = true;
			for (int i = 0; i < this->edgeLinkages[u].size(); i++) {
				Edge v = this->edgeLinkages[u][i];

				if (!this->S[v.vertex] && this->dist[v.vertex] > this->dist[u] + v.weight) {
					this->dist[v.vertex] = this->dist[u] + v.weight;
					this->pred[v.vertex] = u;
					this->pq.Update(Edge(v.vertex, this->dist[v.vertex]));
				}
			}
		}
	}
}