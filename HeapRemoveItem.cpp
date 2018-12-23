#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//First write a method to read the input data into an array representing a heap.  The input data is the Test case input.  Return the //size of the heap.  A pointer to the heap array is a parameter of readheap.
int readheap(int * theheap)
{
	int size = 0;
	//use cin to read in the data
	int i = 0;
	while (cin >> theheap[i]) {
		i++;
		size++;
	}

	return size;

}

//write a method to remove an item from the heap. 
int heapRemove(int * theheap, int size)
{

	//replace root with last item in the array
	theheap[0] = theheap[size - 1];
	theheap[size - 1] = NULL;
	size--;

	//sift down new root value
	int currIndex = 0;
	int * currNode = &theheap[currIndex];
	bool done = false;
	while (!done) {
		int leftChildIndex = currIndex * 2 + 1;
		int rightChildIndex = currIndex * 2 + 2;

		if (rightChildIndex >= size) {
			//no children
			if (leftChildIndex >= size) {
				done = true;
			}
			//one child (left)
			else {
				// if currNode < child, swap currNode value with child value
				if (*currNode > theheap[leftChildIndex]) {
					// point currNode to the child
					// update index
					int tmp = *currNode;
					*currNode = theheap[leftChildIndex];
					theheap[leftChildIndex] = tmp;

					currNode = &theheap[leftChildIndex];
					currIndex = leftChildIndex;
				}
			}
		}
		//two children (rightChildIndex < size && leftChildIndex < size)
		else {
			int smallestChildIndex;
			if (theheap[leftChildIndex] > theheap[rightChildIndex]) {
				smallestChildIndex = rightChildIndex;
			}
			else {
				smallestChildIndex = leftChildIndex;
			}
			if (*currNode > theheap[smallestChildIndex]) {
				int tmp = *currNode;
				*currNode = theheap[smallestChildIndex];
				theheap[smallestChildIndex] = tmp;

				currNode = &theheap[smallestChildIndex];
				currIndex = smallestChildIndex;
			}
			// find the smallest child. if currNode < smallest child, swap currNode value with child value
			// point currNode to the child
			// update index
		}
	}
	return size;
}

//write a method to print the heap.  Print the data as shown in the Test case output.
void heapPrint(int * theheap, int size)
{
	for (int i = 0; i < size; i++) {
		cout << theheap[i] << " ";
	}
}

int main()
{
	int * theheap = new int[10];
	int size = readheap(theheap);
	size = heapRemove(theheap, size);
	heapPrint(theheap, size);
}