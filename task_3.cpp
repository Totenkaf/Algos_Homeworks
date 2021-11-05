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

#include <iostream>

class Queue {
public:
  Queue() : dataQueue(nullptr), sizeQueue(0), headQueue(0), tailQueue(0) {
    growQueue();
  }

  ~Queue() {
    if (dataQueue != nullptr) {
      delete[] dataQueue;
    }
  }

  // удаляет первый элемент и возвращает его
  int pop() {
    if (headQueue != tailQueue) {
      // очередь не пуста
      int value = dataQueue[headQueue];
      if (headQueue == sizeQueue - 1) {
        headQueue = 0;
      } else {
        headQueue++;
      }
      return value;
    }
    return -1;
  }

  // добавляет новый элемент в конец
  void push(int value) {
    if ((tailQueue + 1) % sizeQueue == headQueue) {
      growQueue();
      push(value);
    } else {
      // добавляем следующий элемент
      dataQueue[(tailQueue) % sizeQueue] = value;
      tailQueue = (tailQueue + 1) % sizeQueue;
    }
  }
  bool isEmpty() { return headQueue == tailQueue; }

private:
  int *dataQueue;
  int sizeQueue;
  int headQueue;
  int tailQueue;

  const int capacityQueue = 10;
  const int sizeFactor = 2;

  void growQueue() {
    int newsizeQueue = (sizeQueue > 0) ? sizeQueue * sizeFactor : capacityQueue,
        *newdataQueue = new int[newsizeQueue];

    if (headQueue != tailQueue) {
      int j = 0;
      for (int i = headQueue; i < sizeQueue; ++i) {
        if (i == tailQueue) {
          break;
        }
        newdataQueue[j++] = dataQueue[i];
        if (i == sizeQueue - 1) {
          i = -1;
        }
      }
      headQueue = 0;
      tailQueue = j;
    }
    if (dataQueue != NULL) {
      delete[] dataQueue;
    }
    dataQueue = newdataQueue;
    sizeQueue = newsizeQueue;
  }
};

int main() {
  Queue queue;
  int numberOfCommands = 0;
  std::cin >> numberOfCommands;

  int queueCommandNumber = 0, commandValue = 0;

  bool queueStatus = true;

  for (int i = 0; i < numberOfCommands; ++i) {
    std::cin >> queueCommandNumber >> commandValue;
    if (!queueStatus) {
      continue;
    }
    switch (queueCommandNumber) {
    case 2:
      if (queue.isEmpty()) {
        commandValue = -1;
      }
      queueStatus = (queue.pop() == commandValue) && queueStatus;
      break;
    case 3:
      queue.push(commandValue);
      break;
    }
  }
  std::cout << (queueStatus ? "YES" : "NO");
  return 0;
}
