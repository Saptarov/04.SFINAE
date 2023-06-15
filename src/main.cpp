#include "check.h"

template<typename T>
typename std::enable_if_t<std::is_integral_v<T>, void>
print_ip(T v) {
    if constexpr(sizeof(T) == 1) {
        uint8_t* byte = (uint8_t*)&v;
        std::cout << (int)*byte << std::endl;
    }
    else if constexpr(sizeof(T) == 2) {
        uint8_t* byte = (uint8_t*)&v;
        std::cout << (int)byte[1] << "." << (int)byte[0] << std::endl;
    }
    else if constexpr(sizeof(T) == 4) {
        uint8_t* byte = (uint8_t*)&v;
        std::cout << (int)byte[3] << "." << (int)byte[2] << "." << (int)byte[1] << "." << (int)byte[0] << std::endl;
    }
    else if constexpr(sizeof(T) == 8) {
        uint8_t* byte = (uint8_t*)&v;
        std::cout << (int)byte[7] << "." << (int)byte[6] << "." << (int)byte[5] << "." << (int)byte[4]
                                  << "." << (int)byte[3] << "." << (int)byte[2] << "." << (int)byte[1]
                                  << "." << (int)byte[0] << std::endl;
    }
}

template<typename T>
typename std::enable_if<std::is_same<decltype(std::declval<T>().length()), std::string>::value, void>
print_ip(T v) {
    std::cout << v.c_str() << std::endl;
}

template<class TupType, size_t... I>
void print(const TupType& _tup, std::index_sequence<I...>)
{
    (..., (std::cout << (I == 0? "" : ".") << std::get<I>(_tup)));
}

template<class... T>
void print (const std::tuple<T...>& _tup)
{
    print(_tup, std::make_index_sequence<sizeof...(T)>());
}

template<typename T>
typename std::enable_if<is_vector<T>::value, void>::type print_ip(T t)
{
    std::for_each(t.begin(), t.end(), [&](auto&& elem) {
       std::cout <<elem << ".";
     } );
    std::cout << std::endl;
}

template<typename T>
typename std::enable_if<is_list<T>::value, void>::type print_ip(T t)
{
    std::for_each(t.begin(), t.end(), [&](auto&& elem) {
       std::cout <<elem << ".";
     } );
    std::cout << std::endl;
}

template<typename T>
typename std::enable_if<is_tuple<T>::value, void>::type print_ip(T t)
{
    print(t);
    std::cout << std::endl;
}

int main () {
    print_ip(int8_t{-1});
    print_ip(int16_t{0});
    print_ip(int32_t{2130706433});
    print_ip(int64_t{8875824491850138409});
    print_ip(std::string{"Hello, World!"});
    print_ip(std::vector<int>{100, 200, 300, 400});
    print_ip(std::list<int>{400, 300, 200, 100});
    print_ip(std::make_tuple(123, 456, 789, 0));
    return 0;
}
