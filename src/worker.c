#include "inlcude/worker.h"

#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "jerryscript-port.h"

#include "module.h"

#include "inlcude/jerry.h"

void SIGCHLD_handler (int signum)
{
  printf("receive taskProcess signal: SIGCHLD. signum: %d\n", signum);
  pid_t child_pid = wait(NULL);
  printf("taskProcess: %d was exited.\n", child_pid);
}

void register_worker_signal_handler ()
{
  signal(SIGCHLD, SIGCHLD_handler);
}

int8_t push_js_effect_task (const char *file_name_p)
{
  pid_t pid = fork();
  if (pid < 0)
  {
    printf("fork error. fork return errno: %d\n", pid);
    return -1;
  } else if (pid > 0) {
    printf("new effect task run in pid: %d\n", pid);
    return 0;
  } else {
    jerry_value_t exports = jerry_require(file_name_p);
    if (jerry_value_is_error(exports))
    {
      jerry_release_value(exports);
      printf("taskProcess: require js effect error: No such file: %s\n", file_name_p);
      exit(EXIT_FAILURE);
    }
    jerry_value_t ret_value = run_effect_handler(exports);
    printf("taskProcess: js effect task was completed. exit now! pid: %d\n", getpid());
    exit(EXIT_SUCCESS);
  }
}