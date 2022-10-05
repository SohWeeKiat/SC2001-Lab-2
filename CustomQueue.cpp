#include "CustomQueue.hpp"

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

	template<>
	Edge PriorityQueueArrV2<Edge>::top()
	{
		auto lowest = this->begin();
		for (int i = 1; i < this->size(); i++) {
			if (this->at(i).weight < lowest->weight)
				lowest = this->begin() + i;
		}
		Edge res = *lowest;
		this->erase(lowest);
		return res;
	}
};