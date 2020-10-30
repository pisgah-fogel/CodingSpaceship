use std::process::{Command, Stdio};
use std::io::{Read, Write};
use std::thread;

fn main() {
    let mut child : std::process::Child = Command::new("/usr/bin/bc")
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .stderr(Stdio::piped())
        .spawn()
        .expect("Failed to start process");

    println!("Writing to stdin...");
    let mut stdin = child.stdin.as_mut().expect("Failed to open stdin");
    stdin.write_all("2+3\n".as_bytes()).expect("Failed to write to stdin");

    for i in 0..8 {
        println!("Reading stdout...");
        thread::sleep_ms(500);
        let mut read_string = String::new();
        if let Some(ref mut valid_stdout) = child.stdout {
            valid_stdout.read_to_string(&mut read_string);
        }
        println!(": {}", read_string);
    }
    
    println!("Waiting for the process to finish");
    let output = child.wait_with_output().expect("Failed to read stdout");
    
    let result = String::from_utf8_lossy(&output.stdout);
    println!("Result: \"{}\"", result);
    println!("Done");
}
