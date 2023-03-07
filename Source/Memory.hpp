#pragma once

namespace Saint
{
#pragma once
#include <span>

	namespace memory
	{
		template<typename T>
		concept SpanCompatibleType = requires(T a)
		{
			std::span{ a };
		};

		class byte_patch
		{
		public:
			virtual ~byte_patch();

			void apply() const;

			void restore() const;

			void remove() const;

			template <typename TAddr>
			static const std::unique_ptr<byte_patch>& make(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
			{
				return m_patches.emplace_back(
					std::unique_ptr<byte_patch>(new byte_patch(address, value)));
			}

			template <typename TAddr, typename T> requires SpanCompatibleType<T>
			static const std::unique_ptr<byte_patch>& make(TAddr address, T span_compatible)
			{
				return m_patches.emplace_back(
					std::unique_ptr<byte_patch>(new byte_patch(address, std::span{ span_compatible })));
			}

			static void restore_all();

		private:
			template <typename TAddr>
			byte_patch(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
				: m_address(address)
			{
				m_size = sizeof(std::remove_pointer_t<std::remove_reference_t<TAddr>>);

				m_original_bytes = std::make_unique<byte[]>(m_size);
				memcpy(m_original_bytes.get(), m_address, m_size);

				m_value = std::make_unique<byte[]>(m_size);
				memcpy(m_value.get(), &value, m_size);
			}

			template <typename TAddr, typename T, std::size_t N>
			byte_patch(TAddr address, std::span<T, N> span)
				: m_address((void*)address)
			{
				m_size = span.size();

				m_original_bytes = std::make_unique<byte[]>(m_size);
				memcpy(m_original_bytes.get(), m_address, m_size);

				m_value = std::make_unique<byte[]>(m_size);
				for (int i = 0; i < m_size; i++)
					m_value[i] = span[i];
			}

		protected:
			static inline std::vector<std::unique_ptr<byte_patch>> m_patches;

		private:
			void* m_address;
			std::unique_ptr<byte[]> m_value;
			std::unique_ptr<byte[]> m_original_bytes;
			std::size_t m_size;

			friend bool operator== (const std::unique_ptr<byte_patch>& a, const byte_patch* b);
		};
	}

	class MemoryHandle
	{
	public:
		/**
		 * \brief Constructs the object with a pointer
		 * \param p The pointer to initialize the object with, optional
		 */
		constexpr MemoryHandle(void* p = nullptr) :
			m_Ptr(p)
		{}

		/**
		 * \brief Constructs the object with an integral pointer
		 * \param p The integral pointer to initialize the object with
		 */
		explicit MemoryHandle(std::uintptr_t p) :
			m_Ptr(reinterpret_cast<void*>(p))
		{}

		/**
		 * \brief Retrieves the pointer as a pointer
		 * \return A pointer
		 */
		template <typename T>
		constexpr std::enable_if_t<std::is_pointer_v<T>, T> As()
		{
			return static_cast<T>(m_Ptr);
		}

		/**
		 * \brief Retrieves the pointer as a reference
		 * \return A pointer
		 */
		template <typename T>
		constexpr std::enable_if_t<std::is_lvalue_reference_v<T>, T> As()
		{
			return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(m_Ptr);
		}

		/**
		 * \brief Retrieves the pointer as an integral pointer
		 * \return An integral pointer
		 */
		template <typename T>
		constexpr std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> As()
		{
			return reinterpret_cast<T>(m_Ptr);
		}

		/**
		 * \brief Adds an offset to the pointer
		 * \param offset The offset to be added
		 * \return MemoryHandle
		 */
		template <typename T>
		constexpr MemoryHandle Add(T offset)
		{
			return MemoryHandle(As<std::uintptr_t>() + offset);
		}

		/**
		 * \brief Subtracted an offset to the pointer
		 * \param offset The offset to be subtracted
		 * \return MemoryHandle
		 */
		template <typename T>
		constexpr MemoryHandle Sub(T offset)
		{
			return MemoryHandle(As<std::uintptr_t>() - offset);
		}

		/**
		 * \brief Gets the relative displacement of the pointer
		 * \return MemoryHandle
		 */
		constexpr MemoryHandle Rip()
		{
			if (!m_Ptr)
				return nullptr;
			return Add(As<std::int32_t&>()).Add(4U);
		}

		/**
		 * \brief Checks if the stored pointer is valid
		 * \return bool
		 */
		constexpr explicit operator bool() noexcept
		{
			return m_Ptr;
		}
	protected:
		void* m_Ptr;
	};

	class MemoryRegion
	{
	public:
		/**
		 * \brief Constructs the region
		 * \param base The base of the region
		 * \param size The size of the region
		 */
		constexpr explicit MemoryRegion(MemoryHandle base, std::size_t size):
			m_Base(base),
			m_Size(size)
		{}

