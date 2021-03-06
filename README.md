# Private-Data-Collection-and-Notification-Management-for-Contact-Tracing-Prototype

The present artifact is a proof-of-concept implementation of our protocol in Figure 4 (Section 4.2) of the related paper. As a pre-requisite of this protocol, the prototype also implements the `EnrollUser` protocol in Figure 3 (Section 3.3) of our paper. Each entity in these protocols is a class in this prototype, each phase of the protocols is translated to a public method of the participating entity (class). For instance, `DeriveRiskList()` is a method in both Gov and Store classes since both entities participate in `DeriveRiskList` phase of the protocol. The implementation of each method meticulously carries out the computations that are shown in the corresponding protocol diagram (in paper). For a deeper understanding of our implementation, the interested reader is directed to the associated code files, which are self-documented and self-explanatory.  

## Pre-requisites 

- g++ compiler (v7.4.0)
- [libsodium](https://libsodium.gitbook.io/doc/installation) library.
- CMake v3.10.2 or higher (Optional)

## Compilation 
- **Option 1**

On the terminal, navigate to src directory. Enter following command line to compile: 
```
g++ main.cpp user.cpp store.cpp gov.cpp setup.cpp -o pptrace -lsodium -w
```
- **Option 2** (Requires CMake v3.10.2 or higher)

On the terminal, navigate to project directory. Enter following sequence of command lines to compile:
```
  mkdir build
  cd build
  cmake ..
  make
```

## Execution 
Numbers similar to those reported in Table 1 and Table 2 of our paper may now be reproduced by running the executable: 
```
./pptrace
```

## Output
Besides being printed on the console as the program runs, the experimental results are also saved in `Contact_Tracing_Results.txt` in the project directory for later reference.


