#include "jerryscript.h"
#include "jerryscript-core.h"
#include "jerryscript-ext/handler.h"
#include "jerryscript-port.h"

void module_init ()
{
  jerry_value_t global_object = jerry_get_global_object();
  jerry_value_t module_object = jerry_create_object();
  jerry_value_t module_object_name = jerry_create_string((const jerry_char_t *) "module");

  jerry_value_t exports_prop_name = jerry_create_string((const jerry_char_t *) "exports");
  jerry_value_t exports_default_value = jerry_create_undefined();
  
  jerry_release_value(jerry_set_property(module_object, exports_prop_name, exports_default_value));
  jerry_release_value(jerry_set_property(global_object, module_object_name, module_object));
  
  jerry_release_value(exports_default_value);
  jerry_release_value(exports_prop_name);
  
  jerry_release_value(module_object_name);
  jerry_release_value(module_object);
  
  jerry_release_value(global_object);
}

/**
 * load a js file and return the exports value.
 * This function can only be used after the module_init() function is called.
 */
jerry_value_t jerry_require (const char *file_name_p)
{
  size_t size = 0;
  jerry_char_t *script = jerry_port_read_source(file_name_p, &size);
  if (script == NULL)
  {
    return jerry_create_error(JERRY_ERROR_URI, (const jerry_char_t *) "No such file");
  }
  if (size == 0)
  {
    return jerry_create_undefined();
  }

  jerry_value_t parsed_code = jerry_parse (NULL, 0, script, size, JERRY_PARSE_NO_OPTS);
  // free script
  jerry_port_release_source(script);

  if (jerry_value_is_error(parsed_code))
  {
    jerry_release_value(parsed_code);
    return jerry_create_undefined();
  }
  
  /* Execute the parsed source code in the Global scope */
  jerry_value_t ret_value = jerry_run (parsed_code);
  jerry_release_value(parsed_code);
  jerry_release_value(ret_value);

  // get module.exports property
  jerry_value_t global_object = jerry_get_global_object();
  jerry_value_t module_prop_name = jerry_create_string((const jerry_char_t *) "module");
  jerry_value_t exports_prop_name = jerry_create_string((const jerry_char_t *) "exports");
  jerry_value_t module_value = jerry_get_property(global_object, module_prop_name);
  jerry_value_t exports_value = jerry_get_property(module_value, exports_prop_name);
  // free value
  jerry_release_value (global_object);
  jerry_release_value (module_prop_name);
  jerry_release_value (exports_prop_name);
  jerry_release_value (module_value);

  return exports_value;
}