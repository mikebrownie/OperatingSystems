#include <iostream>

class Heapsort
{
    private:
    int *heap; //ptr to array of data in heap
    int capacity; // max possible size of min heap
    int currentSize; //current # of elements in min heap

    void minHeapify(int index); // recursive method to fix heap used with pop();
    int parent(int index) {return (index-1)/2;}
    int leftChild(int index) {return 2*index+1;}
    int rightChild(int index) {return 2*index+2;}
    void swap(int *x, int *y); // swaps two values in an array


    public:
    Heapsort(int cap); //constructor
    ~Heapsort();
    void insert(int value);
    void search(int data);
    void printArray();

};
