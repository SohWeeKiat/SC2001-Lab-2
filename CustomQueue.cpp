#include "CustomQueue.hpp"

namespace Dijkstra {

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