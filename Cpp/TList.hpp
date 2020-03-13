#pragma once
namespace tlists{
  //List setup
  template<typename...> struct List {};
  //Utils
  template<typename, typename> struct prepend;
  template<typename, typename> struct postpend;
  template<typename T, typename... Ts> struct prepend<T, List<Ts...>>{
    using type = List<T, Ts...>;
  };
  template<typename T, typename... Ts> struct postpend<List<Ts...>, T>{
    using type = List<Ts..., T>;
  };
  //length
  template<typename> struct length; //length :: [a] -> Int
  template<> struct length<List<>>{ //base case
    static constexpr auto value = 0;
  };
  template<typename T, typename... Ts> struct length<List<T, Ts...>>{ //recursive case
    static constexpr auto value = 1 + length<List<Ts...>>::value;
  };

  //sum
  template<typename> struct sum; //sum :: Num a => [a] -> a
  template<> struct sum<List<>>{ //base case
    static constexpr auto value = 0;
  };
  //sum of types is the sum of their sizes
  template<typename T, typename... Ts> struct sum<List<T, Ts...>>{ //recursive case
    static constexpr auto value = sizeof(T) + sum<List<Ts...>>::value;
  };

  //product
  template<typename> struct product; //product :: Num a => [a] -> a
  template<> struct product<List<>>{ //base case
    static constexpr auto value = 1;
  };
  template<typename T, typename... Ts> struct product<List<T, Ts...>>{ //recursive case
    static constexpr auto value = sizeof(T) * product<List<Ts...>>::value;
  };

  //min : returns the type of the smallest size in the list
  template<typename> struct min; //min :: Ord a => [a] -> a
  template<> struct min<List<>>{ //base case : empty list
    using type = void;
  };
  template<typename T> struct min<List<T>>{ //list of one type
    using type = T;
  };
  //returns the type of the smallest size
  template<typename T, typename... Ts> struct min<List<T, Ts...>>{ //recursive case
    using type = typename std::conditional<
    (sizeof(T) < sizeof(typename min<List<Ts...>>::type)),
    T,
    typename min<List<Ts...>>::type
    >::type;
  };

  //max : returns the type of the biggest size
  template<typename> struct max; //max :: Ord a => [a] -> a
  template<> struct max<List<>>{ //base case : empty list
    using type = void;
  };
  template<typename T> struct max<List<T>>{
    using type = T;
  };
  template<typename T, typename... Ts> struct max<List<T, Ts...>>{ //recursive case
    using type = typename std::conditional<
    (sizeof(T) > sizeof(typename max<List<Ts...>>::type)),
    T,
    typename max<List<Ts...>>::type
    >::type;
  };
  
  //takeWhileHelper
  template<template<typename> typename, typename, bool, typename>
  struct takeWhileHelper;
  template<template<typename> typename P, typename Prev>
  struct takeWhileHelper<P, List<>, false, Prev>{ //P is false, empty list
    using type = List<>;
  };
  template<template<typename> typename P, typename Prev>
  struct takeWhileHelper<P, List<>, true, Prev>{ //P is true, empty list
    //using type = List<Prev>;
    using type = List<>;
  };
  template<template<typename> typename P, typename T, typename... Ts, typename Prev>
  struct takeWhileHelper<P, List<T, Ts...>, true, Prev> { //P is true, recursive case
    using type = typename prepend<Prev, typename takeWhileHelper<P, List<Ts...>, P<T>::value, T>::type>::type;
  };
  template<template<typename> typename P, typename T, typename... Ts, typename Prev>
  struct takeWhileHelper<P, List<T, Ts...>, false, Prev>{ //P is false : stop
    using type = List<>;
  };
  //takeWhile
  template<template<typename> typename, typename>
  struct takeWhile; //takeWhile :: (a -> Bool) -> [a] -> [a]
  template<template<typename> typename P> struct takeWhile<P, List<>>{ //base case : empty list
    using type = List<>;
  };
  template<template<typename> typename P, typename T, typename... Ts>
  struct takeWhile<P, List<T, Ts...>>{ //recursive case
    using type = typename takeWhileHelper<P, List<Ts...>, P<T>::value, T>::type;
  };
}
