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
This command will generate a `test.asm` file. To execute it, utilize the appropriate NASM assembler commands based on your operating system. Below is an example command specifically for MacOS:
```bash
cd ../test/outputFile
nasm -f macho64 test.asm && ld test.o -o test -demangle -dynamic -macos_version_min 11.0 -L/usr/local/lib -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -lSystem -no_pie && ./test; echo $? 
```



## Tour of the Language

### 1. Variables

Variables are declared using the `let:` keyword followed by its data type.

```python
let: digit x = 2;
```

### 2. Data Types

Panda supports two datatypes : `digit` and `string`. String implementation is currently under devleopment.

```python
let: digit number = 27; 
let: string name = "Vishal";
```

### 3. Conditional Statements

You can use `if` and `else` for conditional branching.

```python
if(condition){
    //do something
}
else{
    //do something
}
```

### 4. Loops

Panda offers both `for` and `while` loops.

#### For Loop

```python
for(let: digit i = 0; i<10; i = i +1 ){
    #code block
}
```

#### While Loop

```python
while(1){
    #code block
}
```

### 5. Functions

Define functions using the `func` keyword. You can specify parameters and return types.

```python
fun add(digit x, digit y):digit{
    return x + y;
}
```

### 6. Vectors and Map

Create vectors and map to store collections of data.
Feature currently under development