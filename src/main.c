#include "jerryscript.h"
#include "jerryscript-port.h"
#include "jerryscript-ext/handler.h"

#include "light.h"
#include "module.h"

#include "inlcude/jerry.h"
#include "inlcude/worker.h"

void init_components ()
{
  light_init();
  module_init();
}

int main (void)
{
  // register worker signal.
  register_worker_signal_handler();

  // setup jerry engine.
  setup_jerry();

  // init all components here.
  init_components();

  const char *file_name_p = "example/render.js";
  uint8_t ret = push_js_effect_task(file_name_p);
  printf("js effect task result: %d", ret);

  // clean jerry engine.
  clean_jerry();

  printf("All task complete! exit now!");

  return 0;
}