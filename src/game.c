#include "../include/game.h"


    struct game *
game_init(const char *title, const i32 screen_width, const i32 screen_height, i32 log_priority)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s ENTERED\n", __func__);

    SDL_assert_paranoid(screen_width > 0);
    SDL_assert_paranoid(screen_width <= 4096);
    SDL_assert_paranoid(screen_height > 0);
    SDL_assert_paranoid(screen_height <= 4096);

    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, log_priority);

    i32 retval;
    retval = SDL_Init(SDL_INIT_EVERYTHING);
    if(retval != 0)
    {
        SDL_LogError (SDL_LOG_CATEGORY_APPLICATION, "%s: SDL_Init: %s\n", __func__, SDL_GetError());
        exit(EXIT_FAILURE);
    }

    struct game * self = malloc(sizeof *self);
    memset(self, 0, sizeof *self);

    self->window = NULL;
    self->screen_width = screen_width;
    self->screen_height = screen_height;
    self->window = SDL_CreateWindow("Engine: Init",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            self->screen_width,
            self->screen_height,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(!self->window)
    {
        SDL_LogError (SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    self->title = SDL_strdup (title);
    SDL_SetWindowTitle(self->window, title);

    /* TODO: Set widow ICON if available */

    self->renderer = NULL;
    self->renderer = SDL_CreateRenderer(self->window, -1, SDL_RENDERER_ACCELERATED);
    if(!self->renderer)
    {
        SDL_LogError (SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetRenderDrawColor(self->renderer, 0x1f, 0x1f, 0x1f, SDL_ALPHA_OPAQUE);
    if(retval < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    self->is_running = true;

    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s EXIT \n", __func__);
    return self;
}


    void
game_destroy(struct game *self)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s ENTERED\n", __func__);
    if(self)
    {
        free(self->title);
        self->title = NULL;

        if(self->renderer)
        {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Destroying renderer\n");
            SDL_DestroyRenderer (self->renderer);
            self->renderer = NULL;
        }

        if(self->window)
        {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Destroying main window\n");
            SDL_DestroyWindow (self->window);
            self->window = NULL;
        }
    }
    IMG_Quit();
    SDL_Quit();
    SDL_Log ("Engine closed\n");
    SDL_Log("Bye.\n");
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s EXIT\n", __func__);
}


    i32
game_handle_input(struct game *game)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s ENTERED\n", __func__);
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                game->is_running = false;
                break;
        }
    }
    // SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");
    //
    // SDL_GameController *gamecontroller;
    // SDL_Joystick *joystick;
    // SDL_JoystickPowerLevel plevel;
    // case SDL_KEYDOWN:
    //     if (event.key.keysym.sym == SDLK_ESCAPE) {
    //         is_running = SDL_FALSE;
    //     }
    //     break;

    //     /*
    //      * GAME CONTROLLER
    //      */
    // case SDL_CONTROLLERDEVICEADDED:
    //     name = SDL_JoystickNameForIndex(event.cdevice.which);
    //     /* Fixed in SDLBUG 5233 */
    //     if (name && SDL_strstr(name, "Motion Sensors")) { break; }

    //     gamecontroller = SDL_GameControllerOpen(event.cdevice.which);
    //     if(gamecontroller)
    //     {
    //         joystick = SDL_GameControllerGetJoystick (gamecontroller);
    //         plevel = SDL_JoystickCurrentPowerLevel(joystick);
    //         if (plevel == SDL_JOYSTICK_POWER_UNKNOWN)
    //         {
    //             SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
    //                     "%s: SDL_JoystickCurrentPowerLevel(): %s\n",
    //                     __func__, SDL_GetError());
    //         }
    //         SDL_Log("Controller %d opened - PowerLevel %d\n", event.cdevice.which, plevel);
    //     } else {
    //         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
    //                 "%s: SDL_GameControllerOpen(%d): %s\n",
    //                 __func__, event.cdevice.which, SDL_GetError());
    //     }
    //     break;
    // case SDL_CONTROLLERDEVICEREMOVED:
    //     SDL_Log("Controller %d detached.\n", (int) event.cdevice.which);
    //     gamecontroller = SDL_GameControllerFromInstanceID(event.cdevice.which);
    //     if(gamecontroller)
    //     {
    //         SDL_GameControllerClose(gamecontroller);
    //         SDL_Log("Game controller device %d closed.\n", (int) event.cdevice.which);
    //     } else {
    //         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
    //                 "%s: SDL_GameControllerFromInstanceID(%d): %s\n",
    //                 __func__, event.cdevice.which, SDL_GetError());
    //     }
    //     break;
    // case SDL_CONTROLLERBUTTONDOWN:
    // case SDL_CONTROLLERBUTTONUP:
    //     SDL_Log("Controller %d button '%s' %s\n",
    //             event.cdevice.which,
    //             SDL_GameControllerGetStringForButton((SDL_GameControllerButton)event.cbutton.button),
    //             event.cbutton.state ? "pressed" : "released");
    //     break;

    //     /*
    //      * JOYSTICK
    //      */
    // case SDL_JOYDEVICEADDED:
    //     /* This device is a Game Controller we will handle elsewhere */
    //     if (SDL_IsGameController(event.jdevice.which))
    //     {
    //         SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "JOYDEVADD: Guard triggered\n");
    //         break;
    //     }

    //     SDL_Log("Joystick   %d found.\n", event.jdevice.which );
    //     joystick = SDL_JoystickOpen(event.jdevice.which);
    //     if(joystick) {
    //         plevel = SDL_JoystickCurrentPowerLevel(joystick);
    //         if (plevel == SDL_JOYSTICK_POWER_UNKNOWN)
    //         {
    //             SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
    //                     "%s: SDL_JoystickCurrentPowerLevel(): %s\n",
    //                     __func__, SDL_GetError());
    //         }
    //         SDL_Log("Joystick   %d opened - PowerLevel %d\n", event.jdevice.which, plevel);
    //     } else {
    //         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
    //                 "%s: SDL_JoystickOpen(%d): %s\n",
    //                 __func__, event.jdevice.which, SDL_GetError());
    //     }
    //     break;
    // case SDL_JOYDEVICEREMOVED:
    //     /*
    //      * This guard is necessary for two reasons:
    //      * 1. If a joystick event was received but we will handle
    //      *    as a GameController;
    //      * 2. If it was ALREADY handled as game controller, hence
    //      *    we will not be able to fetch the controller or the
    //      *    joystick id
    //      */
    //     joystick = SDL_JoystickFromInstanceID(event.jdevice.which);
    //     if (SDL_GameControllerFromInstanceID(event.jdevice.which) || !joystick)
    //     {
    //         SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "JOYDEVREM: Guard triggered\n");
    //         break;
    //     }

    //     SDL_Log("Joystick   %d dettached.\n", event.jdevice.which);
    //     if(joystick)
    //     {
    //         SDL_JoystickClose(joystick);
    //         SDL_Log("Joystick   %d closed.\n", (int) event.jdevice.which);
    //     } else {
    //         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
    //                 "%s: SDL_JoystickFromInstanceID(%d): %s\n",
    //                 __func__, event.jdevice.which, SDL_GetError());
    //     }
    //     break;
    // case SDL_JOYBUTTONDOWN:
    // case SDL_JOYBUTTONUP:
    //     /* This device is a Game Controller we will handle elsewhere */
    //     if (SDL_GameControllerFromInstanceID(event.jdevice.which))
    //     {
    //         SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "JOYDEVBUT: Guard triggered\n");
    //         break;
    //     }

    //     SDL_Log("Joystick   %d - Button: %d %s\n",
    //             event.jdevice.which,
    //             event.jbutton.button,
    //             event.jbutton.state ? "pressed" : "released");
    //     break;
    // default:
    //     break;


    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s EXIT\n", __func__);
    return GAME_RETURN_SUCCESS;
}


    i32
game_update(struct game *game)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s ENTERED\n", __func__);
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s EXIT\n", __func__);
    return GAME_RETURN_SUCCESS;
}


    i32
