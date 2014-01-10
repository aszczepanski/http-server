#ifndef SRC_SERVER_CONNECTION_H_
#define SRC_SERVER_CONNECTION_H_

#include "thread/thread_interface.h"

namespace server {

class Connection : public thread::ThreadInterface {
 public:
  void Stop();

 private:
  virtual void* StartRoutine();
};

}  // namespace server

#endif  // SRC_SERVER_CONNECTION_H_
