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

  //min1
  template<typename> struct min1; //min :: Ord a => [a] -> a
  template<> struct min1<List<>>{ //base case : empty list
    static constexpr auto value = 0;
  };
  template<typename T> struct min1<List<T>>{ //list of one type
    static constexpr auto value = sizeof(T);
  };
  //returns the size of the smallest type
  template<typename T, typename... Ts> struct min1<List<T, Ts...>>{ //recursive case
    static constexpr auto value = (sizeof(T) < min1<List<Ts...>>::value) ? sizeof(T) : min1<List<Ts...>>::value;
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
}