		/**
		 * \brief Gets the base of the region
		 * \return MemoryHandle
		 */
		constexpr MemoryHandle Base()
		{
			return m_Base;
		}

		/**
		 * \brief Gets the end of the region
		 * \return MemoryHandle
		 */
		constexpr MemoryHandle End()
		{
			return m_Base.Add(m_Size);
		}

		/**
		 * \brief Gets the size of the region
		 * \return std::size_t
		 */
		constexpr std::size_t Size()
		{
			return m_Size;
		}

		/**
		 * \brief Checks if p is within this region
		 * \param p The pointer
		 * \return bool
		 */
		constexpr bool Contains(MemoryHandle p)
		{
			if (p.As<std::uintptr_t>() < m_Base.As<std::uintptr_t>())
				return false;
			if (p.As<std::uintptr_t>() > m_Base.Add(m_Size).As<std::uintptr_t>())
				return false;

			return true;
		}
	protected:
		MemoryHandle m_Base;
		std::size_t m_Size;
	};

	class Module : public MemoryRegion
	{
	public:
		/**
		 * \brief Constructs the class with the main moduée
		 */
		explicit Module(std::nullptr_t):
			Module(static_cast<char*>(nullptr))
		{}
		
		/**
		 * \brief Constructs the class with a module name
		 * \param name The name of the module
		 */
		explicit Module(const char* name):
			Module(GetModuleHandleA(name))
		{
		}

		/**
		 * \brief Constructs the class with a module base
		 */
		Module(HMODULE hmod):
			MemoryRegion(hmod, 0)
		{
			auto dosHeader = m_Base.As<IMAGE_DOS_HEADER*>();
			auto ntHeader = m_Base.Add(dosHeader->e_lfanew).As<IMAGE_NT_HEADERS64*>();
			m_Size = ntHeader->OptionalHeader.SizeOfImage;
		}

		/**
		 * \brief Gets the DOS headers for the module
		 */
		IMAGE_DOS_HEADER* GetDosHeaders()
		{
			return m_Base.As<IMAGE_DOS_HEADER*>();
		}

		/**
		 * \brief Gets the NT headers for the module
		 */
		IMAGE_NT_HEADERS64* GetNtHeaders()
		{
			return m_Base.Add(m_Base.As<IMAGE_DOS_HEADER*>()->e_lfanew).As<IMAGE_NT_HEADERS64*>();
		}
	private:
		/**
		 * \brief Transforms a relative virtual address to a virtual address
		 */
		template <typename TReturn, typename TOffset>
		TReturn GetRVA(TOffset rva)
		{
			return m_Base.Add(rva).As<TReturn>();
		}
	};

	class Signature
	{
	public:
		struct Element
		{
			std::uint8_t m_Data{};
			bool m_Wildcard{};
		};

		/**
		 * \brief Constructs the signature with an IDA pattern
		 * \param pattern The IDA pattern string
		 */
		explicit Signature(const char* pattern)
		{
			auto toUpper = [](char c) -> char
			{
				return c >= 'a' && c <= 'z' ? static_cast<char>(c + ('A' - 'a')) : static_cast<char>(c);
			};

			auto isHex = [&](char c) -> bool
			{
				switch (toUpper(c))
				{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
					return true;
				default:
					return false;
				}
			};

			do
			{
				if (*pattern == ' ')
					continue;
				if (*pattern == '?')
				{
					m_Elements.push_back(Element{ {}, true });
					continue;
				}

				if (*(pattern + 1) && isHex(*pattern) && isHex(*(pattern + 1)))
				{
					char str[3] = { *pattern, *(pattern + 1), '\0' };
					auto data = std::strtol(str, nullptr, 16);

					m_Elements.push_back(Element{ static_cast<std::uint8_t>(data), false });
				}
			} while (*(pattern++));
		}

		/**
		 * \brief Scans for the pattern in a memory region
		 * \param region The region to search in, default is the main module
		 * \return MemoryHandle
		 */
		MemoryHandle Scan(MemoryRegion region = Module(nullptr))
		{
			auto compareMemory = [](std::uint8_t* data, Element* elem, std::size_t num) -> bool
			{
				for (std::size_t i = 0; i < num; ++i)
				{
					if (!elem[i].m_Wildcard)
						if (data[i] != elem[i].m_Data)
							return false;
				}

				return true;
			};

			for (std::uintptr_t i = region.Base().As<std::uintptr_t>(), end = region.End().As<std::uintptr_t>(); i != end; ++i)
			{
				if (compareMemory(reinterpret_cast<std::uint8_t*>(i),  m_Elements.data(), m_Elements.size()))
				{
					return MemoryHandle(i);
				}
			}

			return {};
		}
	private:
		std::vector<Element> m_Elements;
	};
}
