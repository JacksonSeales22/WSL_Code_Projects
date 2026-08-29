#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#define COLOR_MAX 10 //Maximum number of colors

enum color {FREE, WHITE, ORANGE, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, BABY_PINK, BLACK};

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
        SDL_DestroyTexture(textTexture);
        TTF_CloseFont(font);
        SDL_Quit();
        TTF_Quit();
    }

    void draw_block (int pX1, int pY1, int blockWidth, int blockHeight, enum color blockColor);
    void draw_text (int x, int y, const std::string &text, SDL_Color textColor);
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
    TTF_Font* font;
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    int screenWidth;
    int screenHeight;
    const Uint8* keyState;

};

//Initializes all SDL classes required to 'draw' the boardstate
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

    if (TTF_Init() == -1)
    {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    font = TTF_OpenFont("Nasa21.ttf", 24); 
    if (!font)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return -1;
    }
    
    return 0;
}

//Compares an enum to specific colors to render
static void setColor(SDL_Renderer* r, color c)
{
    switch (c)
    {
        case RED:     SDL_SetRenderDrawColor(r, 255,   0,   0, 255); break;
        case GREEN:   SDL_SetRenderDrawColor(r,   0, 255,   0, 255); break;
        case BLUE:    SDL_SetRenderDrawColor(r,   0,   0, 255, 255); break;
        case YELLOW:  SDL_SetRenderDrawColor(r, 255, 255,   0, 255); break;
        case ORANGE:  SDL_SetRenderDrawColor(r, 255, 165, 0, 0); break;
        case CYAN:    SDL_SetRenderDrawColor(r,   0, 255, 255, 255); break;
        case MAGENTA: SDL_SetRenderDrawColor(r, 255,   0, 255, 255); break;
        case BABY_PINK: SDL_SetRenderDrawColor(r, 244, 194, 194, 255); break;
        case BLACK:     SDL_SetRenderDrawColor(r, 0, 0, 0, 255); break;
        case WHITE:     SDL_SetRenderDrawColor(r, 255, 255, 255, 255);break;
        default:            SDL_SetRenderDrawColor(r, 255, 255, 255, 255); break;
    }
}

//Creates a texture for the text using the font and color, then renders it. Destroys the texture, since the score is re-rendered each turn
void Display::draw_text(int x, int y, const std::string &text, SDL_Color textColor)
{
    textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    if (!textSurface) return;

    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect;
    textRect.x = x;
    textRect.y = y;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    SDL_FreeSurface(textSurface);

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
}

//Draws a single block on the screen at the recieved pixel coordinates.
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