// Copyright 2021 Artem Ustsov

/*
 *
 * Задача № 1_3
 * Если в числе содержится только один бит со значением 1, записать в выходной
 * поток OK. Иначе записать FAIL Во всех задачах необходимо использование
 * битовых операций. Использование арифметических операций запрещено. Входное
 * число лежит в диапазоне 0..232 -1 и вводится в десятичном виде.
 *
 * Ввод/вывод отделены от решения.
 * Не должно быть утечек памяти, за каждую утечку памяти - штраф “-1”.
 */

// double linked list
#include <iostream>

bool is_only_one_one_bit(uint number) {
  size_t counter = 0;
  while (number != 0) {
    if ((number & 1) == 1) {
      counter++;
      number = number >> 1;
    } else {
      number = number >> 1;
    }
  }

  if (counter == 1) {
    return true;
  } else {
    return false;
  }
}

int main() {
  int number = 0;
  std::cin >> number;

  if (number < 0) {
    std::cout << "[WRONG INPUT]" << std::endl;
    return -1;
  }

  if (is_only_one_one_bit(number)) {
    std::cout << "OK" << std::endl;
  } else {
    std::cout << "FAIL" << std::endl;
  }
  return 0;
}
