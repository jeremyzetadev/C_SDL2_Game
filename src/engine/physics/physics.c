#include "../arraylist/arraylist.h"
#include "../types.h"
#include <linmath.h>
#include "physics.h"
#include "physics_internal.h"
#include "../global/global.h"
#include "../util.h"

static Physics_State_Internal state;

void aabb_min_max(vec2 min, vec2 max, AABB aabb){
    vec2_sub(min, aabb.position, aabb.half_size);
    vec2_add(max, aabb.position, aabb.half_size);
}

// args vec2 is array  -> decays to pointer (byref)
// args AABB is struct -> pass as a whole   (byval)
bool physics_point_intersect_aabb(vec2 point, AABB aabb){
    vec2 min, max;
    aabb_min_max(min, max, aabb);
    return point[0] >= min [0] &&
           point[0] <= max [0] &&
           point[1] >= min [1] &&
           point[1] <= max [1];
}
// if AABB has array inside -> the array does not decay, pass as a whole   (byval)
// if AABB is declared as array AABB[] -> the array AABB decays to pointer (byref)

void physics_init(void){
    state.body_list = arraylist_create(sizeof(Body), 0);
}

void physics_update(void){
    Body *body;

    for(u32 i=0; i<state.body_list->len; ++i){
        body = arraylist_get(state.body_list, i);
        body->velocity[0] += body->acceleration[0] * global.time.delta;
        body->velocity[1] += body->acceleration[1] * global.time.delta;
        body->aabb.position[0] += body->velocity[0] * global.time.delta;
        body->aabb.position[1] += body->velocity[1] * global.time.delta;
    }
}

size_t physics_body_create(vec2 position, vec2 size){
    Body body = {
        .aabb = {
            .position = {position[0], position[1]},
            .half_size = {size[0]*0.5, size[1]*0.5},
        },
        .velocity ={0, 0}
    };
    
    if(arraylist_append(state.body_list, &body) == -1){
        ERROR_RETURN(-1,"Could not append body to list\n");
    }

    return state.body_list->len-1;
}

Body *physics_body_get(size_t index){
    return arraylist_get(state.body_list, index);
}
