#include "inlcude/jerry.h"

#include "jerryscript.h"
#include "jerryscript-port.h"
#include "jerryscript-ext/handler.h"

void setup_jerry ()
{
  /* Initialize engine */
  jerry_init (JERRY_INIT_EMPTY);

  /* Register 'print' function from the extensions */
  jerryx_handler_register_global ((const jerry_char_t *) "print",
                                  jerryx_handler_print);
}

void clean_jerry ()
{
  /* Cleanup engine */
  jerry_cleanup ();
}

jerry_value_t run_effect_handler (jerry_value_t handler)
{
  if (jerry_value_is_function(handler))
  {
    jerry_value_t this_value = jerry_create_undefined();
    jerry_value_t ret_value = jerry_call_function(handler, this_value, NULL, 0);
    
    jerry_release_value (handler);
    jerry_release_value(this_value);
    
    return ret_value;
  }
  jerry_release_value(handler);
  return jerry_create_undefined();
}