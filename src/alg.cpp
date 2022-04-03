// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
  TStack<char, 20> stack1;
  std::string post;
  std::map<char, int> ci;
  ci['('] = 0;
  ci[')'] = 0;
  ci['+'] = 1;
  ci['-'] = 1;
  ci['*'] = 2;
  ci['/'] = 2;
  for (char i : inf) {
    if (ci.find(i) == ci.end()) {
      post += i;
      post += ' ';
    } else {
      if (i == ')') {
        while (stack1.get() != '(') {
          post += stack1.get();
          post += ' ';
          stack1.pop();
        }
        stack1.pop();
      } else if (ci[i] > ci[stack1.get()]) {
        stack1.push(i);
      } else if (i == '(' || stack1.isEmpty()) {
        stack1.push(i);
      } else {
        while (ci[stack1.get()] >= ci[i] && !stack1.isEmpty()) {
          post += stack1.get();
          post += ' ';
          stack1.pop();
        }
        stack1.push(i);
      }
    }
  }
  while (!stack1.isEmpty()) {
    post += stack1.get();
    post += ' ';
    stack1.pop();
  }
  post.pop_back();
  return post;
}

int eval(std::string pref) {
  TStack<int, 50> stack2;
  int i = 0;
  int x, y = 0;
  int math = 0;
  while (i < post.length()) {
    if (Imp(post[i]) == 10) {
      if (post[i] != ' ') {
        stack2.push(post[i] - '0');
      }
    } else if (Imp(post[i]) < 4) {
      x = stack1.get();
      stack2.pop();
      y = stack2.get();
      stack2.pop();
      stack2.push(calcul(post[i], y, x));
    }
    i++;
  }
  math = stack2.get();
  return math;
}
