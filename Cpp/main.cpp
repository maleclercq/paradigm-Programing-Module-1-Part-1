#include <iostream>

#include "VList.hpp"
#include "VListUtils.hpp"

//#include "TListSetup.hpp"
//#include "TList.hpp"

using std::cout;
using std::endl;

void test_v_and(){
    using L1 = vlists::List<true,true,false,true>;

    using L2 = vlists::List<true>;
    using L3 = vlists::List<false>;

    using L4 = vlists::List<>;

    using L5 = vlists::List<true,true,false>;

    static_assert(vlists::and_list<L1>::value == 0);
    static_assert(vlists::and_list<L2>::value == 1);
    static_assert(vlists::and_list<L3>::value == 0);
    static_assert(vlists::and_list<L4>::value == 1);
    static_assert(vlists::and_list<L5>::value == 0);
}

void test_v_or(){
    using L1 = vlists::List<true,true,false,true>;

    using L2 = vlists::List<true>;
    using L3 = vlists::List<false>;

    using L4 = vlists::List<>;

    using L5 = vlists::List<true,true,false>;

    static_assert(vlists::or_list<L1>::value == 1);
    static_assert(vlists::or_list<L2>::value == 1);
    static_assert(vlists::or_list<L3>::value == 0);
    static_assert(vlists::or_list<L4>::value == 1);
    static_assert(vlists::or_list<L5>::value == 1);
}

void test_v_sum(){
    using L1 = vlists::List<1,2,3,4>;
    using L2 = vlists::List<>;

    using L3 = vlists::List<42>;

    using L4 = vlists::List<43,-1,2,-2>;

    static_assert(vlists::sum<L1>::value == 10);
    static_assert(vlists::sum<L2>::value == 0);
    static_assert(vlists::sum<L3>::value == 42);
    static_assert(vlists::sum<L4>::value == 42);
}

template<auto T>
struct minus_three
{
    static constexpr bool value = T < 3;
};

void test_v_dropWhile(){
    using L1 = vlists::List<1,2,3,4,5,6,7,8,1,2,3>;
    using L2 = vlists::dropWhile<L1,minus_three>::type; //should be 3,4,5,6,7,8,1,2,3

    using L3 = vlists::List<1,2,42>;
    using L4 = vlists::dropWhile<L3,minus_three>::type; //should be 42

    using L5 = vlists::List<1,2>;
    using L6 = vlists::dropWhile<L5,minus_three>::type; //should be <>

    static_assert(vlists::sum<L2>::value == 39);
    static_assert(vlists::sum<L4>::value == 42);
    static_assert(vlists::sum<L6>::value == 0);
};

void test_v_takeWhile(){
    using L1 = vlists::List<1,2,3,4,5,6,7,8,1,2,3>;
    using L2 = vlists::takeWhile<L1,minus_three>::type; //should be 4,5,6,7,8,1,2,3

    using L3 = vlists::List<1,2,42>;
    using L4 = vlists::takeWhile<L3,minus_three>::type; //should be 1,2

    using L5 = vlists::List<2,42>;
    using L6 = vlists::takeWhile<L5,minus_three>::type; //should be 42

    using L7 = vlists::List<>;
    using L8 = vlists::takeWhile<L7,minus_three>::type;;

    static_assert(vlists::sum<L2>::value == 3);
    static_assert(vlists::sum<L4>::value == 3);
    static_assert(vlists::sum<L6>::value == 2);
    static_assert(vlists::sum<L8>::value == 0);
}

void test_v_elem(){
    using L1 = vlists::List<1,2,3,4,5>;
    using L2 = vlists::List<'e',7,8,false>;

    using L3 = vlists::List<>;

    static_assert(vlists::elem<L1,5>::value == true);
    static_assert(vlists::elem<L2,8>::value == true);

    static_assert(vlists::elem<L1,6>::value == false);
    static_assert(vlists::elem<L2,'e'>::value == true);

    static_assert(vlists::elem<L3,42>::value == false);
}

