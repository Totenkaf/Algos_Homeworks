/*
* Ввод/вывод отделены от решения.
* Не должно быть утечек памяти, за каждую утечку памяти - штраф “-1”.
*
* Задача № 1_3
* Если в числе содержится только один бит со значением 1, записать в выходной поток OK. Иначе записать FAIL
* Требования:  Решить перебором
*
*/

//double linked list
#include <iostream>
 
//people struct which receives next pointer, previous pointer, and current people position
struct People {
  int pos;
  People *next, *prev;
} *first_people = nullptr, *cur_people = nullptr, *to_kill_people = nullptr;


int find_survive(int N, int k) {

	//exceptions
	if (N == 0 && k == 0) {
		return 0;
	}
	if (N == 1) {
		return 1;
	}

	int result = 0;
	// creating a people circle
	// creating the first people in the circle 
	for (int pos = 1; pos <= N; ++pos) {	
		if (first_people == nullptr && cur_people == nullptr) {
			cur_people = new People;
			cur_people->pos = pos;
			cur_people->next = nullptr;
			cur_people->prev = nullptr;
			first_people = cur_people;
	// creating remaining people in the circle
		} else {
			to_kill_people = new People;
			to_kill_people->pos = pos;
			to_kill_people->next = nullptr;
			to_kill_people->prev = cur_people;
			cur_people->next = to_kill_people;
			cur_people = to_kill_people;
		}
	}
	// cycling the circle
	cur_people->next = first_people;
	first_people->prev = cur_people;

	// start with the first people
	// and kill everyone until there is only one survivor
	cur_people = first_people;
	while (N > 1) {
		// as a default we looking at current people to kill
		to_kill_people = cur_people;

		for (int i = 1; i < k; ++i) {
			to_kill_people = to_kill_people->next;
		}
		// kill the poor fellow
		to_kill_people->next->prev = to_kill_people->prev;
		to_kill_people->prev->next = to_kill_people->next;

		// after kill people starts with the next one
		cur_people = to_kill_people->next;
		delete to_kill_people;
		N--;
	}

	result = cur_people->pos;

	delete cur_people;
	return result;
}


int main () {
	int N = 0;
	std::cin >> N;
	int k = 0;
	std::cin >> k;

	std::cout << find_survive(N, k) << std::endl;
	return 0;
}


//with cycled array
int find_survive_array(int N, int k) {
	if (N == 0 && k == 0) {
		return 0;
	}
	if (N == 1) {
		return 1;
	}
	
	bool* alive_people = new bool[N];

	for (int i = 0; i < N; ++i) {
		alive_people[i] = true;
	}
	int curr_person = 0;

	for (int i = 0; i < N; ++i) {
		int skipped = 1;
		while (skipped < k || !alive_people[curr_person]) {
			skipped += alive_people[curr_person];
			curr_person = (curr_person + 1) % N;
		}
		alive_people[curr_person] = false;
	}

	delete[] alive_people;
	return curr_person + 1;
}


//with formula
int find_survive_formula(int N, int k) {
	if (N == 0 && k == 0) {
		return 0;
	}
	if (N == 1) {
		return 1;
	}
	
	int cur = 0;
	for (int i = 1; i <= N; ++i)
		cur = (cur + k) % i;
	return cur + 1;
}