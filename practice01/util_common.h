#ifndef UTIL_COMMON_H_
#define UTIL_COMMON_H_

namespace nexon {
namespace util {
namespace common {
template <typename T>
class Singleton {
public :
	Singleton() = default;
	virtual ~Singleton() = default;

	static T& GetInstance() {
		static T instance;
		return instance;
	}

	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) = delete;
};
} // namespace common
} // namespace util
} // namespace nexon

#endif // UTIL_COMMON_H_