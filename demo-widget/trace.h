#pragma once
#ifndef TRACE_H
#define TRACE_H

#include <iostream>

namespace sdl {

void print_timestamp();

template<typename T>
static void trace_delim(T && value) {
    std::cout << value << std::endl;
}
template<typename T, typename... Ts>
static void trace_delim(T && value, Ts&&... params) {
    std::cout << value << '|';
    trace_delim(std::forward<Ts>(params)...);
}
template<typename T, typename... Ts>
static void trace_delim_with_timestamp(T && value, Ts&&... params) {
    print_timestamp();
    trace_delim(std::forward<T>(value), std::forward<Ts>(params)...);
}

}

#define SDL_TRACE_ARGS_IMPL(...)	sdl::trace_delim_with_timestamp(__VA_ARGS__)
#define SDL_TRACE_ARGS(...)			SDL_TRACE_ARGS_IMPL(__FUNCTION__, __VA_ARGS__)

#endif // TRACE_H
