# Rust Memory Management - Ownership and Borrowing

> Reminder of  C
> - We manually used malloc and free to allocate and deallocate memory.
> - Fail to malloc/free leads to undefined behaviour/ Segment fault
> 
> Reminder of JAVA
> - We use a Inefficient garbage collector to automatically allocate and deallocate memory.
> - NULL pointer exceptions are common.

In Rust:
The programmer must code in a restricted way, with annotations to allow the compiler to check the memory management.

## Rust Ownership

- Every value has an owner.
- The data is deallocated once owner out of scope.
- Assignments/ function calls transfer the ownership.

Demo of transfer of ownership:
```rust
fn main() {
    let s1 = String::from("hello");
    let x = s1;
    println!("{}, world!", x); // will work since x has ownership
    println!("{}, world!", s1); // will not work since s1 has lost ownership
}
```

Demo of transfer of ownership in function:
```rust
fn main() {
    let s1 = String::from("hello");
    println!("{}, world!", s1); // will work since s1 has ownership
    takes_ownership(s1);
    println!("{}, world!", s1); // will not work since s1 has lost ownership
}

fn takes_ownership(some_string: String) {
    println!("{}", some_string);
}
```

## Rust Borrowing

- Borrowing allows to pass reference to a value without transferring ownership.
- We prefix with an `&` to borrow a reference.
- We can have multiple immutable borrows or one mutable borrow at a time.


Demo of borrowing:
```rust
fn main() {
    let s1 = String::from("hello");
    println!("{}, world!", s1); // will work since s1 has ownership
    takes_borrow(&s1); // borrow s1 (notice the &)
    println!("{}, world!", s1); // will work since s1 has ownership
}

fn takes_borrow(some_string: &String) { // notice the & to borrow
    println!("{}", some_string);
}
```

## Basic Types and Mutability

Basic types do not need to worry about ownership and borrowing.
- Integers(u32), floats, bool, char, tuples, arrays, etc.
- let doesn't transfer ownership, it will re-initialize the variable. ("Shadowing")
- pass by copy, not reference by default.

All rust variables are immutable by default.
- We can make them mutable by using the `mut` keyword.
- We also need to add this to function parameters

```rust
fn main(){
    let x = 5; // immutable
    let mut y = 5; // mutable
    y = 6; // works
    x = 6; // error
}
```

## Mutability and Borrowing

- We can have either one mutable borrow or multiple immutable borrows.
- We cannot borrow normally while there is a live mutable borrow.
- When we have mutable borrow, only you can access the data.

We use the `mut` keyword to make a variable mutable, and we use the `&mut` syntax to create a mutable reference.

```rust
fn main() {
    let mut s = String::from("hello");
    change(&mut s);
}

fn change(some_string: &mut String) {
    some_string.push_str(", world");
}
```

>NOTE: ```println!("{}", s);``` will borrow s immutably, even through we do not use &. This is because println! takes a reference to the string.

## Example
```rust
fn main() {
    let s = String::from("hello");

    let mut d = String::from("overwrit this!");

    mov(&mut d, s); // s is moved to d

    println!("{}",d);
}

fn mov(d: &mut String, s: String) {
    *d = s.clone(); // clone is needed since s is moved
    // d is mutable borrow, s is moved
    // s is deallocated
}
```