void test_v_length(){
    using L1 = vlists::List<1,'c',3,4,true>;
    using L2 = vlists::List<6,7,8,9>;

    using L3 = vlists::List<>;

    static_assert(vlists::length<L1>::value==5);
    static_assert(vlists::length<L2>::value==4);
    static_assert(vlists::length<L3>::value==0);
}

void test_v_min(){
    using L1 = vlists::List<1,2,3,4,5>;
    using L2 = vlists::List<6,7,8,9,-42>;

    using L3 = vlists::List<>;
    using L4 = vlists::List<42,69,8,9,18>;

    static_assert(vlists::min<L1>::value == 1);
    static_assert(vlists::min<L2>::value == -42);
    static_assert(vlists::min<L3>::value == 0);
    static_assert(vlists::min<L4>::value == 8);
}

void test_v_max(){
    using L1 = vlists::List<1,2,3,4,5>;
    using L2 = vlists::List<6,7,8,9,-42>;

    using L3 = vlists::List<>;
    using L4 = vlists::List<42,69,8,9,18>;

    static_assert(vlists::max<L1>::value == 5);
    static_assert(vlists::max<L2>::value == 9);
    static_assert(vlists::max<L3>::value == 0);
    static_assert(vlists::max<L4>::value == 69);
}

void test_v_drop(){
    using L1 = vlists::List<1,2,3,4,5,6,7,8,1,2,3>;
    using L2 = vlists::drop<L1,3>::type; //should be 4,5,6,7,8,1,2,3

    using L3 = vlists::List<1,2,42>;
    using L4 = vlists::drop<L3,2>::type; //should be 42

    using L5 = vlists::List<1,2>;
    using L6 = vlists::drop<L5,2>::type; //should be <>

    using L7 = vlists::List<>;
    using L8 = vlists::drop<L7,42>::type;

    static_assert(vlists::sum<L2>::value == 36);
    static_assert(vlists::sum<L4>::value == 42);
    static_assert(vlists::sum<L6>::value == 0);
    static_assert(vlists::sum<L8>::value == 0);
}

template<auto T>
struct pair
{
    static constexpr bool value = T % 2 = 0;
};


void test_v_all(){
    using L1 = vlists::List<1,2,3,4,5,6,7,8>;
    using L2 = vlists::List<2,4,6,8,10>;
    using L3 = vlists::List<>;
    using L4 = vlists::List<-1,-3,-5>;

    static_assert(vlists::all<L1,pair>::value == false);
    static_assert(vlists::all<L2,pair>::value == true);
    static_assert(vlists::all<L3,pair>::value == true);
    static_assert(vlists::all<L4,pair>::value == false);

}
void test_v_any(){
    using L1 = vlists::List<1,2,3,4,5,6,7,8>;
    using L2 = vlists::List<2,4,6,8,10>;
    using L3 = vlists::List<>;
    using L4 = vlists::List<-1,-3,-5>;

    static_assert(vlists::any<L1,pair>::value == true);
    static_assert(vlists::any<L2,pair>::value == true);
    static_assert(vlists::any<L3,pair>::value == true);
    static_assert(vlists::any<L4,pair>::value == false);

}
void test_v_product(){
    using L1 = vlists::List<1,2,3,4,5>;
    using L2 = vlists::List<0,63,29,18,18>;
    using L3 = vlists::List<>;
    using L4 = vlists::List<-1,1,2,3,4,5>;

    static_assert(vlists::product<L1>::value == 120);
    static_assert(vlists::product<L2>::value == 0);
    static_assert(vlists::product<L3>::value == 1);
    static_assert(vlists::product<L4>::value == -120);
}
void test_v_foldr(){

}
void test_v_foldr1(){

}

int main() {
    test_v_and();
    test_v_or();
    test_v_sum();
    test_v_dropWhile();
    test_v_takeWhile();
    test_v_elem();
    test_v_length();
    test_v_min();
    test_v_max();
    test_v_drop();
    test_v_all();
    test_v_any();
    test_v_product();
    test_v_foldr();
    test_v_foldr1();

    cout << "Everything is fine" <<endl;
return 0;
}
