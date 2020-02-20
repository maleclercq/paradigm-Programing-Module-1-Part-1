fn main() {
    let input = "42";
    let a : u8 = input.parse().unwrap();
    let b : i32 = input.parse().unwrap();
    let c : f32 = input.parse().unwrap();
    let d : f64 = input.parse().unwrap();
    
    println!("{} = {} = {} = {} = {}", input, a, b, c, d);
}
