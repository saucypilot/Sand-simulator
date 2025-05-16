#include <SDL.h>
#include <iostream>
#include <vector>

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 800;
const int cellSize = 3; // Each "sand grain" is a 3x3 pixel square

const int gridWidth = SCREEN_WIDTH / cellSize;
const int gridHeight = SCREEN_HEIGHT / cellSize;

// Define sand grid cell states
enum CellType { EMPTY, SAND };

// Main entry point
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Grid-Based Sand Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // The 2D sand grid
    std::vector<std::vector<CellType>> grid(gridHeight, std::vector<CellType>(gridWidth, EMPTY));

    bool quit = false;
    bool mouseHeld = false;
    SDL_Event event;

    while (!quit) {
        // --- HANDLE EVENTS ---
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                mouseHeld = true;
            }
            if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
                mouseHeld = false;
            }
        }

        // --- SPAWN SAND WHERE MOUSE IS HELD ---
        if (mouseHeld) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            int gx = mouseX / cellSize;
            int gy = mouseY / cellSize;
            // You can spawn a "cluster" for a thicker stream of sand:
            for (int oy = -1; oy <= 1; ++oy) {
                for (int ox = -1; ox <= 1; ++ox) {
                    int sx = gx + ox;
                    int sy = gy + oy;
                    if (sx >= 0 && sx < gridWidth && sy >= 0 && sy < gridHeight) {
                        grid[sy][sx] = SAND;
                    }
                }
            }
        }

        // --- SAND PHYSICS: Bottom-up update ---
        for (int y = gridHeight - 2; y >= 0; --y) {
            for (int x = 0; x < gridWidth; ++x) {
                if (grid[y][x] == SAND) {
                    // Move down if possible
                    if (grid[y + 1][x] == EMPTY) {
                        grid[y + 1][x] = SAND;
                        grid[y][x] = EMPTY;
                    }
                    // Or diagonally down-left
                    else if (x > 0 && grid[y + 1][x - 1] == EMPTY) {
                        grid[y + 1][x - 1] = SAND;
                        grid[y][x] = EMPTY;
                    }
                    // Or diagonally down-right
                    else if (x < gridWidth - 1 && grid[y + 1][x + 1] == EMPTY) {
                        grid[y + 1][x + 1] = SAND;
                        grid[y][x] = EMPTY;
                    }
                }
            }
        }

        // --- RENDERING ---
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 194, 178, 128, 255); // Sand color (light brown)
        for (int y = 0; y < gridHeight; ++y) {
            for (int x = 0; x < gridWidth; ++x) {
                if (grid[y][x] == SAND) {
                    SDL_Rect rect = { x * cellSize, y * cellSize, cellSize, cellSize };
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
