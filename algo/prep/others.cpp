#include "others.h"

#include "algo/basic/max_heap.h"

namespace ps::algo {

std::vector<std::string> permutations(const std::string& str)
{
    if (str.empty()) {
        return std::vector<std::string>{};
    }
    else if (str.size() == 1) {
        return std::vector<std::string>{1, str};
    }

    std::vector<std::string> words;

    std::string first_char = str.substr(0, 1);
    std::vector<std::string> word_list = permutations(str.substr(1));

    for (auto& word : word_list) {
        size_t n = word.size();
        for (size_t i = 0; i <= n; ++i) {
            words.push_back(word.substr(0, i) + first_char + word.substr(i));
        }
    }

    return words;
}

int64_t skyline_area(const std::vector<Building>& buildings)
{
    struct LocHeight
    {
        int32_t x;
        int32_t height;
    };
    std::vector<LocHeight> loc_heights;

    struct HeapElement
    {
        int32_t height;
        int32_t building_end;
        bool operator>(const HeapElement& other) const
        {
            if (height > other.height) {
                return true;
            }
            if (height < other.height) {
                return false;
            }
            return building_end > other.building_end;
        }
    };
    ps::algo::MaxHeap<HeapElement> max_heap;

    int32_t current_height = 0;
    for (size_t i = 0, n = buildings.size(); i < n || !max_heap.is_empty();) {
        int current_x;
        if (max_heap.is_empty() || (i < n && buildings[i].start < max_heap.top().building_end)) {
            current_x = buildings[i].start;
            while (i < n && buildings[i].start == current_x) {
                max_heap.push(HeapElement{buildings[i].height, buildings[i].end});
                ++i;
            }
        }
        else {
            current_x = max_heap.top().building_end;
        }

        while (!max_heap.is_empty() && max_heap.top().building_end <= current_x) {
            max_heap.pop();
        }

        const auto new_height = max_heap.is_empty() ? 0 : max_heap.top().height;
        if (current_height != new_height) {
            current_height = new_height;
            loc_heights.push_back(LocHeight{current_x, current_height});
        }
    }

    int64_t area = 0;
    for (size_t i = 1; i < loc_heights.size(); ++i) {
        area += loc_heights[i - 1].height * (loc_heights[i].x - loc_heights[i - 1].x);
    }
    return area;
}

} // namespace ps::algo
