// MIT
// Allosker - 2025
// ===================================================
// Defines a proxy struct, a proxy allows the integration of a common base access variable such as 'T().a'
// without allowing the user to change the underlying pointer.
// ===================================================


namespace mpml
{


template<typename T>
struct Proxy
{
	T* value;

	constexpr Proxy()
		: value{nullptr}
	{}

	constexpr Proxy(T& value_)
		: value{ &value_ }
	{}

	constexpr Proxy(T* value_)
		: value{ value_ }
	{}


	// Explicit conversions to trick the compiler
	constexpr operator T& () noexcept { return *value; }
	constexpr operator const T& () const noexcept { return *value; }
	 
	constexpr Proxy& operator=(const T& arg_) noexcept
	{
		*value = arg_;
		return *this;
	}

	constexpr Proxy& operator=(T&& arg_) noexcept
	{
		*value = arg_;
		return *this;
	}

	constexpr void set(T* ptr) { value = ptr; }
};


} // mpml