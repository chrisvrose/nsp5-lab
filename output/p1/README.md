# Program 1 Output

- [Program 1 Output](#program-1-output)
  - [1](#1)
    - [Client](#client)
    - [Server](#server)
  - [2](#2)
    - [Client](#client-1)
    - [Server](#server-1)
  - [3](#3)
    - [Client](#client-2)
    - [Server](#server-2)


## 1

Successful client server exchange

### Client

```
[atreya@atreya-laptop-lan build]$ ls -l
total 112
-rw-r--r--.  1 atreya atreya 19815 Oct 21 15:34 CMakeCache.txt
drwxr-xr-x. 35 atreya atreya  4096 Oct 21 17:04 CMakeFiles
-rw-r--r--.  1 atreya atreya  1555 Oct 21 15:32 cmake_install.cmake
-rw-r--r--.  1 atreya atreya   730 Oct 21 15:38 compile_commands.json
-rw-r--r--.  1 atreya atreya  3514 Oct 21 15:32 CPackConfig.cmake
-rw-r--r--.  1 atreya atreya  3980 Oct 21 15:32 CPackSourceConfig.cmake
-rw-r--r--.  1 atreya atreya   317 Oct 21 15:32 CTestTestfile.cmake
-rw-r--r--.  1 atreya atreya  2679 Oct 21 15:32 DartConfiguration.tcl
-rw-r--r--.  1 atreya atreya  7328 Oct 21 15:38 Makefile
-rwxr-xr-x.  1 atreya atreya 23912 Oct 21 17:04 p1C
-rwxr-xr-x.  1 atreya atreya 25480 Oct 21 17:04 p1S
drwxr-xr-x.  3 atreya atreya  4096 Oct 21 15:32 Testing
[atreya@atreya-laptop-lan build]$ ./p1C 127.0.0.1
I>Hello world
I>Allocated socket 1
Enter file name
:Makefile
I> Read filesize 7328
I>READ up 300
I>READ up 200
I>READ up 100
I>READ up 100
I>READ up 100
I>READ up 2000
I>READ up 400
I>READ up 800
I>READ up 2000
I>READ up 1328
I>Wrote output to "resp.out"
[atreya@atreya-laptop-lan build]$ ls -l Makefile resp.out
-rw-r--r--. 1 atreya atreya 7328 Oct 21 15:38 Makefile
-r----x--t. 1 atreya atreya 7328 Oct 21 17:05 resp.out
[atreya@atreya-laptop-lan build]$ diff Makefile resp.out 
[atreya@atreya-laptop-lan build]$ 
```

### Server
```
[atreya@atreya-laptop-lan build]$ ./p1S
I>Allocated socket 1
31084>Created to respond
7>Ready
I>File"Makefile"
I>Getting file size
I>File size 7328
G>Child(31084) has exit
```

## 2

Client not provided server address

### Client
```
[atreya@atreya-laptop-lan build]$ ./p1C
I>Hello world
E>No addr
```

### Server
```
[atreya@atreya-laptop-lan build]$ ./p1S
I>Allocated socket 1
```

## 3

Client `resp.out` file open error, disconnects

### Client

```
[atreya@atreya-laptop-lan build]$ ls
CMakeCache.txt         CPackConfig.cmake        Makefile  Testing
CMakeFiles             CPackSourceConfig.cmake  p1C
cmake_install.cmake    CTestTestfile.cmake      p1S
compile_commands.json  DartConfiguration.tcl    resp.out
[atreya@atreya-laptop-lan build]$ ./p1C 127.0.0.1
I>Hello world
I>Allocated socket 1
Enter file name
:Makefile
I> Read filesize 7328
E> Could not open file
[atreya@atreya-laptop-lan build]$ 
```

### Server

```
[atreya@atreya-laptop-lan build]$ ./p1S
I>Allocated socket 1
31793>Created to respond
7>Ready
I>File"Makefile"
I>Getting file size
I>File size 7328
E> Closed suddenly
G>Child(31793) has exit
```