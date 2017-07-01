//#include "iostream"
//#include "assert.h"
//#include "algorithm"
//#include "string"
//using namespace std;
//
//template<typename T>
//class myvector {
//public:
//	myvector() :array(0), size(0), capacity(0) {}
//	myvector( int n, const T& t) :array(0), size(0), capacity(0) {
//		while (n--) {
//			push_back(t);
//		}
//	}
//	myvector(const myvector<T>& other) {
//		size = other.size;
//		capacity = other.capacity;
//		array = new T[capacity];
//		for (int i = 0; i < size; ++i) {
//			array[i] = other.array[i];
//		}
//	}
//	myvector<T>& operator=(myvector<T>& other) {
//		if (this == other)
//			return *this;
//		clear();
//		size = other.size;
//		capacity = other.capacity;
//		array = new T[capacity];
//		for (int i = 0; i < size; ++i) {
//			array[i] = other[i];
//		}
//		return *this;
//	}
//	int getsize() {
//		return size;
//	}
//	int getcapacity() {
//		return capacity;
//	}
//	bool empty() {
//		return size == 0;
//	}
//	void clear() {
//		deallocator(array);
//		array = 0;
//		size = 0;
//		capacity = 0;
//	}
//	
//	void push_front(const T& t) {
//		insert(0, t);
//	}
//	void push_back(const T& t) {
//		insert(size, t);
//	}
//	void insert(int pos, const T& t) {
//		if (size == capacity) {  //这就有问题了
//			T* oldarr = array;
//			if (capacity == 0) {
//				capacity = 1;
//			}
//			else {
//				capacity *= 2;
//			}
//			array = allocator(capacity);
//			for (int i = 0; i < pos; ++i) {
//				array[i] = oldarr[i];
//			}
//			for (int i = pos + 1; i <= size; ++i) {
//				array[i] = oldarr[i - 1];
//			}
//			delete oldarr;
//			oldarr = NULL;
//			array[pos] = t;
//			
//		}
//		else {  //capacity还够
//			for (int i = size; i > pos; --i) {
//				array[i] = array[i - 1];
//			}
//			array[pos] = t;
//		}
//		size++;
//	}
//	void erase(int pos) {
//		if (pos < size) {
//			--size;
//			for (int i = pos; i < size; ++i) {
//				array[i] = array[i + 1];
//			}
//		}
//	}
//	void printvec() {
//		for (int i = 0; i < size; ++i) {
//			cout << array[i] << " ";
//		}
//		cout << endl;
//	}
//
//private:
//	T* allocator(int size) {
//		return new T[size];
//	}
//	void deallocator(T* arr) {
//		if (arr) {
//			delete[] arr;
//		}
//	}
//private:
//	T* array;
//	int size;
//	int capacity;
//};
//
//
//int main() {
//	myvector<int> v;
//	v.push_front(1);
//	v.push_front(2);
//	v.push_front(3);
//	cout << v.getsize() << endl;
//	cout << v.getcapacity() << endl;
//	v.printvec();
//	myvector<int> v2;
//	v2.push_front(3);
//	v2.push_front(4);
//	cout << v2.getsize() << endl;
//	cout << v2.getcapacity() << endl;
//	myvector<int> v1(10, 1);
//	cout << v1.getsize() << endl;
//	cout << v1.getcapacity() << endl;
//	v1.printvec();
//	
//}
