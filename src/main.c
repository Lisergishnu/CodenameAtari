/**
 * main.c - Entrada inicial al juego
 * Autor: MBT
 */
#include <stdio.h>
#include "sdl.h"
#include "video.h"
#include "game.h"
#include "audio.h"
#include "icon.h"

#define APPSCENE_INTRO_TIMER 5000.0f

AppScene currentAppScene = APPSCENE_INTRO;
SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
int isGameRunning = 1;
SDL_Event currentEvent;
int lastTick = 0;
float introTimer = 0;
char currentMenuSelection = 0;
SDL_RWops *hsFile = NULL;
char *pref_path = NULL;
    char hsStrPath[256];
extern int highScore;

void InitializePrefPath() {
    char *base_path = SDL_GetPrefPath("Enactivo", "Elevator Rescue");
    if (base_path) {
        pref_path = base_path;
        printf("Using pref path: %s\n",pref_path);
    } else {
        printf("Error: Couldn't find preference path.\n");
    }
}

// Methods
static void SetSDLIcon(SDL_Window* window)
{
    // these masks are needed to tell SDL_CreateRGBSurface(From)
    // to assume the data it gets is byte-wise RGB(A) data
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    int shift = (er_icon.bytes_per_pixel == 3) ? 8 : 0;
    rmask = 0xff000000 >> shift;
    gmask = 0x00ff0000 >> shift;
    bmask = 0x0000ff00 >> shift;
    amask = 0x000000ff >> shift;
#else // little endian, like x86
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = (er_icon.bytes_per_pixel == 3) ? 0 : 0xff000000;
#endif
    SDL_Surface* icon = SDL_CreateRGBSurfaceFrom((void*)er_icon.pixel_data, er_icon.width,
                        er_icon.height, er_icon.bytes_per_pixel*8, er_icon.bytes_per_pixel*er_icon.width,
                        rmask, gmask, bmask, amask);
    SDL_SetWindowIcon(window, icon);

    SDL_FreeSurface(icon);
}

void
init()
{
#ifdef __APPLE__
    char path[PATH_MAX];
    CFURLRef res = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
    CFURLGetFileSystemRepresentation(res, TRUE, (UInt8 *)path, PATH_MAX);
    CFRelease(res);
    chdir(path);
#endif


    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
        {
            printf( "SDL could not initialize! SDL_Error: %s\n",
                    SDL_GetError() );
            exit(-1);
        }
    else
        {
            //Create window
            window = SDL_CreateWindow( "Elevator Rescue",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       320*SCALING_FACTOR,
                                       192*SCALING_FACTOR,
                                       SDL_WINDOW_SHOWN );
            if( window == NULL )
                {
                    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
                }
            else
                {
                    SetSDLIcon(window);
                    initVideo();
                    initAudio();
                }
        }
    /*
     * Load the current high score. If there is none,
     * create a new file for it
     */
     InitializePrefPath();
    strcat(hsStrPath, pref_path);
    strcat(hsStrPath, "hs.dat");
    hsFile = SDL_RWFromFile(hsStrPath,"r+b");
    if (hsFile == NULL)
        {
            hsFile = SDL_RWFromFile(hsStrPath,"w+b");
            if (hsFile == NULL)
                {
                    printf("Error: Couldn't create high score file!!\n");
                    exit(-1);
                }
            highScore = 0;
            SDL_RWwrite(hsFile, &highScore,
                        sizeof(highScore), 1);
            SDL_RWclose(hsFile);
        }
    else
        {
            SDL_RWread(hsFile, &highScore,
                       sizeof(highScore), 1);
            SDL_RWclose(hsFile);
        }
}

void
shutdownGame()
{
    /* Write highscore */
    hsFile = SDL_RWFromFile(hsStrPath,"w+b");
    SDL_RWwrite(hsFile, &highScore,
                sizeof(highScore), 1);
    SDL_RWclose(hsFile);

    cleanupAudio();
    cleanUpVideo();
    cleanGameLogic();
    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();
    printf("Shuting down...\n");
}

int
main(int argc, char *argv[])
{
    init();
    loadAssets();
    loadAudioClips();
    playSound(AC_THEME);
    while (isGameRunning)
        {
            int thisTick = SDL_GetTicks();
            float dt = (float) (thisTick - lastTick);
            lastTick = thisTick;
            switch (currentAppScene)
                {
                case APPSCENE_INTRO:
                    introTimer += dt;
                    //Handle events on queue
                    while( SDL_PollEvent( &currentEvent ) != 0 )
                        {
                            //User requests quit
                            if( currentEvent.type == SDL_QUIT )
                                {
                                    isGameRunning = 0;
                                }
                            else if (currentEvent.type == SDL_KEYDOWN)
                                {
                                    currentAppScene = APPSCENE_MAINMENU;
                                }
                        }
                    if (introTimer > APPSCENE_INTRO_TIMER)
                        currentAppScene = APPSCENE_MAINMENU;
                    renderIntroScene();
                    break;
                case APPSCENE_MAINMENU:
                    while (SDL_PollEvent( &currentEvent ) != 0)
                        {
                            if (currentEvent.type == SDL_QUIT)
                                {
                                    isGameRunning = 0;
                                }
                            else if (currentEvent.type == SDL_KEYDOWN)
                                {
                                    switch(currentEvent.key.keysym.sym)
                                        {
                                        case SDLK_F1:
                                            currentAppScene = APPSCENE_CREDITS;
                                            break;
                                        case SDLK_RIGHT:
                                        case SDLK_DOWN:
                                        case SDLK_LEFT:
                                        case SDLK_UP:
                                            playSound(AC_MENU);
                                            currentMenuSelection = (currentMenuSelection == 0) ?1:0;
                                            break;
                                        case SDLK_RETURN:
                                            if (currentMenuSelection == 0)
                                                {
                                                    currentAppScene = APPSCENE_GAMEPLAY;
                                                    initGameLogic();
                                                }
                                            else
                                                isGameRunning = 0;
                                            break;
                                        }
                                }
                        }
                    renderSplashScreen();
                    break;
                case APPSCENE_GAMEPLAY:
                    //Handle events on queue
                    while( SDL_PollEvent( &currentEvent ) != 0 )
                        {
                            //User requests quit
                            if( currentEvent.type == SDL_QUIT )
                                {
                                    isGameRunning = 0;
                                }
                        }
                    handleGameInput(currentEvent);
                    update(dt);
                    render();
                    break;
                case APPSCENE_CREDITS:
                    while( SDL_PollEvent( &currentEvent ) != 0 )
                        {
                            if( currentEvent.type == SDL_QUIT )
                                {
                                    isGameRunning = 0;
                                }
                            else if (currentEvent.type == SDL_KEYDOWN)
                                {
                                    currentAppScene = APPSCENE_MAINMENU;
                                }
                        }
                    renderCredits();
                    break;
                }
        }
    shutdownGame();
    return 0;
}
