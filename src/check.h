#ifndef CHECK_H
#define CHECK_H
#include "common.h"

/**
 * @brief check for vector type
 * @result false
**/
template<typename T>
struct is_vector : std::false_type {};

/**
 * @brief check for vector type
 * @result true
**/
template<typename... Args>
struct is_vector<std::vector<Args...>> : std::true_type {};

/**
 * @brief check for list type
 * @result false
**/
template<typename T>
struct is_list : std::false_type {};

/**
 * @brief check for list type
 * @result true
**/
template<typename... Args>
struct is_list<std::list<Args...>> : std::true_type {};

/**
 * @brief check for tuple type
 * @result false
**/
template<typename T>
struct is_tuple : std::false_type {};

/**
 * @brief check for tuple type
 * @result true
**/
template<typename... Args>
struct is_tuple<std::tuple<Args...>> : std::true_type {};

#endif // CHECK_H
