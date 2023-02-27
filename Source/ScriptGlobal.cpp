#pragma once
#include "Signatures.hpp"
#include "ScriptGlobal.hpp"

namespace Arctic
{
	global::global(std::size_t index) :
		m_index(index)
	{
	}

	global global::at(std::ptrdiff_t index)
	{
		return global(m_index + index);
	}

	global global::at(std::ptrdiff_t index, std::size_t size)
	{
		return global(m_index + 1 + (index * size));
	}

	void* global::get()
	{
		return g_GameVariables->m_GlobalBase[m_index >> 0x12 & 0x3F] + (m_index & 0x3FFFF);
	}
}
