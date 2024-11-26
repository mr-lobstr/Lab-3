#ifndef STRUCTS_SERIALIZATION_H_GUARD
#define STRUCTS_SERIALIZATION_H_GUARD

#include <string>
#include <tuple>
#include "nlohmann/json.hpp"
#include "data_struct/dynamic_array.h"
#include "data_struct/hash_table.h"
#include "data_struct/string_view.h"

using json = nlohmann::json;
namespace ds = data_struct;


template <typename Key, typename Value, typename Hash>
inline void to_json(json& j, ds::HashTable<Key, Value, Hash> const& table) {
    j = json::array();
    size_t i = 0;

    for (auto& [key, value] : table) {
        j[i][key] = value;
        ++i;
    }
}


template <typename T>
void from_json(const json& j, std::string const& name, ds::DynamicArray<T>& arr) {
    for (auto& el : j[name]) {
        arr.push_back (el);
    }
}


template <typename Ds>
json& serialize (json& j, std::string const& name, Ds const& ds) {
    to_json (j[name], ds);
    return j;
}


template <size_t ind, typename Tuple>
json& serialize_all_ (json& j, ds::DynamicArray<StringView> const& names, Tuple const& tup) {
    auto structName = names[ind];
    auto& structRef = std::get<ind>(tup);

    serialize (j, structName, structRef);

    if constexpr (ind != 0) {
        return serialize_all_<ind-1> (j, names, tup);
    } else {
        return j;
    }
}


template <typename... Structs>
json& serialize_all (json& j, std::string const& names, Structs&&... structs) {
    auto haveNotSpaces = join_views(split_into_words (names), "");
    auto splits = split (haveNotSpaces, ',');

    std::tuple<Structs&&...> tup (std::forward<Structs>(structs)...);
    constexpr size_t size = std::tuple_size<decltype(tup)>::value;
    
    serialize_all_<size-1>(j, splits, tup);

    return j;
}

#define Serialize(j, ds) serialize (j, #ds, ds)
#define SerializeAll(j, ...) serialize_all (j, #__VA_ARGS__, __VA_ARGS__)

#endif