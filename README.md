# Panda Lang

Panda language is a compiled programming language that aims to achieve blend of simplicity and power.
The compiler generates assembly code and utilizes the NASM assembler for execution.

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