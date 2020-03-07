#include <iostream>

#include "VList.hpp"
#include "VListUtils.hpp"

//#include "TListSetup.hpp"
//#include "TList.hpp"

using std::cout;
using std::endl;

template<auto X>
struct times2 {
    static constexpr auto value = X * 2;
};

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
    using L2 = vlists::dropWhile<L1,minus_three>::type; //should be 4,5,6,7,8,1,2,3

    using L3 = vlists::List<1,2,42>;
    using L4 = vlists::dropWhile<L3,minus_three>::type; //should be 4,5,6,7,8,1,2,3

    using L5 = vlists::List<1,2>;
    using L6 = vlists::dropWhile<L5,minus_three>::type; //should be 4,5,6,7,8,1,2,3

    static_assert(vlists::sum<L2>::value == 39);
    static_assert(vlists::sum<L4>::value == 42);
    static_assert(vlists::sum<L6>::value == 0);
};

void test_v_takeWhile(){
    using L1 = vlists::List<1,2,3,4,5,6,7,8,1,2,3>;
    using L2 = vlists::takeWhile<L1,minus_three>::type; //should be 4,5,6,7,8,1,2,3

    using L3 = vlists::List<1,2,42>;
    using L4 = vlists::takeWhile<L3,minus_three>::type; //should be 4,5,6,7,8,1,2,3

    using L5 = vlists::List<2,42>;
    using L6 = vlists::takeWhile<L5,minus_three>::type; //should be 4,5,6,7,8,1,2,

    using L7 = vlists::List<>;
    using L8 = vlists::takeWhile<L7,minus_three>::type;;

    static_assert(vlists::sum<L2>::value == 3);
    static_assert(vlists::sum<L4>::value == 3);
    static_assert(vlists::sum<L6>::value == 2);
    static_assert(vlists::sum<L8>::value == 0);
}

int main() {
    test_v_and();
    test_v_or();
    test_v_sum();
    test_v_dropWhile();
    test_v_takeWhile();

    cout << "Everything is fine" <<endl;
return 0;
}