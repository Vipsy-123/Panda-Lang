# Panda Lang

Panda language is a compiled programming language that aims to achieve blend of simplicity and power.\
The compiler generates assembly code and utilizes the NASM assembler for execution.

## Building

Requires `nasm` and `ld` on a Linux operating system.

```bash
git clone https://github.com/vishalghige43/Panda-Lang
cd Panda-Lang
mkdir build
cmake -S . -B build
cmake --build build
```
Executable will be `./panda <file.pd>` in the `build/` directory.
```bash
./panda test.pd
```
This command will generate a `test.asm` file. To execute it, utilize the appropriate NASM assembler commands based on your operating system.\
Below is an example command specifically for MacOS:
```bash
cd ../test/outputFile
nasm -f macho64 test.asm && ld test.o -o test -demangle -dynamic -macos_version_min 11.0 -L/usr/local/lib -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -lSystem -no_pie && ./test; echo $? 
```



## Example of panda.pd

```python
let: digit num1 = 27; 
num1=3*(1+3);

let: string name = "Vishal";
if(num1){
    #code block
}
else{
    #code block
}
for(let: digit i = 0; i<10; i = i +1 ){
    #code block
}
while(1){
    #code block
}
ret 0;
```
Implementation of vectors and map to store collections of data is currently under development.
