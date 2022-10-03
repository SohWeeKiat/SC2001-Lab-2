#include "PriorityQueue.hpp"
#include "DijstraDef.hpp"

namespace Queue {

	template<>
	PriorityQueueImp<Dijkstra::Edge>::
		PriorityQueueImp(int source, int size) : arr(size),
		index(size), artificial_size(size)
	{
		for (int i = 0; i < size; i++)
			this->arr[i].vertex = i;
		this->arr[source].weight = 0;
		this->Swap(source, 0);
	}

	template<>
	void PriorityQueueImp<Dijkstra::Edge>::Swap(int A, int B)
	{
		auto edge = this->arr[A];
		this->arr[A] = this->arr[B];
		this->arr[B] = edge;

		int temp = this->index[this->arr[A].vertex];
		this->index[this->arr[A].vertex] = this->index[this->arr[B].vertex];
		this->index[this->arr[B].vertex] = temp;
	}
}