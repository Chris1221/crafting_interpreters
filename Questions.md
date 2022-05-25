## Chapter 14

- Why are some functions defined in the header as macros? Like `FREE_ARRAY`, `GROW_ARRAY`, etc. 

## Chapter 15 

What does `;;` mean? I.e. in `vm.c`: 

```c
for (;;) {
    ...
}
```

- In 15.2.1 "Then we look up the value at that index and return it. We don’t need to explicitly “remove” it from the array—moving stackTop down is enough to mark that slot as no longer in use."
    - Why don't we need to remove it? We don't have a garbage collector yet? 