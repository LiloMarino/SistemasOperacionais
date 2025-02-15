#include "replacement_policy.hpp"
#include <limits>

int fifo_policy(std::queue<int> &fifo_queue, std::unordered_map<int, int> &)
{
    if (fifo_queue.empty())
    {
        return -1;
    }

    int victim = fifo_queue.front();
    fifo_queue.pop();
    return victim;
}

int lru_policy(std::queue<int> &, std::unordered_map<int, int> &access_counters)
{
    if (access_counters.empty())
    {
        return -1;
    }

    int min_page = -1;
    int min_time = std::numeric_limits<int>::max();

    for (const auto &[page, time] : access_counters)
    {
        if (time < min_time)
        {
            min_time = time;
            min_page = page;
        }
    }

    return min_page;
}
