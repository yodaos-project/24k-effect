#include "include/light.h"

#include "jerryscript-ext/handler.h"

jerry_value_t light_render_handler (const jerry_value_t func_value, /**< function object */
                            const jerry_value_t this_value, /**< this arg */
                            const jerry_value_t *args_p, /**< function arguments */
                            const jerry_length_t args_cnt) /**< number of function arguments */
{
  printf("render...\n");
  return jerry_create_undefined();
}

jerry_value_t light_requestAnimationFrame_handler (const jerry_value_t func_value, /**< function object */
                            const jerry_value_t this_value, /**< this arg */
                            const jerry_value_t *args_p, /**< function arguments */
                            const jerry_length_t args_cnt) /**< number of function arguments */
{
  printf("requestAnimationFrame...\n");
  return jerry_create_undefined();
}

jerry_value_t light_pixel_handler (const jerry_value_t func_value, /**< function object */
                            const jerry_value_t this_value, /**< this arg */
                            const jerry_value_t *args_p, /**< function arguments */
                            const jerry_length_t args_cnt) /**< number of function arguments */
{
  printf("pixel...\n");
  return jerry_create_undefined();
}

void light_init ()
{
  jerry_value_t global_object = jerry_get_global_object();

  jerry_value_t light_object = create_jerry_light_global();
  jerry_value_t light_prop_name = jerry_create_string((const jerry_char_t *) "light");
  jerry_release_value(jerry_set_property(global_object, light_prop_name, light_object));
  jerry_release_value(light_object);
  jerry_release_value(light_prop_name);

  jerry_release_value(global_object);
}

jerry_value_t create_jerry_light_global ()
{
  jerry_value_t light_object = jerry_create_object();

  jerry_value_t prop_name = jerry_create_string((const jerry_char_t *) "render");
  jerry_value_t func_obj = jerry_create_external_function(light_render_handler);
  jerry_release_value(jerry_set_property(light_object, prop_name, func_obj));
  jerry_release_value(func_obj);
  jerry_release_value(prop_name);

  prop_name = jerry_create_string((const jerry_char_t *) "requestAnimationFrame");
  func_obj = jerry_create_external_function(light_requestAnimationFrame_handler);
  jerry_release_value(jerry_set_property(light_object, prop_name, func_obj));
  jerry_release_value(func_obj);
  jerry_release_value(prop_name);

  prop_name = jerry_create_string((const jerry_char_t *) "pixel");
  func_obj = jerry_create_external_function(light_requestAnimationFrame_handler);
  jerry_release_value(jerry_set_property(light_object, prop_name, func_obj));
  jerry_release_value(func_obj);
  jerry_release_value(prop_name);

  return light_object;
}