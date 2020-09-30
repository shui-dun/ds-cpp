#include <chrono>
#include <ostream>

class Timer {
private:
    std::ostream& out;
    using time_point = std::chrono::high_resolution_clock::time_point;
    using duration = std::chrono::high_resolution_clock::duration;
    using ms_duration =
        std::chrono::duration<double, std::chrono::milliseconds::period>;
    time_point beg;
    std::chrono::high_resolution_clock hires_clock;

public:
    constexpr Timer(std::ostream& _out = std::cout) : out(_out), beg(), hires_clock() {}

    inline void start() {
        beg = hires_clock.now();
    }

    inline void end(const char* label = "default") {
        auto time_end = hires_clock.now();
        out << label << ": " << (ms_duration(time_end - beg)).count() << "ms\n";
    }
};