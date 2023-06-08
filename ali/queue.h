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
		template<typename Function>
		void for_every(Function func) // Function can be of any return type, but it must take one parameter of same type as the object
		{
			queue* saved = this->next;
			for (size_t i = 0; i < sSize; i++)
			{
				func(saved->value);
				saved = saved->next;
			}
		}
	private:
		queue* next = nullptr;
		queue* last = this;
		T value;
		bool bEmpty = true;
		size_t sSize = 0;
	};
}