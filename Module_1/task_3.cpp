// Copyright 2021 by Artem Ustsov

// Задача № 3_1
// Реализовать очередь с динамически зацикленным буфером

// Во всех задачах из следующего списка следует написать структуру данных,
// обрабатывающую команды push* и pop*. Формат входных данных. В первой строке
// количество команд n. n ≤ 1000000. Каждая команда задаётся как 2 целых числа:
// a b. a = 1 - push front a = 2 - pop front a = 3 - push back a = 4 - pop back
// Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.

// Для очереди используются команды 2 и 3. Для дека используются все четыре
// команды.

// Если дана команда pop*, то число b - ожидаемое значение. Если команда pop
// вызвана для пустой структуры данных, то ожидается “-1”. Формат выходных
// данных. Требуется напечатать YES - если все ожидаемые значения совпали.
// Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

// Требования: Очередь должна быть реализована в виде класса.

// #include <iostream>

// class Queue {
// public:
//   Queue() : dataQueue(nullptr), dequeue_sizeQueue(0), head_dequeueQueue(0), tail_dequeueQueue(0) {
//     grow_dequeueQueue();
//   }

//   ~Queue() {
//     if (dataQueue != nullptr) {
//       delete[] dataQueue;
//     }
//   }

//   // удаляет первый элемент и возвращает его
//   int pop() {
//     if (head_dequeueQueue != tail_dequeueQueue) {
//       // очередь не пуста
//       int value = dataQueue[head_dequeueQueue];
//       if (head_dequeueQueue == dequeue_sizeQueue - 1) {
//         head_dequeueQueue = 0;
//       } else {
//         head_dequeueQueue++;
//       }
//       return value;
//     }
//     return -1;
//   }

//   // добавляет новый элемент в конец
//   void push(int value) {
//     if ((tail_dequeueQueue + 1) % dequeue_sizeQueue == head_dequeueQueue) {
//       grow_dequeueQueue();
//       push(value);
//     } else {
//       // добавляем следующий элемент
//       dataQueue[(tail_dequeueQueue) % dequeue_sizeQueue] = value;
//       tail_dequeueQueue = (tail_dequeueQueue + 1) % dequeue_sizeQueue;
//     }
//   }
//   bool isis_empty() { return head_dequeueQueue == tail_dequeueQueue; }

// private:
//   int *dataQueue;
//   int dequeue_sizeQueue;
//   int head_dequeueQueue;
//   int tail_dequeueQueue;

//   const int dequeue_capacityQueue = 10;
//   const int dequeue_sizeFactor = 2;

//   void grow_dequeueQueue() {
//     int newdequeue_sizeQueue = (dequeue_sizeQueue > 0) ? dequeue_sizeQueue * dequeue_sizeFactor : dequeue_capacityQueue,
//         *newdataQueue = new int[newdequeue_sizeQueue];

//     if (head_dequeueQueue != tail_dequeueQueue) {
//       int j = 0;
//       for (int i = head_dequeueQueue; i < dequeue_sizeQueue; ++i) {
//         if (i == tail_dequeueQueue) {
//           break;
//         }
//         newdataQueue[j++] = dataQueue[i];
//         if (i == dequeue_sizeQueue - 1) {
//           i = -1;
//         }
//       }
//       head_dequeueQueue = 0;
//       tail_dequeueQueue = j;
//     }
//     if (dataQueue != NULL) {
//       delete[] dataQueue;
//     }
//     dataQueue = newdataQueue;
//     dequeue_sizeQueue = newdequeue_sizeQueue;
//   }
// };

// int main() {
//   Queue queue;
//   int numberOfCommands = 0;
//   std::cin >> numberOfCommands;

//   int queueCommandNumber = 0, commandValue = 0;

//   bool queueStatus = true;

//   for (int i = 0; i < numberOfCommands; ++i) {
//     std::cin >> queueCommandNumber >> commandValue;
//     if (!queueStatus) {
//       continue;
//     }
//     switch (queueCommandNumber) {
//     case 2:
//       if (queue.is_empty()) {
//         commandValue = -1;
//       }
//       queueStatus = (queue.pop() == commandValue) && queueStatus;
//       break;
//     case 3:
//       queue.push(commandValue);
//       break;
//     }
//   }
//   std::cout << (queueStatus ? "YES" : "NO");
//   return 0;
// }


// Copyright 2022 by Artem Ustsov

// Задача № 3_2
// Реализовать дэк с динамически зацикленным буфером

// Во всех задачах из следующего списка следует написать структуру данных,
// обрабатывающую команды push* и pop*. Формат входных данных. В первой строке
// количество команд n. n ≤ 1000000. Каждая команда задаётся как 2 целых числа:
// a b. a = 1 - push front a = 2 - pop front a = 3 - push back a = 4 - pop back
// Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.

