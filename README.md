# nsp5-lab
Lab for 5th Semester Network Programming and Security Lab


## Programs 

- [X] Program 1 - TCP file server and client
  - [X] Server - Read file according to recieved filename and send it
  - [X] Client - Send filename, and recieve file and output to `stdout`


## Building the resources

This project was built using CMake for convenience as there are lots of executables.

### Cmake

```sh
mkdir -p build
cd build
cmake ..
make
```
## GCC

Needs to be done one by one.
Refer to below example:
```sh
cc -I ./include src/p1/client.c -o client.out
```

## Screenshots and Output

Please refer `output` folder