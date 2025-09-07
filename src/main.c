#include "engine/render/render.h"
#include <SDL2/SDL_events.h>
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

    AABB cursor_aabb = {.half_size = {75, 75}};

    AABB start_aabb = {.half_size = {75, 75}};

    AABB sum_aabb = {
        .position = {test_aabb.position[0], test_aabb.position[1]},
        .half_size = {
            test_aabb.half_size[0] + cursor_aabb.half_size[0],
            test_aabb.half_size[1] + cursor_aabb.half_size[1]}
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
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button==SDL_BUTTON_LEFT){
                    start_aabb.position[0]=pos[0];
                    start_aabb.position[1]=pos[1];
                }
            default:
                break;
            }
        }
        input_update();
        input_handle();
        physics_update();

        render_begin();

        ////////////////////// 
        // Render physics body
        ////////////////////// 
        cursor_aabb.position[0] = pos[0];
        cursor_aabb.position[1] = pos[1];
        render_aabb((f32*)&sum_aabb, GRAY);
        AABB minkowski_difference = aabb_minkowski_difference(test_aabb, cursor_aabb);
        render_aabb((f32*)&minkowski_difference, ORANGE);

        //line-penetration
        vec2 pv;
        aabb_penetration_vector(pv, minkowski_difference);
        AABB collision_aabb = cursor_aabb;
        collision_aabb.position[0] += pv[0];
        collision_aabb.position[1] += pv[1];

        //collision show body not penetrating shape
        if(physics_aabb_intersect_aabb(test_aabb, cursor_aabb)){
            render_aabb((f32*)&cursor_aabb, RED);
            render_aabb((f32*)&collision_aabb, CYAN);
            vec2_add(pv, pos, pv);
            render_line_segment(pos, pv, CYAN); 
        }else{
            render_aabb((f32*)&cursor_aabb, WHITE);
        }

        //draw start aabb at click
        render_aabb((f32*)&start_aabb, GRAY);
        render_line_segment(start_aabb.position, pos, WHITE);

        render_aabb((f32*)&test_aabb, WHITE);
        if(physics_point_intersect_aabb(pos, test_aabb))
            render_quad(pos, (vec2){5, 5}, RED);
        else
            render_quad(pos, (vec2){5, 5}, WHITE);
        ////////////////////// 
        // Render physics body
        ////////////////////// 
        
        render_end();
        time_update_late();
    }

    return 0;
}
