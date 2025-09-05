#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define ERROR_EXIT(...) {fprintf(stderr, __VA_ARGS__); exit(1);}
#define ERROR_RETURN(R, ...) {fprintf(stderr, __VA_ARGS__); return R;}
//Mike Shah macro error check sample
//#define GLCheck(x) GLClearAllErrors(); x; GLCheckErrorStatus();
//use GLCheck to a function
//GLCheck(glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject));

#endif
