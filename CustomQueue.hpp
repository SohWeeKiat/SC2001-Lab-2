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
	class custom_priority_queue : public std::priority_queue<T, std::vector<T>, std::greater<T>> {

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

		void Update(const T& value) {
			auto it = std::find(this->c.begin(), this->c.end(), value);

			if (it == this->c.end())
				return;
			else {
				*it = value;
				std::make_heap(this->c.begin(), this->c.end(), this->comp);
			}
		}
	};

	template<typename T>
	class custom_priority_queueV2 : public std::vector<T> {

	public:
		T top()
		{
			T obj = this->at(0);
			this->Swap(0, this->ActualItemCount - 1);
			this->ActualItemCount--;
			this->FixHeap(0);

			return obj;
		}

		void push(const T& obj)
		{
			this->push_back(obj);
			this->FixHeap(this->size() - 1);
			this->ActualItemCount++;
		}

		void Update(const T& value) {
			auto it = std::find(this->begin(), this->end(), value);

			if (it == this->end())
				return;
			else {
				*it = value;
				if (this->begin() == it)
					this->FixHeap(0);
				else
					this->FixHeap(it - this->begin());
			}
		}

		bool IsEmpty() { return this->ActualItemCount == 0; }
	private:
		int ActualItemCount = 0;

		void FixHeap(int index)
		{
			if (this->LeftChild(index) >= this->ActualItemCount &&
				this->RightChild(index) >= this->ActualItemCount)//no child, base case
				return;

			if (this->RightChild(index) < this->ActualItemCount &&
				this->at(this->RightChild(index)) <= this->at(this->LeftChild(index)) &&
				this->at(this->RightChild(index)) < this->at(index))
			{
				this->Swap(index, this->RightChild(index));
				this->FixHeap(this->RightChild(index));
			}
			else if (this->at(this->LeftChild(index)) <
				this->at(index))
			{
				this->Swap(index, this->LeftChild(index));
				this->FixHeap(this->LeftChild(index));
			}
		}
		void Bubble(int index)
		{
			if (!index) return;
			if (this->at(index) < this->at(this->Parent(index))) {
				this->Swap(index, this->Parent(index));
				this->Bubble(this->Parent(index));
			}
		}

		void Swap(int A, int B)
		{
			auto edge = this->at(A);
			this->at(A) = this->at(B);
			this->at(B) = edge;
		}

		int Parent(int index)
		{
			return (index + 1) / 2 - 1;// account for 0 index, hence +1 & -1
		}

		int LeftChild(int index)
		{
			return 2 * (index + 1) - 1;// account for 0 index, hence +1 & -1
		}

		int RightChild(int index)
		{
			return 2 * (index + 1);// account for 0 index, but since -1 + 1 = 0
		}
	};
}