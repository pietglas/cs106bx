#include <utility>		// for std::move()

template<typename T>
void swap(T& first, T& second) {
	T temp = std::move(first);
	first = std::move(second);
	second = std::move(temp);
}
