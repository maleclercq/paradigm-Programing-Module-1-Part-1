#pragma once

#include <iostream>
#include <string>
#include "VList.hpp"

namespace vlists
{

template<typename> struct convert_init;
template<typename> struct convert_last;

template<auto... Xs> struct convert_init<VList<Xs...>>
{
  static std::string to_string()
  {
    if constexpr (sizeof... (Xs) > 0)
      return std::to_string(head<VList<Xs...>>::value) +
             ", " +
             convert_init<typename tail<VList<Xs...>>::type>::to_string();
    else
      return "";
  }
};

template<auto... Xs> struct convert_last<VList<Xs...>>
{
  static std::string to_string()
  {
    if constexpr (sizeof... (Xs) > 0)
      return std::to_string(last<VList<Xs...>>::value);
    else
      return "";
  }
};

template<auto... Xs>
constexpr std::string to_string(VList<Xs...> l)
{
  return "[" +
         convert_init<typename init<VList<Xs...>>::type>::to_string() +
         convert_last<VList<Xs...>>::to_string() +
         "]";
}

}//namespace vlists

namespace std
{

template<auto... Xs>
std::ostream& operator << (std::ostream& out, vlists::VList<Xs...> l)
{
  out << to_string(l);
  return out;
}

}//namespace std
