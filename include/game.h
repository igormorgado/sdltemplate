#ifndef __GAME_H__
#define __GAME_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float    f32;
typedef double   f64;

enum GAME_RETURN_VALUES
{
    GAME_RETURN_SUCCESS,
    GAME_RETURN_FAILURE,
};

enum GAME_BUILD
{
    GAME_BUILD_RELEASE,
    GAME_BUILD_TEST,
    GAME_BUILD_DEBUG,
};

struct game
{
    char *title;
    char *company;
    SDL_Window *window;
    i32 screen_width;
    i32 screen_height;
    /*
     * TODO:
     *  Check if is faster and more feasible to use window->renderer
     */
    SDL_Renderer *renderer;
    bool is_running;

    char * basepath;
    char * prefpath;
};


struct game *   game_init(const char *title, const i32 screen_width, const i32 screen_height, i32 log_priority);
void            game_destroy(struct game *self);
i32             game_handle_input(struct game *game);
i32             game_update(struct game *game);
i32             game_render(struct game *game);
i32             game_wait(struct game *game);
i32             game_set_icon(struct game *game);
void            game_get_base_path(struct game *self);
void            game_get_pref_path(struct game * self);

#endif /* __GAME_H__ */
