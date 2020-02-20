fn main() {
    // sqrt(sqrt(16)) = 2
    println!("sqrt(sqrt(16)) = {}",
        eval_twice(f64::sqrt, 16.0));
    
    // C != C++
    println!("C != {}",
        eval_twice(append_plus, "C".to_string()));
}

fn eval_twice<T>(f : fn(T) -> T, i : T) -> T {
    f(f(i))
}

fn append_plus(mut input : String) -> String {
    input.push_str("+");
    input
}
