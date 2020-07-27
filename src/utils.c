#include "../include/utils.h"

void
renderer_print_info(SDL_Renderer *renderer)
{
    SDL_RendererInfo info;
    SDL_GetRendererInfo(renderer, &info);
    SDL_Log("Renderer Name: %s\n", info.name);

    SDL_Log("Texture formats: \n");
    for (size_t i = 0; i < info.num_texture_formats; i++) {
        SDL_Log("%s\n", SDL_GetPixelFormatName(info.texture_formats[i]));
    }
}
