#pragma once

#include "../arraylist/arraylist.h"
#include "../types.h"

typedef struct physics_state_internal {
    f32 gravity;
    f32 terminal_velocity;
    Arraylist *body_list;
    Arraylist *static_body_list;
} Physics_State_Internal;
