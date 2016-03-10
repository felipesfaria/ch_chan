//
// Created by erick on 08/03/16.
//

#ifndef CH_CHAN_SDL_H
#define CH_CHAN_SDL_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define USE_SDL 0

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

typedef unsigned int uint;
typedef char uint8;

#define amask 0xff000000
#define rmask 0x00ff0000
#define gmask 0x0000ff00
#define bmask 0x000000ff
#define LINE_THICKNESS 2

class SDL {
private:
    int window_height;
    int window_width;
    SDL_Window* window;
    SDL_Renderer* renderer;
    double offset_x;
    double offset_y;
    double scale_x;
    double scale_y;

    void draw_point_at(Point_2 point);
public:
    SDL(int window_width, int window_height, Point_2 top_left, Point_2 bottom_write);
    ~SDL();
    void draw_points_to_buffer(int count, Point_2 points[]);
    void draw_hull_to_buffer(int count, Point_2 hull[]);
    void draw_hull_to_buffer(const std::vector<Point_2> &hull);

    void draw_line_between(Point_2 begin, Point_2 end, uint8 r, uint8 g, uint8 b);
    void clear_buffer();

    void fill_buffer_color(uint8 r, uint8 g, uint8 b);
    void display_buffer();

    void wait_for_msecs(int msecs);

    void wait_for_close();
};



#endif //CH_CHAN_SDL_H
