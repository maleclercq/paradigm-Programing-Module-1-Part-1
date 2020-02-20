//fn main() {
//    start3();
//}
//
//fn start3() {
//    println!("{}",3);
//    println!("{}",2);
//    println!("{}",1);
//    println!("Go");
//}
//
// becomes :

fn main() {
    start(3);
}

fn start(count : u32) {
    for i in (1..count+1).rev() {
        println!("{}", i);
    }
    println!("Go");
}
