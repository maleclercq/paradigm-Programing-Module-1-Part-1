use std::cmp::Ordering;
use std::fmt::Display;

fn main() {
    print_comparison(4, 4); // integers
    print_comparison('t', 'p'); // characters
    print_comparison("abc", "xyz"); // strings
}

fn print_comparison<T> (val1 : T, val2 : T)
    where T : Ord + Display {
        println!("{} {} {}",
            val1,
            match val1.cmp(&val2) {
                Ordering::Less => "comes before",
                Ordering::Equal => "is equal to",
                Ordering::Greater => "comes after"
            },
            val2);
}
