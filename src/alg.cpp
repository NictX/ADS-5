// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char i) {
    switch (i) {
        case '(': return 0;
        case ')': return 1;
        case '+': return 2;
        case '-': return 2;
        case '*': return 3;
        case '/': return 3;
        case ' ': return 4;
        default : return 5;
    }
}

int calculate(char i, int a, int b) {
      switch (i) {
        case '+': return b + a;
        case '-': return b - a;
        case '*': return b * a;
        case '/':
        if ( a != 0) return b / a;
        default : return 0;
    }
}

std::string infx2pstfx(std::string inf) {
  TStack<char, 20> stack1;
  std::string post;
  for (int i = 0; i < inf.size(); i++) {
    if (priority(inf[i]) == 5) {
      post += inf[i];
      post += ' ';
    } else {
      if (priority(inf[i]) == 0) {
        stack1.push(inf[i]);
      } else if (stack1.isEmpty()) {
        stack1.push(inf[i]);
      } else if (priority(inf[i]) > priority(stack1.get())) {
        stack1.push(inf[i]);
      } else if (priority(inf[i]) == 1) {
        while (priority(stack1.get()) != 0) {
          post += stack1.get();
          post += ' ';
          stack1.pop();
        }
        stack1.pop();
      } else {
        while (stack1.isEmpty() && (priority(inf[i]) <= priority(stack1.get()))) {
            post += stack1.get();
            post += ' ';
            stack1.pop();
        }
        stack1.push(inf[i]);
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

int eval(std::string post) {
  TStack<int, 50> stack2;
  int math = 0;
  for (int i = 0; i < post.size(); i++) {
    if (priority(post[i]) == 5) {
      stack2.push(post[i] - '0');
    } else if (priority(post[i]) < 4) {
      int x = stack2.get();
      stack2.pop();
      int y = stack2.get();
      stack2.pop();
      stack2.push(calculate(post[i], x, y));
    }
  }
  math = stack2.get();
  return math;
}
