#include <string>
#include <map>
#include "tstack.h"

int priority(char oper) {
    switch (oper) {
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

int calculate(char oper, int a, int b) {
      switch (oper) {
        case '+': return b + a;
        case '-': return b - a;
        case '*': return b * a;
        case '/':
        if ( a != 0)
        return b / a;
        default : return 0;
    }
}

std::string infx2pstfx(std::string inf) {
  std::string post;
  TStack <char, 100> t;
  for (int i = 0; i < inf.size(); i++) {
    if (priority(inf[i]) == 5) {
        post += inf[i];
        post += ' ';
    } else {
    if (priority(inf[i]) == 0) {
        t.push(inf[i]);
    } else if (t.isEmpty()) {
       t.push(inf[i]);
    } else if ((priority(inf[i]) > priority(t.get()))) {
        t.push(inf[i]);
    } else if (priority(inf[i]) == 1) {
        while (priority(t.get()) != 0) {
            post += t.get();
            post += ' ';
            t.pop();
        }
        t.pop();
    } else {
        while (!t.isEmpty() && (priority(inf[i]) <= priority(t.get()))) {
            post += t.get();
            post += ' ';
            t.pop();
        }
        t.push(inf[i]);
    }
    }
  }
  while (!t.isEmpty()) {
    post += t.get();
    post += ' ';
    t.pop();
  }
  for (int j = 0; j < post.size(); j++) {
      if (post[post.size()-1] == ' ')
      post.erase(post.size() - 1);
  }
  return post;
}

int eval(std::string pref) {
TStack <int, 100> t;
int res = 0;
for (int i = 0; i < pref.size(); i ++) {
    if (priority(pref[i]) == 5) {
        t.push(pref[i] - '0');
    } else if (priority(pref[i]) < 4) {
        int x = t.get();
        t.pop();
        int y = t.get();
        t.pop();
        t.push(calculate(pref[i], x, y));
    }
}
res = t.get();
return res;
}
