# Bitprim Keoken 
> An open protocol for extending blockchain functionality

## Documents

- [White Paper](keoken-whitepaper.md)

- [Technical Specification](keoken-technical-specification.md)

## Installation Requirements

- 64-bit machine.
- [Conan](https://www.conan.io/) package manager, version 1.4.0 or newer. See [Conan Installation](http://docs.conan.io/en/latest/installation.html#install-with-pip-recommended).

## Installation

The *Keoken* executable can be installed on Linux, macOS, FreeBSD, Windows and others. These binaries are pre-built for the most usual operating system/compiler combinations and hosted in an online repository. If there are no pre-built binaries for your platform, a build from source will be attempted.

So, for any platform, an installation can be performed in 2 simple steps:

1. Configure the Conan remote
```
conan remote add bitprim https://api.bintray.com/conan/bitprim/bitprim
```

2. Install the executable

```
conan install bitprim-node-exe/0.13.0@bitprim/testing -o keoken=True -o with_rpc=True 
```

## Building from source Requirements

In case there are no pre-built binaries for your platform, it is necessary to build from source code. In such a scenario, the following requirements must be added to the previous ones:

- C++11 Conforming Compiler.
- [CMake](https://cmake.org/) building tool, version 3.4 or newer.


## Source Code

The source code are distributed in the following Github repositories:

- [bitprim-core](https://github.com/bitprim/bitprim-core/commit/539a237ddafa4aecdf4e75abced3a1002faac2a5)
- [bitprim-blockchain](https://github.com/bitprim/bitprim-blockchain/commit/5d43b41cd9919e5ebe613611fc63f926454a2ed7)
- [bitprim-node](https://github.com/bitprim/bitprim-node/commit/f24cc8de9e7089d9a8b88417dfc066d1d7bf7c22)

*(The links are pointing to the starting commit)*

## About Bitprim

Since 2014, our multidisciplinary team has been creating tools that help and attract developers to boost a massive adoption of cryptocurrencies. Bitprim's main pillars are transparency, professionalism, customer service and collaboration with other teams. Keoken is an open protocol with a performance reference implementation built from scratch leveraging [Bitprim-Node](https://github.com/bitprim/bitprim) advanced features. Bitprim headquarters are based in Argentina.

## Contact Us

- Mail: dev@bitprim.org
- Web: https://www.bitprim.com/

