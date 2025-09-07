#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define ERROR_EXIT(...) {fprintf(stderr, __VA_ARGS__); exit(1);}
#define ERROR_RETURN(R, ...) {fprintf(stderr, __VA_ARGS__); return R;}
//Mike Shah macro error check sample
//#define GLCheck(x) GLClearAllErrors(); x; GLCheckErrorStatus();
//use GLCheck to a function
//GLCheck(glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject));

#define WHITE (vec4){1, 1, 1, 1}
#define BLACK (vec4){0, 0, 0, 1}
#define RED (vec4){1, 0, 0, 1}
#define GREEN (vec4){0, 1, 0, 1}
#define BLUE (vec4){0, 0, 1, 1}
#define YELLOW (vec4){1, 1, 0, 1}
#define CYAN (vec4){0, 1, 1, 1}
#define MAGENTA (vec4){1, 0, 1, 1}
#define ORANGE (vec4){1, 0.5, 0, 1}
#define PURPLE (vec4){0.5, 0, 1, 1}
#define TURQUOISE (vec4){0, 1, 0.5, 1}
#define GRAY (vec4){1, 1, 1, 0.5}

#endif
