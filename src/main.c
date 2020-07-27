#include "../include/game.h"
#include <SDL2/SDL_log.h>

int main(void) {
    struct game * game = game_init("Teste", 1280, 720, SDL_LOG_PRIORITY_INFO );

    while(game->is_running)
    {
        game_handle_input(game);
        game_update(game);
        game_render(game);
        game_wait(game);
    }

    game_destroy(game);
    return EXIT_SUCCESS;
}

