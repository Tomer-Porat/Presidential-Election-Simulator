#pragma once
namespace election {
	template <class T>
	class DynamicArray
	{
	public:
		DynamicArray(int size = 2) : _logicalSize(0), _physicalSize(size), _arr(new T[size]) {}

		DynamicArray(const DynamicArray& other) : _arr(nullptr) {
			*this = other;
		}
		~DynamicArray() {
			delete[] _arr;
		}

		const DynamicArray& operator=(const DynamicArray& other) {
			if (this != &other) {
				_logicalSize = other._logicalSize;
				_physicalSize = other._physicalSize;
				delete[] _arr;
				_arr = new T[_physicalSize];
				for (int i = 0; i < _logicalSize; i++)
					_arr[i] = other._arr[i];
			}
			return *this;
		}

		const T& operator[](int i) const { return _arr[i]; }
		T& operator[](int i) { return _arr[i]; }

		void push_back(const T& value) {
			if (_logicalSize == _physicalSize)
				resize();
			_arr[_logicalSize++] = value;
		}

		const T& front()    const { return _arr[0]; }
		int      size()     const { return _logicalSize; }
		int      capacity() const { return _physicalSize; }
		bool     empty()    const { return _logicalSize == 0; }
		void     clear() { _logicalSize = 0; }

		class iterator
		{
		private:
			DynamicArray* _da;
			int				_i;
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;
			iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
			iterator(const iterator& other) : _da(other._da), _i(other._i) {}
			friend class const_iterator;

			const iterator& operator=(const iterator& other) {
				_da = other._da;
				_i = other._i;
				return *this;
			}

			// comparison with another iterator
			bool operator==(const iterator& other) const {
				return (_da == other._da) && (_i == other._i);
			}
			bool operator!=(const iterator& other) const {
				return !(*this == other);
			}

			// smart-pointer iterator methods
			T& operator*() {
				return _da->_arr[_i];
			}
			T* operator->() {
				return &_da->_arr[_i];
			}

			// increment-decrement iterator methods
			iterator& operator++() {
				++_i;
				return *this;
			}
			iterator operator++(int) {
				iterator temp(*this);
				++_i;
				return temp;
			}
			iterator& operator--() {
				--_i;
				return *this;
			}
			iterator operator--(int) {
				iterator temp(*this);
				--_i;
				return temp;
			}
		};
		class const_iterator {
		private:
			DynamicArray* _da;
			int				_i;
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			// other options exist, e.g., std::forward_iterator_tag
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			const_iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
			const_iterator(const iterator& other) : _da(other._da), _i(other._i) {}

			const const_iterator& operator=(const const_iterator& other) {
				_da = other._da;
				_i = other._i;
				return *this;
			}
			const const_iterator& operator=(const iterator& other) {
				_da = other._da;
				_i = other._i;
				return *this;
			}

			// comparison with another iterator
			bool operator==(const iterator& other) const {
				return (_da == other._da) && (_i == other._i);
			}
			bool operator!=(const iterator& other) const {
				return !(*this == other);
			}

			// smart-pointer iterator methods
			T& operator*() {
				return _da->_arr[_i];
			}
			T* operator->() {
				return &_da->_arr[_i];
			}

			// increment-decrement iterator methods
			const_iterator& operator++() {
				++_i;
				return *this;
			}

			const_iterator operator++(int) {
				const_iterator temp(*this);
				++_i;
				return temp;
			}
			const_iterator& operator--() {
				--_i;
				return *this;
			}
			const_iterator operator--(int) {
				const_iterator temp(*this);
				--_i;
				return temp;
			}

		};


		iterator begin() {
			return iterator(*this, 0);
		}
		iterator end() {
			return iterator(*this, _logicalSize);
		}

		const_iterator cbegin() const {
			return const_iterator(*this, 0);
		}
		const_iterator cend() const {
			return const_iterator(*this, _logicalSize);
		}

		iterator insert(const iterator& pos, const T& val) {
			if (_logicalSize == _physicalSize)
				resize();

			iterator itrEnd = end();
			iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
			while (itrCurrent != pos)
			{
				*itrCurrent = *itrPrev;
				itrCurrent = itrPrev--;
			}

			iterator p = pos;
			*p = val;
			++_logicalSize;
			return p;
		}

