#ifndef P_KIT
#define P_KIT

namespace punkyoi_api {

	template<typename T, T head, T...tail>
	class kit : kit<T, tail...> {
	public:
		kit() {
		}

		~kit() {
		}

		constexpr auto operator[] (size_t i) {
			return reinterpret_cast<T*>(this)[i];
		}

		constexpr auto begin() {
			return reinterpret_cast<T*>(this);
		}

		constexpr auto end() {
			return reinterpret_cast<T*>(this) + sizeof...(tail) + 1;
		}

		T value = head;
	};

	template<typename T, T head>
	class kit<T, head> {
	public:
		kit() {
		}

		~kit() {
		}

		constexpr auto operator[] (size_t i) {
			return reinterpret_cast<T*>(this)[i];
		}

		constexpr auto begin() {
			return reinterpret_cast<T*>(this);
		}

		constexpr auto end() {
			return reinterpret_cast<T*>(this) + 1;
		}

		T value = head;
	};

}

#endif