#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iostream>
using namespace std;

template <class T>
struct __list_node {
	typedef void* void_pointer; 
	void_pointer prev; //型别为void*,其实可设为__list_node<T>*
	void_pointer next;
	T data;
};

template <class T, class Alloc>  

int main() {
	
	return 0;
}
