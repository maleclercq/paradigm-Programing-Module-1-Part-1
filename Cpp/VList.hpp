#pragma once

#include <cuchar>

#include "VListSetup.hpp"

namespace vlists
{

//Forward Declarations*********************************************************

    template<typename> struct null;//null :: [a] -> Bool
    template<typename> struct head;//head :: [a] -> a
    template<typename> struct last;

    template<typename> struct sum;
    template<typename> struct and_list;
    template<typename> struct or_list;
    template<typename, template<auto> typename> struct all;
    template<typename, template<auto> typename> struct any;
    template<typename> struct product;
    template<typename> struct foldr;
    template<typename> struct foldrl;
    template<typename, template<auto> typename> struct dropWhile;
    template<typename, template<auto> typename, bool , auto> struct dropWhileHelper;
    template<typename, template<auto> typename> struct takeWhile;
    template<typename, template<auto> typename, bool, auto > struct takeWhileHelper;
    template<typename, auto> struct elem;
    template<typename> struct length;
    template<typename> struct min;
    template<typename> struct max;
    template<typename,std::size_t> struct drop;
    template<typename,std::size_t,bool> struct dropHelper;

    template<typename> struct tail;//tail :: [a] -> [a]
    template<typename> struct init;//init :: [a] -> [a]

//Definitions******************************************************************

    template<> struct null<List<>>//null []
    {static constexpr auto value = true;};//= true

