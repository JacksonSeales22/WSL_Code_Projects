#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>

#define COLOR_MAX 10 //Maximum number of colors

enum color {FREE, WHITE, BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, BABY_PINK};

class Display
{
    public:
    Display()
    : window(nullptr), renderer(nullptr),
        screenWidth(640), screenHeight(600), keyState(nullptr)
    {}

    ~Display()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void draw_block (int pX1, int pY1, int blockWidth, int blockHeight, enum color blockColor);
    void clear_screen ();
    int get_screen_height ();
    int init_window ();
    int poll_key ();
    int get_key ();
    int key_press (int keyPress);
    void update_screen ();

    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;
    const Uint8* keyState;

};


int Display::init_window()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return -1;

    window = SDL_CreateWindow("Tetris",
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                screenWidth, screenHeight, 0);
    if (!window) return -1;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return -1;

    keyState = SDL_GetKeyboardState(nullptr);
    return 0;
}

static void setColor(SDL_Renderer* r, color c)
{
    switch (c)
    {
        case RED:     SDL_SetRenderDrawColor(r, 255,   0,   0, 255); break;
        case GREEN:   SDL_SetRenderDrawColor(r,   0, 255,   0, 255); break;
        case BLUE:    SDL_SetRenderDrawColor(r,   0,   0, 255, 255); break;
        case YELLOW:  SDL_SetRenderDrawColor(r, 255, 255,   0, 255); break;
        case CYAN:    SDL_SetRenderDrawColor(r,   0, 255, 255, 255); break;
        case MAGENTA: SDL_SetRenderDrawColor(r, 255,   0, 255, 255); break;
        case BABY_PINK: SDL_SetRenderDrawColor(r, 244, 194, 194, 255); break;
        case BLACK:
        case WHITE:
        default:            SDL_SetRenderDrawColor(r, 255, 255, 255, 255); break;
    }
}

void Display::draw_block(int x, int y, int width, int height, enum color blockColor)
{
    setColor(renderer, blockColor);
    SDL_Rect rect {x, y, width, height}; //SDL2 rects are x, y, w, h
    SDL_RenderFillRect(renderer, &rect);
}

void Display::clear_screen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

int Display::get_screen_height()
{
    return screenHeight;
}

void Display::update_screen() {SDL_RenderPresent(renderer);}

int Display::poll_key()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            exit(0); //handle window close
        }
        if (event.type == SDL_KEYDOWN && !event.key.repeat)
        {
            return event.key.keysym.sym;
        }
    }
    return -1;
}

int Display::get_key()
{
    SDL_Event event;
    while (true)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
            return event.key.keysym.sym;
    }
}

int Display::key_press(int pKey)
{
    SDL_PumpEvents();
    return keyState[SDL_GetScancodeFromKey(pKey)];
}

#endif //DISPLAY_H