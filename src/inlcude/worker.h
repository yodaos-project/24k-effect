#ifndef WORKER_H
#define WORKER_H

#include <stdint.h>

void SIGCHLD_handler (int signum);
void register_worker_signal_handler ();

int8_t push_js_effect_task (const char *file_name_p);

#endif