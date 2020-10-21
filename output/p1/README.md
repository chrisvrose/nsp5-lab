# Program 1 Output

- [Program 1 Output](#program-1-output)
  - [1](#1)
    - [Server](#server)
    - [Client](#client)
  - [2](#2)
    - [Client](#client-1)
    - [Server](#server-1)
  - [3](#3)
    - [Client](#client-2)
    - [Server](#server-2)


## 1

Successful client server exchange

![Program1](Screenshot%20from%202020-10-21%2017-51-53.png)

### Server

```
[atreya@atreya-laptop-lan build]$ cat ./file.txt
Hello world
This is a file
[atreya@atreya-laptop-lan build]$ ./p1S
I>Allocated socket 1
37256>Created to respond
7>Ready
I>File"file.txt"
I>Getting file size
I>File size 27
G>Child(37256) has exit
```

### Client



```
[atreya@atreya-laptop-lan build]$ ./p1C 127.0.0.1
I>Hello world
I>Allocated socket 1
Enter file name
:file.txt
I> Read filesize 27
I>File contents:
Hello world
This is a file

I>File contents over
```

## 2

Client not provided server address

![Program1](Screenshot%20from%202020-10-21%2017-52-19.png)

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

File does not exist on server

![Program1](Screenshot%20from%202020-10-21%2017-53-34.png)

### Client

```
[atreya@atreya-laptop-lan build]$ ./p1C 127.0.0.1
I>Hello world
I>Allocated socket 1
Enter file name
:random.txt
I> Read filesize 0
E> ServerError
[atreya@atreya-laptop-lan build]$ 
```

### Server

```
[atreya@atreya-laptop-lan build]$ ./p1S
I>Allocated socket 1
37528>Created to respond
7>Ready
I>File"random.txt"
I>File size 0
E>Could not open file
G>Child(37528) has exit

```