#ifndef PERFECT_CACHE_H
#define PERFECT_CACHE_H

#include <assert.h>
#include <iostream>
#include <list>
#include <unordered_map>
#include <map>
#include <functional>
#include <set>

template <typename KeyT = int>
struct perfect_cache_t {
private:
    size_t capacity_;

    std::list<KeyT> input_;
    std::unordered_set<KeyT> current_cache_;

    bool full() const {
        return capacity_ == current_cache_.size();
    }
public:
    bool lookup_update(KeyT key) {
        std::cout << "now " << key << std::endl;

        auto hit = current_cache_.find(key);
    
        if (hit == current_cache_.end()) {
            if (full()) {
                std::unordered_set<KeyT> candidates_to_erase(current_cache_);

                for(KeyT next_key : input_) {
                    if(candidates_to_erase.size() == 1) {
                        int erased = *(candidates_to_erase.begin());

                        std::cout << "erased: " << erased << std::endl;

                        current_cache_.erase(erased);
                        break;
                    }

                    std::cout << "erasing from candidates: " << next_key << std::endl;

                    candidates_to_erase.erase(next_key);
                }
            }

            current_cache_.insert(key);

            std::cout << "miss" << std::endl;

            return false;
        }

        input_.pop_front();

        std::cout << "hit" << std::endl;

        return true;
    }

    perfect_cache_t(size_t capacity, std::list<int> input) : 
        capacity_(capacity),
        input_(input) 
        {};
};

#endif // PERFECT_CACHE_H