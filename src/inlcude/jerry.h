#ifndef JERRY_H
#define JERRY_H

#include "jerryscript.h"

void setup_jerry ();

void clean_jerry ();

jerry_value_t run_effect_handler (jerry_value_t handler);

#endif // JERRY_H