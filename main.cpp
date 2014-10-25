#include "ThreadPool.h"

#include <iostream>
#include <unistd.h>

using namespace std;

const int MAX_TASKS = 4;

void hello(void* arg)
{
  int* x = (int*) arg;
  cout << "Hello " << *x << endl;
}

int main(int argc, char* argv[])
{
  ThreadPool tp(1);

  int trys = 0;
  for (int i = 0; i < MAX_TASKS; i++) {
    int* x = new int();
    *x = i+1;
    if (tp.thread_avail()) {
      tp.dispatch_thread(hello, (void*) x);
    }
    else if (trys > 1000) {
      break;
    }
    else {
      trys++;
      i--;
    }
  }

  cout << "Before sleep\n";
  unsigned int microseconds = 2000000;
  usleep(microseconds);

  cout << "Exiting app..." << endl;

  return 0;
}