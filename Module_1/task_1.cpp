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



// Copyright 2022 Artem Ustsov

/*
 *
 * Задача № 1_1
 * Подсчитать кол-во единичных бит в входном числе, стоящих на четных позициях. 
 * Позиции битов нумеруются с 0.
 * 
 * Во всех задачах необходимо использование битовых операций. 
 * Использование арифметических операций запрещено. 
 * Входное число лежит в диапазоне 0..232 -1 и вводится в десятичном виде.
 *
 * Ввод/вывод отделены от решения.
 * Не должно быть утечек памяти, за каждую утечку памяти - штраф “-1”.
 */

#include <iostream>

int count_of_one_bits(uint number) {
  size_t i = 0;
  size_t counter = 0;
  while (number != 0) {
    if (i % 2 == 0 && (number & 1) == 1) {
      counter++;
    }
    number = number >> 1;
    i++;
  }
  return counter;
}

int main() {
  int number = 0;
  std::cin >> number;

  std::cout << count_of_one_bits(number) << std::endl;
  return 0;
}