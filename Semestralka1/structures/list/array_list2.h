#pragma once

#include "array_list.h"

namespace structures
{
	/// <summary> Zoznam implementovany polom s premenlivou pociatocnou velkostou pola. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class ArrayList2 : public ArrayList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ArrayList2();

		/// <summary> Konstruktor s pociatocnou velkostou pola. </summary>
		ArrayList2(size_t initialSize);
	private:
		typedef structures::ArrayList<T> super;
	};

	template<typename T>
	inline ArrayList2<T>::ArrayList2()
	{
	}

	template<typename T>
	inline ArrayList2<T>::ArrayList2(size_t initialSize)
	{
		if (initialSize > ARRAYLIST_ARRAY_INITIAL_SIZE)
		{
			delete super::array_;
			super::array_ = new structures::Array<T>(initialSize + ARRAYLIST_ARRAY_INITIAL_SIZE);
		}
	}
}
