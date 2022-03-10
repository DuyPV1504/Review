#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Texture Test";

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture* loadTexture( string path, SDL_Renderer* renderer );

int main(int argc, char *argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    SDL_Texture* background = loadTexture("background.jpg", renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);

    SDL_RenderPresent( renderer );
    waitUntilKeyPressed();

    SDL_Texture* Mon = loadTexture("mon.png", renderer);
    SDL_Rect MonRect;
    SDL_QueryTexture(Mon, NULL, NULL, &MonRect.w, &MonRect.h);
    MonRect.x = 290;
    MonRect.y = 350;
    MonRect.w = MonRect.w/5;
    MonRect.h = MonRect.h/5;
    SDL_RenderCopy( renderer, Mon, NULL, &MonRect );

    SDL_Texture* Mouse = loadTexture("chuot.png", renderer);
    SDL_Rect MouseRect;
    SDL_QueryTexture(Mouse, NULL, NULL, &MouseRect.w, &MouseRect.h);
    MouseRect.x = 450;
    MouseRect.y = 500;
    MouseRect.w = MouseRect.w/4;
    MouseRect.h = MouseRect.h/4;
    SDL_RenderCopy( renderer, Mouse, NULL, &MouseRect );

    SDL_Texture* dorayaki = loadTexture("dorayaki.png", renderer);
    SDL_Rect dorayakiRect;
    SDL_QueryTexture(dorayaki, NULL, NULL, &dorayakiRect.w, &dorayakiRect.h);
    dorayakiRect.x = 400;
    dorayakiRect.y = 100;
    dorayakiRect.w = dorayakiRect.w/10;
    dorayakiRect.h = dorayakiRect.h/10;
    SDL_RenderCopy( renderer, dorayaki, NULL, &dorayakiRect );

    SDL_RenderPresent( renderer );
    waitUntilKeyPressed();

    //Free loaded image
    SDL_DestroyTexture( Mon );
    Mon = NULL;
    SDL_DestroyTexture( dorayaki );
    dorayaki = NULL;
    SDL_DestroyTexture( Mouse );
    Mouse = NULL;
    SDL_DestroyTexture( background );
    background = NULL;

    quitSDL(window, renderer);
    return 0;
}

SDL_Texture* loadTexture( string path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == nullptr )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
      // SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
