#ifndef MODULE_H
#define MODULE_H

#include "jerryscript-core.h"

void module_init ();

/**
 * load a js file and return the exports value.
 * This function can only be used after the module_init() function is called.
 */
jerry_value_t jerry_require (const char *file_name_p);

#endif