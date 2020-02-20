#[macro_export]
macro_rules! powers_2_3 {
    ($($x:expr),*) => {
        {
            let mut v_square = Vec::new();
            let mut v_cube = Vec::new();
            
            $(
                v_square.push($x*$x);
                v_cube.push($x*$x*$x);
            )*
            
            (v_square, v_cube)
        }
    };
}

fn main() {
    let numbers : (Vec<i8>, Vec<i8>) =
        powers_2_3![0, -1, -2, -3, -4];
    
    // ([0, 1, 4, 9, 16], [0, -1, -8, -27, -64]) 
    println!("{:?}", numbers);
}
