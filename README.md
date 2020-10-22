# Private-Data-Collection-and-Notification-Management-for-Contact-Tracing-Prototype

## Note
The present artifact is a proof-of-concept implementation of our protocol in Figure 4 (Section 4.2) of the related paper. Each entity in the protocol is a class in this prototype, each phase of the protocol is translated to a public method of the participating entity. For instance, DeriveRiskList() is a method in both Gov and Store classes since both the entities participate in the protocol. The implementation of each method meticulously carries out the calculations that are shown in the corresponding figure.  


## Pre-requisite 
Linux OS with g++ compiler and [libsodium](https://libsodium.gitbook.io/doc/installation) library installed.

## Compilation 
Command line to compile: g++ main.cpp user.cpp store.cpp gov.cpp -o app.out -lsodium

## Execution 
Commmand line to run: ./app.out
