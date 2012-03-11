#ifndef MACROS_H
#define MACROS_H

#include <stdint.h>
#include <stdbool.h>


#define forever while(1)
// Diferentes tipos de busy-waits
#define waitUntil(c)  while(!(c));
#define waitWhile(c)  while(c);

#define MAX(a, b) (((a)>(b))?(a):(b))

#endif
