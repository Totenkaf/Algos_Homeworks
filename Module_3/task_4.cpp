// Copyright 2022 by Artem Ustsov

/*
* Написать алгоритм для решения игры в “пятнашки”. Решением задачи является приведение к виду:
*	[ 1  2  3  4 ]
*	[ 5  6  7  8 ]
*	[ 9  10 11 12] 
*	[ 13 14 15 0 ]
* где 0 задает пустую ячейку.
* 
* Достаточно найти хотя бы какое-то решение. Число перемещений костяшек не обязано быть минимальным.
* Формат входных данных
* Начальная расстановка.
* Формат выходных данных
* Если решение существует, то в первой строке выходного файла выведите минимальное число перемещений костяшек, которое нужно сделать, 
* чтобы достичь выигрышной конфигурации, а во второй строке выведите соответствующую последовательность ходов: 
* L означает, что костяшка сдвинулась влево, R – вправо, U – вверх, D – вниз. 
* Если таких последовательностей несколько, то выведите любую из них. Если же выигрышная конфигурация недостижима, 
* то выведите в выходной файл одно число −1.
*
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <unordered_map>

static constexpr uint8_t NUM_OF_CELLS = 16;
static constexpr uint8_t NUM_OF_NON_EMPTY_CELLS = NUM_OF_CELLS - 1;

static constexpr uint8_t MOVE_UP_POSITION = 3;
static constexpr uint8_t MOVE_DOWN_POSITION = 12;
static constexpr uint8_t MOVE_RIGHT_POSITION = 3;
static constexpr uint8_t MOVE_LEFT_POSITION = 0;

static constexpr uint8_t NUM_OF_MOVE_STAGES = 4;

class State {
public:
	State();
	bool operator==(const State&) const;
	bool operator!=(const State&) const;

	struct HashFunc {
		size_t operator()(const State&) const;
	};
	struct Comparator {
		bool operator()(const State&, const State&) const;
	};

	void calculate_heuristic();
	bool can_move_up() const;
	bool can_move_down() const;
	bool can_move_left() const;
	bool can_move_right() const;

	State move_up() const;
	State move_down() const;
	State move_left() const;
	State move_right() const;

	bool check() const;

	uint8_t empty_cell_position;
	uint8_t cells[NUM_OF_CELLS];
	uint8_t shortest_distance;
	uint8_t astar_heuristic;
};

static void make_astar_proceed(std::unordered_map<State, std::pair<State, char>, State::HashFunc> &visited,
std::set<State, State::Comparator> &pq, State &current_state, State next_state, char step) {
	auto it = visited.find(next_state);
	if (it == visited.end()) {
		visited[next_state] = std::make_pair(current_state, step);
		next_state.shortest_distance = current_state.shortest_distance + 1;
		pq.insert(next_state);
	} else if (next_state.shortest_distance > current_state.shortest_distance + 1) {
		pq.erase(it->first);
		next_state.shortest_distance = current_state.shortest_distance + 1;
		pq.insert(next_state);
	}
}

static bool find_solution(State &start_state, std::string &result) {
	start_state.calculate_heuristic();
	std::unordered_map<State, std::pair<State, char>, State::HashFunc> visited;
	visited[start_state] = std::make_pair(start_state, 0);
	std::set<State, State::Comparator> pq;
	pq.insert(start_state);
	do {
		State current_state = *pq.begin();
		pq.erase(pq.begin());
		if (current_state.check()) {
			while (current_state != start_state) {
				auto pair = visited[current_state];
				result += pair.second;
				current_state = pair.first;
			}
			std::reverse(result.begin(), result.end());
			return true;
		}
		if (current_state.can_move_up()) {
			make_astar_proceed(visited, pq, current_state, current_state.move_up(), 'D');
		}
		if (current_state.can_move_down()) {
			make_astar_proceed(visited, pq, current_state, current_state.move_down(), 'U');
		}
		if (current_state.can_move_left()) {
			make_astar_proceed(visited, pq, current_state, current_state.move_left(), 'R');
		}
		if (current_state.can_move_right()) {
			make_astar_proceed(visited, pq, current_state, current_state.move_right(), 'L');
		}
	} while (!pq.empty());
	return false;
}

State::State(): 
empty_cell_position(0), cells{}, shortest_distance(0), astar_heuristic(0) 
{}

bool State::operator==(const State &game_state) const {
	if (empty_cell_position != game_state.empty_cell_position) {
		return false;
	}
	for (size_t index = 0; index < NUM_OF_CELLS; ++index) {
		if (cells[index] != game_state.cells[index]) {
			return false;
		}
	}
	return true;
}

bool State::operator!=(const State &game_state) const {
	return !(*this == game_state);
}

bool State::can_move_up() const {
	return empty_cell_position > MOVE_UP_POSITION;
}

bool State::can_move_down() const {
	return empty_cell_position < MOVE_DOWN_POSITION;
}

bool State::can_move_left() const {
	return empty_cell_position % NUM_OF_MOVE_STAGES != MOVE_LEFT_POSITION;
}

bool State::can_move_right() const {
	return empty_cell_position % NUM_OF_MOVE_STAGES != MOVE_RIGHT_POSITION;
}

State State::move_up() const {
	assert(can_move_up());
	State new_game_state(*this);
	new_game_state.empty_cell_position -= NUM_OF_MOVE_STAGES;
	std::swap(new_game_state.cells[empty_cell_position], new_game_state.cells[new_game_state.empty_cell_position]);
	new_game_state.calculate_heuristic();
	return new_game_state;
}

State State::move_down() const {
	assert(can_move_down());
	State new_game_state(*this);
	new_game_state.empty_cell_position += NUM_OF_MOVE_STAGES;
	std::swap(new_game_state.cells[empty_cell_position], new_game_state.cells[new_game_state.empty_cell_position]);
	new_game_state.calculate_heuristic();
	return new_game_state;
}

State State::move_left() const {
	assert(can_move_left());
	State new_game_state(*this);
	new_game_state.empty_cell_position--;
	std::swap(new_game_state.cells[empty_cell_position], new_game_state.cells[new_game_state.empty_cell_position]);
	new_game_state.calculate_heuristic();
	return new_game_state;
}

State State::move_right() const {
	assert(can_move_right());
	State new_game_state(*this);
	new_game_state.empty_cell_position++;
	std::swap(new_game_state.cells[empty_cell_position], new_game_state.cells[new_game_state.empty_cell_position]);
	new_game_state.calculate_heuristic();
	return new_game_state;
}

bool State::check() const {
	if (empty_cell_position != NUM_OF_NON_EMPTY_CELLS) {
		return false;
	}
	for (size_t index = 0; index < NUM_OF_NON_EMPTY_CELLS; ++index) {
		if (cells[index] != index + 1) {
			return false;
		}
	}
	return true;
}

void State::calculate_heuristic() {
	astar_heuristic = 0;
	for (size_t index = 0; index < NUM_OF_CELLS; ++index) {
		if (cells[index] != 0) {
			if (cells[index] < index + 1) {
				astar_heuristic += index + 1 - cells[index];
			} else {
				astar_heuristic += cells[index] - index - 1;
			}
		}
	}
}

size_t State::HashFunc::operator()(const State &game_state) const {
	size_t index = NUM_OF_NON_EMPTY_CELLS;
	size_t power16 = 1;
	size_t result = 0;
	do {
		result += game_state.cells[index] * power16;
		power16 *= NUM_OF_CELLS;
	} while ((index--) > 0);
	return result;
}

bool State::Comparator::operator()(const State &game_state1, const State &game_state2) const {
	if (game_state1.astar_heuristic == game_state2.astar_heuristic) {
		return game_state1.shortest_distance < game_state2.shortest_distance;
	} 
	return game_state1.astar_heuristic < game_state2.astar_heuristic;
}

int main() {
    State start_game_state;
	unsigned short number = 0;
	for (size_t index = 0; index < NUM_OF_CELLS; ++index) {
		std::cin >> number;
		start_game_state.cells[index] = number;
		if (number == 0) {
			start_game_state.empty_cell_position = index;
		}
	}
	std::string result;
	if (find_solution(start_game_state, result)) {
		std::cout << result.length() << std::endl << result;
	} else {
		std::cout << -1;
	}
	return 0;
}
