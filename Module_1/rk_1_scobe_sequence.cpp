// Copyright 2022 by Artem Ustsov
#include <iostream>
#include <stack>


bool find_bracket_sequence(std::stack<int>& std_stack, std::string input_string) {
    bool error = false;
    for (size_t i = 0; i < input_string.size() && !error; ++i) {
        if (input_string[i] == '(') {
            std_stack.push(input_string[i]);
        } else {
            if(input_string[i] == ')' && !std_stack.empty() && std_stack.top() == '(') {
                std_stack.pop();
            }
            else if (input_string[i] == ')' && std_stack.empty()) {
                std_stack.push(i);
                error = true;
            }
        }
    }
    return std_stack.empty();
}


int main() {
    std::stack <int> std_stack;
    std::string input_brackets;
    std::cin >> input_brackets;

    if (find_bracket_sequence(std_stack, input_brackets)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}
