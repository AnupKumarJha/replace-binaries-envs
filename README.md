# replace-binaries-envs
A tool to replace local environment info in binaries

Steps 
1. create binary file using this 
```clang++ -std=c++11 binary_modifier.cpp -o binary_modifier```
2. run below this to chnage the envs of binary file 
   ```./binary_modifier path/to/binary path/to/base/director ```
