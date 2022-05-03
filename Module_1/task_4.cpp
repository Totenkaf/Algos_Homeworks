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

// #include <iostream>
// #include <vector>

// class Process {
// public:
//   int priority, time_to_complete, current_time;

//   Process(int priority, int time_to_complete)
//       : priority(priority), time_to_complete(time_to_complete),
//         current_time(0){};
// };

// class ProcessComparator {
// public:
//   bool operator()(const Process &process_1, const Process &process_2) {
//     int time_process_1 = process_1.priority * (process_1.current_time + 1);
//     int time_process_2 = process_2.priority * (process_2.current_time + 1);
//     return time_process_1 < time_process_2;
//   }
// };

// template <typename T, typename Comparator> class Heap {
// public:
//   explicit Heap(const std::vector<T> _values_vector, Comparator _cmp);
//   T extract_minMin();
//   T getMin();

//   void insert(T element);
//   void heapSort(Comparator cmp);
//   void hepify();
//   bool isEmpty();
//   int getSize();

// private:
//   void siftDown(int n, int index, Comparator cmp);
//   void siftUp(int index);
//   std::vector<T> values_vector;
//   Comparator cmp;
// };

// template <typename T, typename Comparator>
// Heap<T, Comparator>::Heap(const std::vector<T> _values_vector,
//                           Comparator _cmp) {
//   values_vector = _values_vector;
//   cmp = _cmp;
//   hepify();
// }

// template <typename T, typename Comparator>
// void Heap<T, Comparator>::insert(T element) {
//   values_vector.push_back(element);
//   siftUp(values_vector.size() - 1);
//   return;
// }

// template <typename T, typename Comparator> T Heap<T,
// Comparator>::extract_minMin() {
//   T result = values_vector.front();
//   values_vector.front() = values_vector.back();
//   values_vector.pop_back();
//   if (!values_vector.empty()) {
//     siftDown(values_vector.size(), 0, cmp);
//   }
//   return result;
// }

// template <typename T, typename Comparator> T Heap<T, Comparator>::getMin() {
//   return values_vector.front();
// }

// // optional
// template <typename T, typename Comparator>
// void Heap<T, Comparator>::heapSort(Comparator cmp) {
//   int heapSize = values_vector.size();
//   hepify();
//   while (heapSize > 1) {
//     std::swap(values_vector.front(), values_vector[heapSize - 1]);
//     heapSize--;
//     siftDown(heapSize, 0, cmp);
//   }
//   return;
// }

// template <typename T, typename Comparator> void Heap<T, Comparator>::hepify()
// {
//   for (int i = values_vector.size() / 2; i >= 0; --i) {
//     siftDown(values_vector.size(), i, cmp);
//   }
//   return;
// }

// template <typename T, typename Comparator> bool Heap<T,
// Comparator>::isEmpty() {
//   return values_vector.size() == 0;
// }

// template <typename T, typename Comparator>
// void Heap<T, Comparator>::siftDown(int n, int index, Comparator cmp) {
//   int left = index * 2 + 1;
//   int right = index * 2 + 2;
//   int large = index;

//   if (left < n && cmp(values_vector[left], values_vector[index])) {
//     large = left;
//   }
//   if (right < n && cmp(values_vector[right], values_vector[large])) {
//     large = right;
//   }
//   if (large != index) {
//     std::swap(values_vector[index], values_vector[large]);
//     siftDown(n, large, cmp);
//   }
//   return;
// }

// template <typename T, typename Comparator>
// void Heap<T, Comparator>::siftUp(int index) {
//   while (index > 0) {
//     int parent = (index - 1) / 2;
//     if (!cmp(values_vector[index], values_vector[parent])) {
//       return;
//     }
//     std::swap(values_vector[index], values_vector[parent]);
//     index = parent;
//   }
//   return;
// }

// int countProcessorSwitches(Heap<Process, ProcessComparator> heap) {
//   int switches = 0;
//   while (!heap.isEmpty()) {
//     //Процесс с минимальным показателем
//     Process runningProcess = heap.extract_minMin();
//     //Если на данном этапе процесс не выполняется, то
//     if (runningProcess.current_time + runningProcess.priority <
//         runningProcess.time_to_complete) {
//       //выполняем его
//       runningProcess.current_time += runningProcess.priority;
//       //а затем возвраащем в кучу
//       heap.insert(runningProcess);
//     }
//     // увеличиваем количество переключений
//     switches++;
//   }
//   return switches;
// }

// template <typename T>
// void valuesVectorFill(int processes_num, std::vector<T> &values_vector) {
//   for (int i = 0; i < processes_num; ++i) {
//     int priority = 0;
//     int time_to_complete = 0;
//     std::cin >> priority >> time_to_complete;
//     values_vector.emplace_back(priority, time_to_complete);
//   }
//   return;
// }

// int main() {
//   int processes_num;
//   std::cin >> processes_num;

//   std::vector<Process> values_vector;
//   valuesVectorFill<Process>(processes_num, values_vector);

//   Heap<Process, ProcessComparator> heap(values_vector, ProcessComparator());
//   std::cout << countProcessorSwitches(heap) << std::endl;
//   return 0;
// }

// Copyright 2022 by Artem Ustsov

// Задача №4_1

/* Напишите программу, которая использует кучу для слияния K отсортированных
массивов суммарной длиной N.
*
* Требования: время работы O(N * logK). Ограничение на размер кучи O(K)..
* Формат входных данных: Сначала вводится количество массивов K.
* Затем по очереди размер каждого массива и элементы массива. Каждый массив
упорядочен по возрастанию.
* Формат выходных данных: Итоговый отсортированный массив.

* Решение всех задач данного раздела предполагает использование кучи,
реализованной в виде шаблонного класса.
* Решение должно поддерживать передачу функции сравнения снаружи.
* Куча должна быть динамической.
*/

