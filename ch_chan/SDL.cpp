//
// Created by erick on 08/03/16.
//

#include "SDL.h"

void my_assert(bool condition, char* message, ...) {
    va_list args_list;
    va_start(args_list, message);

    if(!condition) {
        vfprintf(stderr, message, args_list);
        // *((int*)NULL) = 0;
        va_end(args_list);
        exit(1);
    }
    va_end(args_list);
}

void SDL::wait_for_msecs(int msecs) {
    SDL_Delay(msecs);
}

void SDL::wait_for_close() {
    SDL_Event event;

    while (1) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                return;
            }
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE) return;
            }
        }
    }
}

SDL::SDL(int window_width, int window_height, Point_2 top_left, Point_2 bottom_write) {
    this->window_height = window_height;
    this->window_width = window_width;

    bool init_status = SDL_Init(SDL_INIT_VIDEO) >= 0;
    my_assert(init_status, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

    this->window = SDL_CreateWindow( "Convex Hull",
                                     SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                     window_width, window_height, SDL_WINDOW_SHOWN);
    my_assert(this->window != NULL, "Window could not be created! SDL_Error: %s\n", SDL_GetError());

    this->renderer = SDL_CreateRenderer(this->window, -1, NULL);

    my_assert(this->renderer != NULL, "Create Renderer failed: %s\n", SDL_GetError());

    this->offset_x = -top_left.x();
    this->offset_y = -top_left.y();

    double delta_x = bottom_write.x() - top_left.x();
    double delta_y = bottom_write.y() - top_left.y();

    this->scale_x = (double) window_width / delta_x;
    this->scale_y = (double) window_height / delta_y;
}

SDL::~SDL() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void SDL::fill_buffer_color(uint8 r, uint8 g, uint8 b) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, 255);
    SDL_RenderClear(this->renderer);
}

void SDL::clear_buffer() {
    this->fill_buffer_color(255, 255, 255);
}

void SDL::display_buffer() {
    SDL_RenderPresent(this->renderer);
}

void SDL::draw_point_at(Point_2 point) {
    int x = (int)((point.x() + offset_x) * scale_x);
    int y = this->window_height - (int)((point.y() + offset_y) * scale_y);

    circleRGBA(this->renderer, x, y, 2, 0, 0, 255, 255);
}

void SDL::draw_line_between(Point_2 begin, Point_2 end, uint8 r, uint8 g, uint8 b) {
    int x_begin = (int)((begin.x() + offset_x) * scale_x);
    int y_begin = this->window_height - (int)((begin.y() + offset_y) * scale_y);

    int x_end = (int)((end.x() + offset_x) * scale_x);
    int y_end = this->window_height - (int)((end.y() + offset_y) * scale_y);

    thickLineRGBA(renderer, x_begin, y_begin, x_end,  y_end, LINE_THICKNESS, r, g, b, 255);
}

void SDL::draw_points_to_buffer(int count, Point_2 points[]) {
    for(uint i = 0; i < count; i++) {
        this->draw_point_at(points[i]);
    }
}

void SDL::draw_hull_to_buffer(int count, Point_2 hull[]) {
    for(uint i = 0; i < count - 1; i++) {
        this->draw_line_between(hull[i], hull[i + 1],255, 0, 0);
        this->display_buffer();
        this->wait_for_msecs(1000);
    }
    this->draw_line_between(hull[count - 1], hull[0], 255, 0, 0);
}

void SDL::draw_hull_to_buffer(const std::vector<Point_2> &hull) {
    for(uint i = 0; i < hull.size() - 1; i++) {
        this->draw_line_between(hull[i], hull[i + 1],255, 0, 0);
        this->display_buffer();
    }
    this->draw_line_between(hull[hull.size() - 1], hull[0], 255, 0, 0);
}
