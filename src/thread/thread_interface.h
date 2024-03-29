#ifndef SRC_THREAD_THREAD_INTERFACE_H_
#define SRC_THREAD_THREAD_INTERFACE_H_

#include <pthread.h>

namespace thread {

class ThreadInterface {
 public:
  ThreadInterface();
  virtual ~ThreadInterface();

  void Run();
  void Wait();
 protected:
  virtual void* StartRoutine() = 0;
 private:
  pthread_t thread;
  static void* StaticRoutine(void* arg);
};

}  // namespace thread

#endif  // SRC_THREAD_THREAD_INTERFACE_H_
