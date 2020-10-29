use std::process::{Command, Stdio, ChildStdin};

fn main() {
    let mut child : std::process::Child = Command::new("bc")
        .arg("-q")
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .stderr(Stdio::piped())
        .spawn()
        .expect("Failed to start process");

    {
        let mut stdin = child.stdin.as_mut().expect("Failed to open stdin");
        stdin.write_all("Hello, world!".as_bytes()).expect("Failed to write to stdin");
    }
    
    let output = child.wait_with_output().expect("Failed to read stdout");
    
    let result = String::from_utf8_lossy(&output.stdout);
    println!("{}", result);
}
