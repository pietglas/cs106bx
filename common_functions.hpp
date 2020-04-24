#include <utility>		// for std::move()

namespace commfunc {

template<typename T>
void swap(T& first, T& second) {
	T temp = std::move(first);
	first = std::move(second);
	second = std::move(temp);
}

}	// end namespace commfunc
