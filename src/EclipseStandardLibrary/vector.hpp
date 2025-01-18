#pragma once

#include "defines.hpp"

namespace estd {
	template <typename T>
	class vector {
	private:
		T* data;
		u64 _capacity;
		u64 _size;

	public:

		vector();
		u64 size();
		u64 capacity();
		void push_back(T _push_data);
		~vector();

		T& operator[](u64 _index);       // Indexing operator (modifiable)
		const T& operator[](u64 _index) const; // Indexing operator (read-only)
		
	};

	template <typename T>
	vector<T>::vector() {
		// Save memory for 1 value
		_capacity = 1;
		_size = 0;
		data = (T*)malloc(_capacity * sizeof(T));

		// Check for allocation
		// =================IMPLEMENTATION PENDING=====================
		//if (!data);
	}

	template <typename T>
	u64 vector<T>::size() {
		return _size;
	}

	template <typename T>
	u64 vector<T>::capacity() {
		return _capacity;
	}

	template <typename T>
	void vector<T>::push_back(T _push_data) {
		// Resize if not done
		if (_size >= _capacity) {
			_capacity *= 2;
			data = (T*)realloc(data, _capacity * sizeof(T));
		}
		
		// Check for allocation
		// =================IMPLEMENTATION PENDING=====================
		//if (!data);
		
		data[_size++] = _push_data;
	}

	template <typename T>
	vector<T>::~vector() {
		free(data);
	}

	template <typename T>
	T& vector<T>::operator[](u64 _index) {
		if (_index >= _size) {
			//throw std::out_of_range("Index out of range");
		}
		return data[_index];
	}

	template <typename T>
	const T& vector<T>::operator[](u64 _index) const {
		if (_index >= _size) {
			//throw std::out_of_range("Index out of range");
		}
		return data[_index];
	}
};