# Rust - Lifetimes
Lifetime of a variable
- Range of time a variable is valid

We need to ensure the lifetimes of separate variables do not overlap, if one is mutable borrow, the other can't be borrowed at the same time.

Examples where lifetimes are needed:
- t is mutated during x's lifetime
```rust
fn main() {
    let mut s = vec![4,5,6]; // mutable vector

    s.push(7);

    let x = & s;

    //this line is fine
    println!("{}",s.len());

    let t = &mut s;

    t.push(8);

    println!("{}",t.len());
    println!("{}",s.len());

    //this line is not, because it
    //means the mutable borrow of s to x
    //happens at the same time as the
    //mutable borrow to t
    //and we can't have a mutable borrow at
    //the same time as another borrow
    println!("{}",x.len());
}
```

### Solution
- Using ```{``` and ```}``` to limit the scope of the borrow
    - once out of scope, the borrow is released
    - this is called "borrow checker" since checked at compile time
    
```rust
fn main() {
    let a = vec![6,5,];
    println!("{}",a.len());

    let x: &Vec<i32>;

    { // new scope
     let b = vec![7,8,9];
     let y: &Vec<i32>;
     (x,y) = (&a,&b);
     println!("{}",y.len());
    } // b and y goes out of scope

    print!("{}",x.len());
}
```

## Lifetime Annotations
- We explicitly tell the compiler the lifetime of a variable, when borrowed in a function call
- This is done using the ```<'a>``` syntax
- defined explicitly for inputs and outputs, and the lifetimes of the inputs and outputs must match

```rust
fn nice <'a,'b>(x: &'a Vec<i32>, y: &'b Vec<i32>)
  -> ( &'b Vec<i32>, &'a Vec<i32>) {
    return (y,x);
}

fn main() {
    let a = vec![6,5,];
    println!("{}",a.len());

    let x: &Vec<i32>;
    {
     let b = vec![7,8,9];
     let y: &Vec<i32>;
     (y,x) = nice(&a,&b);
     println!("{}",y.len());
    }

    print!("{}",x.len());
}
```

Sometimes the complier can infer the lifetimes, so we don't need to specify them.