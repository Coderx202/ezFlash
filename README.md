# ezFlash

A minimal, fast ISO to device writer for Linux written in C++.  
Supports progress display and large buffered writes.

⚠️ **Warning:** Writing to the wrong device (e.g. `/dev/sda`) will overwrite that drive.
Please double check the path you picked.

---

## Features
- Fast 1MB buffered writes  
- Simple progress bar  
- Simple codebase (easy to extend)  
- Linux only, uses POSIX I/O  

---

## Build

```bash
git clone https://coderx202/ezFlash.git
cd ezFlash
g++ -O2 main.cpp -o ezFlash
```
## Example usage
```bash
./ezFlash test.iso /dev/sdX
```
