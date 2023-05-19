#pragma once
#pragma once
#include <iostream>

namespace ali{
	class smart_console_queue { // A queue that prints itself at end of scope
	public:
		template<typename T>
		void enqueue(const T& data) {
			if constexpr (!std::is_array<T>::value) {
				if constexpr (std::is_same<std::remove_all_extents_t<T>, std::string>::value)
					queue += data;
				else {
					queue += std::to_string(data);
				}
			}
			else {
				for (const auto& i : data)
				{
					enqueue(i);
				}
			}
		}
		smart_console_queue() {}
		~smart_console_queue() {
			printf(queue.c_str());
		}
	private:
		std::string queue = "";
	};
}