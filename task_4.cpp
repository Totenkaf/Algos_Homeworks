// Copyright 2021 by Artem Ustsov

// Задача №4_3
/*
* В операционной системе Technux есть планировщик процессов.
* Каждый процесс характеризуется:
* приоритетом P (process_priority)
* временем, которое он уже отработал t (process_current_time)
* временем, которое необходимо для завершения работы процесса T
(process_time_to_complete).

* Планировщик процессов выбирает процесс с минимальным значением P * (t + 1),
выполняет его время P и кладет обратно в очередь процессов.
* Если выполняется условие t >= T, то процесс считается завершенным и удаляется
из очереди.
* Требуется посчитать кол-во переключений процессора.
* Формат входных данных:  Сначала вводится кол-во процессов. После этого
процессы в формате P T
* Формат выходных данных: Кол-во переключений процессора.
*
* Требования:
* В качестве очереди с приоритетом нужно использовать кучу.
* Куча должна быть реализована в виде шаблонного класса.
* Решение должно поддерживать передачу функции сравнения снаружи.
* Куча должна быть динамической.
*/

#include <iostream>
#include <vector>

class Process {
public:
  int priority, time_to_complete, current_time;

  Process(int priority, int time_to_complete)
      : priority(priority), time_to_complete(time_to_complete),
        current_time(0){};
};

class ProcessComparator {
public:
  bool operator()(const Process &process_1, const Process &process_2) {
    int time_process_1 = process_1.priority * (process_1.current_time + 1);
    int time_process_2 = process_2.priority * (process_2.current_time + 1);
    return time_process_1 < time_process_2;
  }
};

template <typename T, typename Comparator> class Heap {
public:
  explicit Heap(const std::vector<T> _values_vector, Comparator _cmp);
  T extractMin();
  T getMin();

  void insert(T element);
  void heapSort(Comparator cmp);
  void hepify();
  bool isEmpty();
  int getSize();

private:
  void siftDown(int n, int index, Comparator cmp);
  void siftUp(int index);
  std::vector<T> values_vector;
  Comparator cmp;
};

template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(const std::vector<T> _values_vector,
                          Comparator _cmp) {
  values_vector = _values_vector;
  cmp = _cmp;
  hepify();
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::insert(T element) {
  values_vector.push_back(element);
  siftUp(values_vector.size() - 1);
  return;
}

template <typename T, typename Comparator> T Heap<T, Comparator>::extractMin() {
  T result = values_vector.front();
  values_vector.front() = values_vector.back();
  values_vector.pop_back();
  if (!values_vector.empty()) {
    siftDown(values_vector.size(), 0, cmp);
  }
  return result;
}

template <typename T, typename Comparator> T Heap<T, Comparator>::getMin() {
  return values_vector.front();
}

// optional
template <typename T, typename Comparator>
void Heap<T, Comparator>::heapSort(Comparator cmp) {
  int heapSize = values_vector.size();
  hepify();
  while (heapSize > 1) {
    std::swap(values_vector.front(), values_vector[heapSize - 1]);
    heapSize--;
    siftDown(heapSize, 0, cmp);
  }
  return;
}

template <typename T, typename Comparator> void Heap<T, Comparator>::hepify() {
  for (int i = values_vector.size() / 2; i >= 0; --i) {
    siftDown(values_vector.size(), i, cmp);
  }
  return;
}

template <typename T, typename Comparator> bool Heap<T, Comparator>::isEmpty() {
  return values_vector.size() == 0;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::siftDown(int n, int index, Comparator cmp) {
  int left = index * 2 + 1;
  int right = index * 2 + 2;
  int large = index;

  if (left < n && cmp(values_vector[left], values_vector[index])) {
    large = left;
  }
  if (right < n && cmp(values_vector[right], values_vector[large])) {
    large = right;
  }
  if (large != index) {
    std::swap(values_vector[index], values_vector[large]);
    siftDown(n, large, cmp);
  }
  return;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::siftUp(int index) {
  while (index > 0) {
    int parent = (index - 1) / 2;
    if (!cmp(values_vector[index], values_vector[parent])) {
      return;
    }
    std::swap(values_vector[index], values_vector[parent]);
    index = parent;
  }
  return;
}

int countProcessorSwitches(Heap<Process, ProcessComparator> heap) {
  int switches = 0;
  while (!heap.isEmpty()) {
    //Процесс с минимальным показателем
    Process runningProcess = heap.extractMin();
    //Если на данном этапе процесс не выполняется, то
    if (runningProcess.current_time + runningProcess.priority <
        runningProcess.time_to_complete) {
      //выполняем его
      runningProcess.current_time += runningProcess.priority;
      //а затем возвраащем в кучу
      heap.insert(runningProcess);
    }
    // увеличиваем количество переключений
    switches++;
  }
  return switches;
}

template <typename T>
void valuesVectorFill(int processes_num, std::vector<T> &values_vector) {
  for (int i = 0; i < processes_num; ++i) {
    int priority = 0;
    int time_to_complete = 0;
    std::cin >> priority >> time_to_complete;
    values_vector.emplace_back(priority, time_to_complete);
  }
  return;
}

int main() {
  int processes_num;
  std::cin >> processes_num;

  std::vector<Process> values_vector;
  valuesVectorFill<Process>(processes_num, values_vector);

  Heap<Process, ProcessComparator> heap(values_vector, ProcessComparator());
  std::cout << countProcessorSwitches(heap) << std::endl;
  return 0;
}