		iterator& erase(const iterator& iter) {
			iterator res = begin();
			int counter = 0, j = 0;
			_logicalSize--;
			T* tmp = new T[_logicalSize];
			for (int i = 0; i < _logicalSize; i++)
			{
				if (res == iter) {
					counter = i;
					j++;
					i--;
				}
				else {
					tmp[i] = _arr[j];
					j++;
				}
				res++;
			}
			delete[] _arr;
			_arr = tmp;
			res = begin();
			while (counter != 1) {
				res++;
				counter--;
			}
			_physicalSize = _logicalSize;
			return res;
		}
		iterator& erase(const iterator& first, const iterator& last) {
			int countToFirst = 0;
			int countToDel = 0;
			iterator iterBegin = begin();
			iterator curr = first;
			while(curr != first){
				countToFirst++;
			}
			while (curr != last)
			{
				countToDel++;
			}
			_logicalSize -= countToDel;
			_physicalSize -= countToDel;
			T* tmp = new T[_logicalSize];
			curr = begin();
			int write = 0, read = 0;
			while (curr != first) {//Copy all elements until "first" to the new array.
				tmp[write] = _arr[read];
				write++;
				read++;
				curr++;
			}
			//Skip the elements to delete:
			curr = last;
			read += countToDel;
			while (curr != end()) {//Copy all elements from "last" to the end.
				tmp[write] = _arr[read];
				write++;
				read++;
				curr++;
			}
			delete[] _arr;
			_arr = tmp;
			iterator res = _arr[countToFirst - 1];
			return res;
		}
		iterator& rbegin() {
			iterator curr = begin();
			T* tmp = new T[_logicalSize];
			int j = _logicalSize;
			for (int i = 0; i < _logicalSize; i++) {
				tmp[i] = _arr[j];
				j--;
			}
			delete[] _arr;
			_arr = tmp;
			return begin();
		}
		iterator& rend() {
			iterator curr = end();
			T* tmp = new T[_logicalSize];
			int j = _logicalSize;
			for (int i = 0; i < _logicalSize; i++) {
				tmp[i] = _arr[j];
				j--;
			}
			delete[] _arr;
			_arr = tmp;
			return end();
		}
		void print() const {
			for (int i = 0; i < _logicalSize; i++)
				cout << _arr[i] << " ";
			cout << endl;
		}
		T& at(int i) const {
			if (i > _logicalSize || i < 0) {
				cout << "out of bound!";
			}
			else {
				return _arr[i];
			}
		}
		void swap(T* A, T* B) {
			T* temp = A;
			A  = B;
			B = temp;
		}
		void insertionSort(int arr[], int size)
		{
			int index1, key, index2;
			for (index1 = 1; index1 < size; index1++)
			{
				key = arr[index1];
				index2 = index1 - 1;
				while (index2 >= 0 && arr[index2] > key)
				{
					arr[index2 + 1] = arr[index2];
					index2 = index2 - 1;
				}
				arr[index2 + 1] = key;
			}
		}
		void ourSort() {
			Quicksort(this->_arr, this->size());
		}
		void Quicksort(T* const arr, const int size)
		{
			if (size <= 1)
			{
				return;
			}
			else if (size == 2)
			{
				if (arr[0]>arr[1])
				{
					swap(&arr[0], &arr[1]);
				}
				return;
			}
			int posArr[3] = { 0, (size / 2) - 1, size - 1 };
			this->insertionSort(posArr, 3);
			const int pivot = size - 1;
			swap(&arr[posArr[1]], &arr[pivot]);
			int indexA = 0;
			int indexB = pivot - 1;
			while (true)
			{
				const int prevIndexA = indexA;
				const int prevIndexB = indexB;
				indexA = -1;
				indexB = -1;

				for (int i = prevIndexA; i < pivot; i++)
				{
					if (arr[i]>arr[pivot])
					{
						indexA = i;
						break;
					}
				}
				for (int i = prevIndexB; i > indexA; i--)
				{
					if (!(arr[i] > arr[pivot]))
					{
						indexB = i;
						break;
					}
				}
				if (indexA == -1 and indexB == -1)
				{
					return;
				}
				else if (indexA == -1)
				{
					indexA = size - 1;
					indexB = size;
					break;
				}
				else if (indexB == -1)
				{
					indexB = indexA + 1;
					break;
				}
				else
				{
					swap(&arr[indexA], &arr[indexB]);
					indexA++;
					indexB--;
				}
			}
			if (indexA != pivot)
			{
				swap(&arr[indexA], &arr[pivot]);
			}
			Quicksort(arr, indexA);
			Quicksort(arr + indexA + 1, size - indexB);
		}
	private:
		void resize() {
			_physicalSize *= 2;
			T* temp = new T[_physicalSize];
			for (int i = 0; i < _logicalSize; i++)
				temp[i] = _arr[i];

			delete[] _arr;
			_arr = temp;
		}

		T* _arr;
		int _logicalSize;
		int _physicalSize;
	};
}



