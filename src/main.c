#include <SDL2/SDL_mouse.h>
#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "engine/util.h"
#include "engine/global/global.h"
#include "engine/input/input.h"
#include "engine/time/time.h"

#include "engine/physics/physics.h"


static bool should_quit = false;
static vec2 pos;

static void input_handle(void){
    if(global.input.escape == KS_PRESSED || global.input.escape == KS_HELD)
        should_quit = true;

    i32 x, y;
    SDL_GetMouseState(&x, &y);
    pos[0] = (f32)x;
    pos[1] = global.render.height - y;
}

int main(int argc, char *argv[]) {
    time_init(60);
    config_init();
    render_init();
    physics_init();

    pos[0] = global.render.width * 0.5;
    pos[1] = global.render.height * 0.5;
    
    SDL_ShowCursor(false);

    // Spawn physics body
    AABB test_aabb = {
        .position = {global.render.width*0.5, global.render.height*0.5}, 
        .half_size = {50, 50}
    };
    // Spawn physics body

    while (!should_quit) {
        time_update();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                should_quit = true;
                break;
            default:
                break;
            }
        }
        input_update();
        input_handle();
        physics_update();

        render_begin();

        // Render physics body
        render_aabb((f32*)&test_aabb, (vec4){1, 1, 1, 0.5});
        if(physics_point_intersect_aabb(pos, test_aabb))
            render_quad(pos, (vec2){5, 5}, RED);
        else
            render_quad(pos, (vec2){5, 5}, WHITE);
        // Render physics body
        
        render_end();
        time_update_late();
    }

    return 0;
}
