#pragma once
// Cool bc no #include

namespace ali{
	template<typename T>
	class queue
	{
	public:
		queue() {

		}
		~queue() {

		}

		T front()
		{
			return next->value;
		}
		void pop()
		{
			if (!next)
				bEmpty = true;
			else {
				next = next->next;
				value = next->value;
			}
			sSize--;
		}
		void push(T value)
		{
			queue* n = new queue;
			n->value = value;
			n->next = nullptr;
			last->next = n;
			last = n;
			bEmpty = false;
			sSize++;
		}
		bool empty()
		{
			return bEmpty;
		}
		size_t size()
		{
			return sSize;
		}
	private:
		queue* next = nullptr;
		queue* last = this;
		T value;
		bool bEmpty = true;
		size_t sSize = 0;
	};
}