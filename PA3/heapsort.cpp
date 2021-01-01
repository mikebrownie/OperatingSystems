#include "heapsort.hpp"

using namespace std;

Heapsort::Heapsort(int cap)
{
    currentSize = 0;
    capacity = cap;
    heap = new int[capacity]; //dynamically instantiating an array
}

Heapsort::~Heapsort() //do i need this
{
    delete[] heap; //freeing memory used by heap
}

void Heapsort::insert(int value)
{
    if (currentSize < capacity)
    {
        //append new element to end of array
        heap[currentSize] = value;
        currentSize++;
        minHeapify(currentSize);
    }
    else
    {
        cout <<"full" << endl;
    }

    //printArray();
}

void Heapsort::printArray()
{
    for (int i = 0; i < currentSize; i++)
    {
        cout << heap[i] << endl;
    }

}
void Heapsort::search(int data) //just gonna make a search array function
{
    for (int i = 0; i < capacity; i++)
    {
        if (heap[i] == data)
        {
            cout << "Data found" << endl;
        }
    }
}

// recursive method to heapify a subtree with the root at given index
void Heapsort::minHeapify(int index) // currentSize is size of heap
{
    int smallest = index;
    int l = leftChild(index);
    int r = rightChild(index);
    //if left child is smaller than root
    if (l < currentSize && heap[l] < heap[smallest])
    {
        smallest = l;
    }
    //if right child is smaller than smallest so far
    if (r < currentSize && heap[r] < heap[smallest])
    {
        smallest = r;
    }
    //if smallest is not root
    if (smallest != index)
    {
        swap(&heap[index], &heap[smallest]);

        //recursively heapify the affected sub-tree
        minHeapify(smallest);
    }
}
//function that swaps two elements
void Heapsort::swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}


int main() {
  Heapsort myHeap(10000);
  cout<< "Inserting 10 elements"<<endl;
  for (int i = 0; i < 10000; i++){
    myHeap.insert(-i);
  }
  cout<< "Heap:"<<endl;
  // myHeap.printArray();

}
