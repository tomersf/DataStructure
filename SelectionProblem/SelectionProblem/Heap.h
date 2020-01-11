
class Person;

class Heap
{
	Person** Arr;
	int maxSize, heapSize;
	static int Left(int node);
	static int Right(int node);
	static int Parent(int node);
	void FixHeap(int node);
public:
	Heap(int max);
	Heap(Person** Arr, int size);
	~Heap();
	Person& Min() const;
	Person& DeleteMin();
	void Insert(Person& Person);
	
};