#pragma once
#include "Signatures.hpp"

namespace Arctic
{
	class global
	{
	public:
		explicit global(std::size_t index);

		global at(std::ptrdiff_t index);
		global at(std::ptrdiff_t index, std::size_t size);

		template <typename T>
		std::enable_if_t<std::is_pointer_v<T>, T> as()
		{
			return static_cast<T>(get());
		}

		template <typename T>
		std::enable_if_t<std::is_lvalue_reference_v<T>, T> as()
		{
			return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(get());
		}
	private:
		void* get();
		std::size_t m_index;
	};
}