    template<auto X, auto... Xs> struct null<List<X, Xs...>>//null (x: xs)
{static constexpr auto value = false;};//= false

//Project***********************************************************************

template<>
struct sum<List<>>
{
    static constexpr auto value = 0;
};

template<auto X, auto... Xs>
struct sum< List<X, Xs...> >
{
    static constexpr auto value =X + sum<List<Xs...>>::value;
//    using type = typename prepend<X, typename init<List<Xs...>>::type>::type;
};

//*****************************************************************************

template<>
struct and_list<List<>>
{
    static constexpr auto value = true;
};

template<auto X, auto... Xs>
struct and_list<List<X,Xs...>>
{
    static constexpr auto value = X & and_list<List<Xs...>>::value;
};

//*****************************************************************************

template<>
struct or_list<List<>>
{
    static constexpr auto value = true;
};

template<auto X, auto... Xs>
struct or_list<List<X,Xs...>>
{
    static constexpr auto value = X || or_list<List<Xs...>>::value;
};

template<auto X>
struct or_list<List<X>>
{
    static constexpr auto value = X;
};
//******************************************************************************

template<template<auto> typename P>
struct dropWhile<List<>,P>{
    using type = List<>;
};

template<auto X,auto... Xs, template<auto> typename P>
struct dropWhile<List<X,Xs...>,P>{
    using type = typename dropWhileHelper<List<Xs...>,P,P<X>::value,X>::type;
};

template<auto X,auto... Xs,template<auto> typename P,auto prev>
struct dropWhileHelper<List<X,Xs...>,P,true,prev>{
    using type = typename dropWhileHelper<List<Xs...>,P,P<X>::value,X>::type;
};

template<auto X,auto... Xs,template<auto> typename P,auto prev>
struct dropWhileHelper<List<X,Xs...>,P,false,prev>{
    using type = typename prepend<prev,List<X,Xs...>>::type;
};

template<template<auto> typename P,auto prev>
struct dropWhileHelper<List<>,P,false,prev>{
    using type = List<prev>;
};

template<template<auto> typename P,auto prev>
struct dropWhileHelper<List<>,P,true,prev>{
    using type = List<>;
};
//*****************************************************************************

template<template<auto> typename P>
struct takeWhile<List<>,P>{
    using type = List<>;
};


template<auto X,auto... Xs, template<auto> typename P>
struct takeWhile<List<X,Xs...>,P>{
    using type = typename takeWhileHelper<List<Xs...>,P,P<X>::value,X>::type;
};

template<auto X,auto... Xs,template<auto> typename P,auto prev>
struct takeWhileHelper<List<X,Xs...>,P,true,prev>{
    using type = typename prepend<prev, typename takeWhileHelper<List<Xs...>,P,P<X>::value,X>::type>::type;
};

template<auto X,auto... Xs,template<auto> typename P,auto prev>
struct takeWhileHelper<List<X,Xs...>,P,false,prev>{
    using type = List<>;
};

template<template<auto> typename P,auto prev>
struct takeWhileHelper<List<>,P,false,prev>{
    using type = List<>;
};

template<template<auto> typename P,auto prev>
struct takeWhileHelper<List<>,P,true,prev>{
    using type = List<prev>;
};

//*****************************************************************************

template<auto X,auto... Xs,auto e>
struct elem<List<X,Xs...>,e>{
    static constexpr auto value = (e==X) ? true : elem<List<Xs...>,e>::value;
};

template<auto e>
struct elem<List<>,e>{
    static constexpr auto value = false;
};

//*****************************************************************************

template<auto X,auto... Xs>
struct length<List<X,Xs...>>{
    static constexpr auto value = 1+length<List<Xs...>>::value;
};

template<>
struct length<List<>>{
    static constexpr auto value = 0;
};

//*****************************************************************************

template<auto X,auto... Xs>
struct min<List<X,Xs...>>{
    static constexpr auto value = (X < min<List<Xs...>>::value) ? X : min<List<Xs...>>::value;
};

template<auto X>
struct min<List<X>>{
    static constexpr auto value = X;
};

template<>
struct min<List<>>{
    static constexpr auto value = 0;
};

//*****************************************************************************

template<auto X,auto... Xs>
struct max<List<X,Xs...>>{
    static constexpr auto value = (X > max<List<Xs...>>::value) ? X : max<List<Xs...>>::value;
};

template<auto X>
struct max<List<X>>{
    static constexpr auto value = X;
};

template<>
struct max<List<>>{
    static constexpr auto value = 0;
};

//*****************************************************************************

template<std::size_t N>
struct drop<List<>,N>
{
    using type = List<>;
};

template<auto X,auto... Xs,std::size_t N>
struct drop<List<X,Xs...>,N>
{
    using type = typename dropHelper<List<X,Xs...>,N-1,N==0>::type;
};

template<auto X,auto... Xs,std::size_t N>
struct dropHelper<List<X,Xs...>,N,true>
{
    using type = List<X,Xs...>;
};

template<auto X,auto... Xs,std::size_t N>
struct dropHelper<List<X,Xs...>,N,false>
{
    using type = typename dropHelper<List<Xs...>,N-1,N==0>::type;
};

template<std::size_t N,bool B>
struct dropHelper<List<>,N,B>
{
    using type = List<>;
};


//END PROJECT******************************************************************

template<auto X>
struct last<List<X>>
{
    static constexpr auto value = X;
};

template<auto X, auto... Xs>
struct last<List<X, Xs...>>
{
    static constexpr auto value = last<List<Xs...>>::value;
};

//*****************************************************************************

//template<auto X, auto... Xs>
//struct tail<List<X, Xs...>> {using type = List<Xs...>;};

//*****************************************************************************

template<auto X>
struct init<List<X>> {using type = List<>;};

template<auto X, auto... Xs>
struct init<List<X, Xs...>>
{
using type = typename prepend<X, typename init<List<Xs...>>::type>::type;
};

//*****************************************************************************

//*****************************************************************************

template<>
struct product<List<>>
{
    static constexpr auto value = 1;
};

template<auto X, auto... Xs>
struct product< List<X, Xs...> >
{
    static constexpr auto value = X * product<List<Xs...>>::value;
};

//*****************************************************************************

template<template<auto> typename P>
struct all<List<>,P>{
    static constexpr auto value = true;
};


template<auto X,auto... Xs, template<auto> typename P>
struct all<List<X,Xs...>,P>{
    static constexpr auto value = P<X> & all<List<Xs...>,P>;
};

//*****************************************************************************
template<template<auto> typename P>
struct any<List<>,P>{
    static constexpr auto value = true;
};


template<auto X,auto... Xs, template<auto> typename P>
struct any<List<X,Xs...>,P>{
    static constexpr auto value = P<X> || all<List<Xs...>,P>;
};

template<auto X, template<auto> typename P>
struct any<List<X>,P>{
    static constexpr auto value = P<X>
};

//*****************************************************************************
    
    template<template<auto> typename F,auto V>
struct foldr<F,V,List<>>
{
    using type = V;
};

template<auto X,auto... Xs,template<auto> typename F, auto V>
struct foldr<F,V,List<X,Xs...>>
{
    using type = typename F<X, foldr<F,V,XS...>>::type;
};

//******************************************************************************
template<auto X>
struct foldr1<List<X>>
{
    using type = X;
};

template<auto X,auto... Xs,template<auto> typename F>
struct foldr1<F,List<X,Xs...>>
{
    using type = typename F<X, foldr1<F,XS...>>::type;
};

//******************************************************************************


}//namespace vlists
