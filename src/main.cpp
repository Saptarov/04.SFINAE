#include "check.h"

template<typename T>
typename std::enable_if_t<std::is_integral_v<T>, void>
print_ip(T v) {
    std::reverse_iterator<uint8_t*> rfirst((uint8_t*)&v + sizeof(T));
    std::reverse_iterator<uint8_t*> rend((uint8_t*)&v);
    std::for_each(rfirst, rend, [](uint8_t& vv){
        std::cout << (int)vv << ".";
    });
    std::cout << std::endl;
}

template<typename T, decltype (std::is_same_v<decltype(std::declval<T>().length()), T>) = 0>
void print_ip(T v) {
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
typename std::enable_if<is_vector<T>::value || is_list<T>::value, void>::type print_ip(T t)
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