#include <cmath>
#include <iostream>
#include <vector>

struct Element {
  int key;
  size_t current_index;

  Element() = default;
  Element(const int &k, const size_t &index) : key(k), current_index(index) {}
  ~Element() = default;
};

template <typename T> class ComparatorDefault {
public:
  bool operator()(const T &lhs, const T &rhs) { 
      return lhs < rhs;
  }
};

template <typename K, typename V>
struct Pair {
  K first;
  V second;
  Pair() = default;
  Pair(K key, V value) : first(key), second(value) {}
  ~Pair() = default;
};

bool operator<(const Element &lhs, const Element &rhs) {
  return lhs.key < rhs.key;
}

template <typename T, typename Comparator> class Heap {
public:
  Heap(const Comparator &cmp_ = ComparatorDefault<T>()) 
  : size(0), capacity(0), array(nullptr), cmp(cmp_) {};

  Heap(const size_t& heap_size, const size_t& heap_capacity, const T& heap, 
       const Comparator &cmp_ = ComparatorDefault<T>()) = delete;

  ~Heap() { 
    delete[] array; 
  }

  void insert(const T &element);
  T extract_min();

private:
  void sift_down(size_t index);
  void sift_up(size_t index);

  size_t size;
  size_t capacity;
  T* array;
  Comparator cmp;
};

template <typename T, typename Comparator>
void Heap<T, Comparator>::sift_down(size_t current_ind) {
  size_t left_ind = 2 * current_ind + 1;
  size_t right_ind = 2 * current_ind + 2;

  while (current_ind < size / 2 &&
         (cmp(array[left_ind], array[current_ind]) ||
          (right_ind < size &&
           cmp(array[right_ind], array[current_ind])))) {
    if (right_ind >= size || cmp(array[left_ind], array[right_ind])) {
      std::swap(array[left_ind], array[current_ind]);
      current_ind = left_ind;
    } else {
      std::swap(array[right_ind], array[current_ind]);
      current_ind = right_ind;
    }
    left_ind = 2 * current_ind + 1;
    right_ind = 2 * current_ind + 2;
  }

  return;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::sift_up(size_t current_ind) {
  size_t parent_ind = current_ind == 0 ? 0 : (current_ind - 1) / 2;

  while (current_ind != 0 && cmp(array[current_ind], array[parent_ind])) {
    std::swap(array[parent_ind], array[current_ind]);
    current_ind = parent_ind;
    parent_ind = current_ind == 0 ? 0 : (current_ind - 1) / 2;
  }

  return;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::insert(const T &element) {
  if (capacity == 0) {
      capacity = 1;
      array = new T[capacity];
  } else if (size == capacity) {
      capacity *= 2;
      T* newArray = new T[capacity];
      std::copy(array, array + size, newArray);
      delete[] array;
      array = newArray;
    }
  array[size] = element;
  ++size;

  sift_up(size - 1);
  return;
}

template <typename T, typename Comparator>
T Heap<T, Comparator>::extract_min() {
    if (size == 0) {
        throw std::invalid_argument("min heap is empty");
    }
    std::swap(array[0], array[size - 1]);
    T result = array[size - 1];
    --size;
    sift_down(0);
    return result;
}

Pair<int *, size_t> k_way_merge(const size_t k, const size_t *array_size,
                                int **array) {
  size_t size = 0;
  for (size_t i = 0; i < k; ++i) {
    size += array_size[i];
  }
  int *result = new int[size];

  Heap<Element, ComparatorDefault<Element>> heap;
  for (size_t i = 0; i < k; ++i) {
    if (array_size[i] > 0) {
      heap.insert(Element(array[i][0], i));
    }
  }

  auto *counter = new size_t[k];
  for (size_t i = 0; i < k; ++i) {
    counter[i] = 1;
  }

  for (size_t i = 0; i < size; ++i) {
    auto minElement = heap.extract_min();
    int element = minElement.key;
    size_t arrayInd = minElement.current_index;
    result[i] = element;
    if (counter[arrayInd] < array_size[arrayInd]) {
      heap.insert(Element(array[arrayInd][counter[arrayInd]], arrayInd));
      ++counter[arrayInd];
    }
  }
  delete[] counter;
  return {result, size};
}

int main() {
  size_t num_of_k_arrays = 0;
  std::cin >> num_of_k_arrays;

  int **array_of_k_arrays = new int *[num_of_k_arrays];
  auto *array_of_k_arrays_size = new size_t[num_of_k_arrays];

  for (size_t i = 0; i < num_of_k_arrays; ++i) {
    std::cin >> array_of_k_arrays_size[i];
    array_of_k_arrays[i] = new int[array_of_k_arrays_size[i]];
    for (size_t j = 0; j < array_of_k_arrays_size[i]; ++j) {
      std::cin >> array_of_k_arrays[i][j];
    }
  }

  auto result = k_way_merge(num_of_k_arrays, array_of_k_arrays_size, array_of_k_arrays);

  for (size_t i = 0; i < result.second; ++i) {
    std::cout << result.first[i] << " ";
  }

  for (size_t i = 0; i < num_of_k_arrays; ++i) {
    delete[] array_of_k_arrays[i];
  }

  delete[] array_of_k_arrays;
  delete[] array_of_k_arrays_size;
  delete[] result.first;
  return 0;
}
