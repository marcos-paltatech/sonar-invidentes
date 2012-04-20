#ifndef GLOBAL_H
#define GLOBAL_H

// Diferentes tipos de busy-waits y loop
#define forever			while(1)
#define waitUntil(c)	while(!(c));
#define waitWhile(c)	while(c);

#define MAX(a, b) (((a)>(b))?(a):(b))
#define MIN(a, b) (((a)<(b))?(a):(b))

#endif
