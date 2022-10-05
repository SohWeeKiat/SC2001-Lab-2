#pragma once
#include "DijstraDef.hpp"
#include <queue>

namespace Dijkstra {
	template<typename T>
	class PriorityQueueArrV2 : public std::vector<T> {

	public:
		T top();

		bool remove(const T& value) {
			auto it = std::find(this->begin(), this->end(), value);

			if (it == this->end())
				return false;
			this->erase(it);
			return true;
		}
	};

	template<typename T>
	class custom_priority_queue : public std::priority_queue<T, std::vector<T>> {

	public:
		bool remove(const T& value) {
			auto it = std::find(this->c.begin(), this->c.end(), value);

			if (it == this->c.end())
				return false;
			if (it == this->c.begin()) 
				this->pop();
			else {
				// remove element and re-heap
				this->c.erase(it);
				std::make_heap(this->c.begin(), this->c.end(), this->comp);
			}
			return true;
		}
	};
}