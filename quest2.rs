fn main(){

let ranges = [
    (11,22),
    (95,115),
    (998,1012),
    (1188511880,1188511890),
    (222220,222224),
    (1698522,1698528), //No matching Id's 
    (446443,446449),
    (38593856,38593862),
    (565653,565659), //no matches 565 | 656 is not a match
    (824824821,824824827), //9 digits so auto skippin'
    (2121212118,2121212124) //no matches 21212 | 12121 is not a match
    //so I won't add the bottom 3 to other coding langauges. 
];

let mut invalid_number_value: i64 = 0;
/*so really quick the i64 thing has to do with storage volume normally it stays as i32 (32-bit) 
but the size of the number might exceed it so u64 makes it save as a (64-bit) */
    for (start, end) in ranges {    
        for n in start..=end {
            let s = n.to_string();

            if s.len() % 2 == 0{
                let half = s.len() /2;
                let first_half = &s[..half];
                let second_half = &s[half..];
                if first_half == second_half{
                    println!("{}", n);
                    invalid_number_value = invalid_number_value + n as i64;
                }
            }
        }
    }
    println!("Sum = {}", invalid_number_value)
}