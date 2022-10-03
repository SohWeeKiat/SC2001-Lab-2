#pragma once
#include <vector>

namespace Queue {

	template<typename T>
	class PriorityQueueImp {

	public:
		PriorityQueueImp(int size) : arr(size), index(size),
			artificial_size(size)
		{
			for (int i = 0; i < size; i++)
				this.index[i] = i;
		}

		PriorityQueueImp(int source, int size);
		
		virtual void Update(const T& Obj) = 0;
		virtual int GetElement() = 0;
		int GetSize() { return this->artificial_size; }
	protected:
		std::vector<T> arr;
		std::vector<int> index;
		int artificial_size;

		void Swap(int A, int B);
	};
}