// Для дека используются все четыре
// команды.

// Если дана команда pop*, то число b - ожидаемое значение. Если команда pop
// вызвана для пустой структуры данных, то ожидается “-1”. Формат выходных
// данных. Требуется напечатать YES - если все ожидаемые значения совпали.
// Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

// Требования: Дэк должен быть реализован в виде класса.


#include <iostream>
#include <sstream>

#define SIZE_INITIAL 1
#define SIZE_FACTOR 2

template <typename T> class Dequeue {
public:
  Dequeue();
  ~Dequeue();

  void push_front(const T value);
  void push_back(const T value);
  T pop_front();
  T pop_back();

  bool is_empty() const;

private:
  void grow_dequeue();

  T *data_dequeue;
  size_t dequeue_size;
  int dequeue_capacity;
  int head_dequeue;
  int tail_dequeue;
};

template <typename T>
Dequeue<T>::Dequeue()
    : dequeue_capacity(SIZE_INITIAL), dequeue_size(0), head_dequeue(0),
      tail_dequeue(0) {
  data_dequeue = new T[SIZE_INITIAL];
}

template <typename T> Dequeue<T>::~Dequeue() { delete[] data_dequeue; }

template <typename T> void Dequeue<T>::push_front(const T value) {
  if (dequeue_size + 1 > dequeue_capacity) {
    grow_dequeue();
  }
  head_dequeue = head_dequeue - 1 >= 0
                     ? head_dequeue - 1
                     : dequeue_capacity -
                           1; /* если head_dequeue = 0 перекидываем в конец*/
  data_dequeue[head_dequeue] = value;
  ++dequeue_size;

  if (dequeue_size == 1) {
    tail_dequeue = head_dequeue;
  }
}

template <typename T> void Dequeue<T>::push_back(const T value) {
  if (dequeue_size + 1 > dequeue_capacity) {
    grow_dequeue();
  }
  tail_dequeue = (tail_dequeue + 1) % dequeue_capacity;
  data_dequeue[tail_dequeue] = value;
  ++dequeue_size;

  if (dequeue_size == 1) {
    head_dequeue = tail_dequeue;
  }
}
template <typename T> T Dequeue<T>::pop_front() {
  if (is_empty()) {
    return -1;
  }
  T res = data_dequeue[head_dequeue];
  head_dequeue = (head_dequeue + 1) % dequeue_capacity;
  --dequeue_size;

  return res;
}

template <typename T> T Dequeue<T>::pop_back() {
  if (is_empty()) {
    return -1;
  }
  T res = data_dequeue[tail_dequeue];
  tail_dequeue = tail_dequeue - 1 >= 0
                     ? tail_dequeue - 1
                     : dequeue_capacity -
                           1; /* если tail_dequeue = 0 - перекидываем в начало*/
  --dequeue_size;

  return res;
}
template <typename T> void Dequeue<T>::grow_dequeue() {
  T *new_data_dequeue = new T[dequeue_capacity * SIZE_FACTOR];

  for (size_t i = 0; i < dequeue_size; ++i) {
    new_data_dequeue[i] = data_dequeue[head_dequeue];
    head_dequeue = (head_dequeue + 1) % dequeue_capacity;
  }

  delete[] data_dequeue;
  data_dequeue = new_data_dequeue;
  dequeue_capacity *= SIZE_FACTOR;
  head_dequeue = 0;
  tail_dequeue = dequeue_size - 1;
}

template <typename T> bool Dequeue<T>::is_empty() const {
  return dequeue_size == 0;
}

void run(std::istream &is, std::ostream &os) {
  Dequeue<int> dequeue;

  int num_of_commands;
  is >> num_of_commands;

  for (size_t i = 0; i < num_of_commands; ++i) {
    int dequeue_command_number;
    int dequeue_command_value;
    is >> dequeue_command_number >> dequeue_command_value;

    switch (dequeue_command_number) {
    case 1: {
      dequeue.push_front(dequeue_command_value);
      break;
    }
    case 2: {
      if (dequeue.pop_front() != dequeue_command_value) {
        os << "NO" << std::endl;
        return;
      }
      break;
    }
    case 3: {
      dequeue.push_back(dequeue_command_value);
      break;
    }
    case 4: {
      if (dequeue.pop_back() != dequeue_command_value) {
        os << "NO" << std::endl;
        return;
      }
      break;
    }
    }
  }
  os << "YES" << std::endl;
}

int main(void) {
  run(std::cin, std::cout);
  return 0;
}
