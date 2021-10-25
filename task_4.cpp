// Задача №4_3

/*
* В операционной системе Technux есть планировщик процессов. 
* Каждый процесс характеризуется:
* приоритетом P
* временем, которое он уже отработал t
* временем, которое необходимо для завершения работы процесса T.

* Планировщик процессов выбирает процесс с минимальным значением P * (t + 1), выполняет его время P и кладет обратно в очередь процессов.
* Если выполняется условие t >= T, то процесс считается завершенным и удаляется из очереди.
* Требуется посчитать кол-во переключений процессора.
* Формат входных данных:  Сначала вводится кол-во процессов. После этого процессы в формате P T
* Формат выходных данных: Кол-во переключений процессора.
*/

#include <iostream>

// Подсчет минимально необходимого количества тупиков
int CountDeadlocks(int n);

class Heap
{
public:
    Heap(int cap = 10);
    ~Heap();
    
    int ExtractMin();
    void Insert(int element);
    int PeekAtNext() { return IsEmpty() ? 0 : buffer[0]; }
    
    bool IsEmpty() { return size == 0; }
    int GetSize() { return size; }
    
private:
        
    void SiftDown(int index);
    void SiftUp(int index);
        
    void Reallocate();
    
    int* buffer;
    int size;
    int capacity;
    const int capacityFactor = 2;
};

Heap::Heap(int cap) 
: capacity(cap), size(0) 
{
    buffer = new int[capacity];
}

Heap::~Heap()
{
    delete[] buffer;
}

void Heap::SiftDown(int index)
{
    int leftSon = 2 * index + 1;
    int rightSon = 2 * index + 2;
    int smallestSon = index;
    
    if (leftSon < size && buffer[leftSon] < buffer[index])
        smallestSon = leftSon;
    
    if (rightSon < size && buffer[rightSon] < buffer[smallestSon])
        smallestSon = rightSon;
    
    if (smallestSon != index) {
        std::swap(buffer[index], buffer[smallestSon]);
        SiftDown(smallestSon);
    }    
}

void Heap::SiftUp(int index)
{
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (buffer[index] >= buffer[parent]) { return; }
        std::swap(buffer[index], buffer[parent]);
        index = parent;
    }
}

void Heap::Reallocate()
{
    int new_capacity = capacity * capacityFactor;
    int* new_buffer = new int[new_capacity];
    
    for (int i = 0; i < capacity; ++i) {
        new_buffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = new_buffer;
    capacity = new_capacity;
}

void Heap::Insert(int element)
{
    buffer[size] = element;
    SiftUp(size++);
    if (size == capacity) {
        Reallocate();
    }  
}

int Heap::ExtractMin()
{
    if (IsEmpty())
        return 0;
    int result = buffer[0];
    buffer[0] = buffer[size-1];
    size--;
    SiftDown(0);
    return result;
}

// Подсчет минимально необходимого количества тупиков
int CountDeadlocks(int n)
{
    int minDeadlocks = 0;
    int arrival = 0, departure = 0;
    Heap heap;
    
    for (int i = 0; i < n; ++i) {
        // Ввод времени прибытия / отбытия
        std::cin >> arrival >> departure;
        if (!heap.IsEmpty()) {
            // Если некоторые электрички к моменту прибытия уехали - извлекаем
            while (arrival > heap.PeekAtNext()) {
                heap.ExtractMin();
            }
        }
        // Добавляем время отправления прибывшей
        heap.Insert(departure);

        // Смотрим, сколько путей занято
        if (heap.GetSize() > minDeadlocks) {
            minDeadlocks = heap.GetSize();
        }
    }
    return minDeadlocks;
}

int main() {
    int n = 0;
    std::cin >> n;
    int minDeadlocks = CountDeadlocks(n);
    std::cout << minDeadlocks;
    return 0;
}