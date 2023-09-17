#include "cache/cache.h"
#include "cache/perfect_cache.h"

int main(int argc, char **argv) {
    size_t cache_size = 0, num_elems = 0;

    std::cin >> cache_size >> num_elems;

    cache_t<int> cache(cache_size);
    std::list<int> input;

    int hits = 0;

    for (int i = 0; i < num_elems; ++i) {
        int id = 0;

        std::cin >> id;

        assert(std::cin.good());

        input.push_back(id);

        if (cache.lookup_update(id, 0)) hits += 1;
    }

    std::cout << hits << "\n";

    perfect_cache_t<int> perfect_cache(cache_size, input);

    hits = 0;

    for(int key : input) {
        if (perfect_cache.lookup_update(key)) hits += 1;
    }

    std::cout << hits << "\n";
}