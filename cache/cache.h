#ifndef CACHE_H
#define CACHE_H

#include <assert.h>
#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <functional>
#include <set>

template <typename T, typename KeyT = int>
struct cache_t {
private:
    size_t capacity_;

    std::unordered_map<KeyT, int> freqs_;

    bool values_frequency_compare(const KeyT& key1, const KeyT& key2) const {
        return freqs_[key1] < freqs_[key2];
    }

    using freq_comp_t = std::function<bool(const KeyT&, const KeyT&)>;
    std::map<KeyT, T, freq_comp_t> values_;

    bool full() const {
        return capacity_ == freqs_.size();
    }

public:
    bool lookup_update(KeyT key, T value) {
        auto hit = freqs_.find(key);
    
        if (hit == freqs_.end()) {
            if (full()) {
                auto least_frequent = values_.begin()->first;

                values_.erase(least_frequent);
                freqs_.erase(least_frequent);
            }

            freqs_[key] = 0;
            values_[key] = value;
            return false;
        }

        freqs_[key]++;

        return true;
    }

    cache_t(size_t capacity) : 
        capacity_(capacity), 
        values_(
            [this](const KeyT& key1, const KeyT& key2) {
                return freqs_.at(key1) < freqs_.at(key2);
            }
        )
        {}
};

#endif // CACHE_H