game_render(struct game *self)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s ENTERED\n", __func__);
    int retval;
    retval = SDL_RenderClear(self->renderer);
    if(retval < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_RenderClear: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Last render command
    SDL_RenderPresent(self->renderer);
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s EXIT\n", __func__);
    return GAME_RETURN_SUCCESS;
}


    i32
game_wait(struct game *self)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s ENTERED\n", __func__);
    SDL_Delay(1);       /* Keep CPU cool */
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s EXIT\n", __func__);
    return 1;
}


    void
game_get_base_path(struct game *self)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s ENTERED\n", __func__);
    char *data_path = NULL;
    char *base_path = SDL_GetBasePath();
    if (base_path) {
        data_path = base_path;
    } else {
        data_path = SDL_strdup("./");
    }
    self->basepath = SDL_strdup(data_path);

    if(data_path)
    {
        free(data_path);
        data_path = NULL;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s EXIT\n", __func__);
}



    void
game_get_pref_path(struct game * self)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s ENTERED\n", __func__);
    char *pref_path = NULL;

    char *base_path = SDL_GetPrefPath(self->company, self->title);
    if (base_path) {
        pref_path = base_path;
    } else {
        SDL_Log ("Could not find a pref path\n");
    }

    self->prefpath = SDL_strdup (pref_path);

    if (base_path)
    {
        free(base_path);
        base_path = NULL;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s EXIT\n", __func__);
}

