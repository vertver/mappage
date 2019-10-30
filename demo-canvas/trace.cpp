#include <time.h>

#include <iostream>

namespace {
bool safe_gmtime(struct tm & dest, const time_t value) {
#if defined(WIN32)
    const errno_t err = ::gmtime_s(&dest, &value);
    return !err;
#else
    struct tm * ptm = ::gmtime_r(&value, &dest);
    return ptm != nullptr;
#endif
}
}

namespace sdl {
void print_timestamp() {
    timespec ts;
    if (timespec_get(&ts, TIME_UTC)) {
        struct tm d;
        if (safe_gmtime(d, ts.tv_sec)) {
            char buf[40];
            snprintf(buf, sizeof(buf), "%02d:%02d:%02d.%03ld",
                     d.tm_hour, d.tm_min, d.tm_sec, (ts.tv_nsec / 1000000L));
            std::cout << buf << "> ";
        }
    }
}
}
