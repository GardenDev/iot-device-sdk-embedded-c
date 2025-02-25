![status: inactive](https://img.shields.io/badge/status-inactive-red.svg)

This project is no longer actively developed or maintained.

Google Cloud IoT Core is being retired on August 16, 2023. Contact your Google Cloud account team for more information.  Additional guidance can be found [here](https://cloud.google.com/iot-core).

# Google Cloud IoT Device SDK for Embedded C

The Google Cloud IoT Device SDK for Embedded C is an easy-to-port, open-source C library that connects low-end IoT devices to Google Cloud IoT Core.

The Device SDK supports concurrent Pub/Sub traffic on a non-blocking socket implementation that runs on POSIX, RTOS, and no-OS devices. A Board Support Package (BSP) facilitates portability and provides platform-specific implementations through a set of functions and directories. The BSP helps implement crypto and time functions, networking, Transport Layer Security (TLS), memory management, and random number generation—without working through MQTT internals.

For more details, see the user guide in the `docs` directory.

## Source
To get the source, clone from the `master` branch of the [Google Cloud IoT
Device SDK for Embedded C GitHub
repository](https://github.com/GoogleCloudPlatform/iot-device-sdk-embedded-c.git):

```
git clone https://github.com/GoogleCloudPlatform/iot-device-sdk-embedded-c.git --recurse-submodules
```

### Directory structure

- `bin`: Executables and libraries produced by a build.
- [`doc`](doc): Documentation: Doxygen references, user guide, and porting guide.
- [`examples`](examples): Example source with makefiles. After you build with `make`, this directory will also contain the example executables.
- [`include`](include): Header files of the Device SDK API. You must add this directory to the header include path when compiling your application against the source.
- [`include/bsp`](include/bsp): Header files of the Board Support Package (BSP). Functions declared here must be defined in a device-specific BSP implementation. When compiling your BSP source, make sure this directory is on the include path.
- [`make`](make): Build system configuration files.
- `obj`: Object files generated during a build.
- [`res`](res): Resource files (for example, trusted root CA certificates.)
- [`src`](src): The source files of the Device SDK. A BSP implementation is provided for POSIX.
- [`third_party`](third_party): Third-party open-source components.
- [`tools`](tools): Scripts used by the maintainers of the repository.

## Building

The default build tool for the Device SDK is `make`. It invokes [GCC](https://www.gnu.org/software/gcc/) to produce a native build on a POSIX host. This serves as the default development environment on Ubuntu.

Run the following command to build the Device SDK:

```
make
```

The source can be cross-compiled to other target platforms via custom toolchains and the makefile, or with a specific device SDK’s IDE. For more information, see [the porting guide](doc/porting_guide.md).

### Building a TLS static library

By default, the Device SDK is built with secure connection support and thus requires a third-party TLS implementation to link against. When executing `make`, the build system defaults to mbedTLS.

As a result, the `make` and `make IOTC_BSP_TLS=mbedtls` commands are synonymous.

You can also configure the `make` system to build a library that uses wolfSSL.

```
make clean
make IOTC_BSP_TLS=wolfssl
```

The value of `IOTC_BSP_TLS` determines which script is run.
- mbedTLS: [`res/tls/build_mbedtls.sh`](res/tls/build_mbedtls.sh)
- wolfSSL: [`res/tls/build_wolfssl.sh`](res/tls/build_wolfssl.sh)

The mbedTLS build script includes a git clone and branch checkout of the mbedTLS source (upon confirmation of the license agreement). However, the wolfSSL build script requires you to clone the repository yourself. When you run `make IOTC_BSP_TLS=wolfSSL`, instructions are provided for cloning the repository.

For more details on running the scripts, see [Security](#security).

### Building and executing tests

To build and execute all tests:
1. Run `git submodule init` from the project's root directory to initialize all test dependencies.
1. Run `git submodule update` from the project's root directory to clone all submodules.
1. Run `make tests`.

By default, test execution is the final step of the `tests` build process. You can also execute the tests manually.

```
cd bin/{host_os}/tests
./iotc_utests
./iotc_gtests
./iotc_itests
```

### Building the examples

Before building the examples, build both the Device SDK static library and a TLS library, as described in the preceding sections. Then, complete the steps below to run the examples.

1. Create a project, registry and device in Cloud IoT Core.
2. Create [Cloud IoT Core device credentials](https://cloud.google.com/iot/docs/how-tos/credentials/keys).
3. Follow the steps in the examples README.md files to provision the device credentials and build the client applications.
4. Run `make` in the [`examples`](examples) folder. The `make` process automatically downloads the Google Root CA PEM file to the example directories. The file enables TLS when communicating with Cloud IoT Core.

To securely connect to Cloud IoT Core, a root CA `.pem` file must be in the current working directory of the example executables. By default, the file is in `res/trusted_RootCA_certs/roots.pem` and contains two certificates that validate Cloud IoT Core credentials. The `make` process automatically moves this file from `res/trusted_RootCA_certs/roots.pem` to the correct location.

To maintain a secure connection with Cloud IoT Core, we strongly recommend that you perform frequent security-related firmware updates.

### Cross-compilation

Follow the steps below to perform the cross-compilation process.

- Extend the build system with a new cross-compilation preset in the file `make/mt-config/mt-presets.mk`.
- Create a set of files that represent the Board Support Package (BSP) implementation you've written for your platform. Store these in the directory `src/bsp/platform/TARGET_PLATFORM`.
- Build a TLS BSP implementation to invoke the TLS SDK for your platform. Store these in a new directory `src/bsp/tls/TARGET_TLS_SOLUTION`.
- Build a Cryptography BSP implementation to handle key signatures of JWTs on your target platform in the directory `src/bsp/crypto/TARGET_CRYPTO_SOLUCTION`.

For more details on the cross-compilation process, see [the porting guide](doc/porting_guide.md).

## Security

The Device SDK supports secure connection through a third-party TLS library. The Device SDK is tested against [mbedTLS](https://tls.mbed.org) and [wolfSSL](https://www.wolfssl.com).

This repository does not directly include TLS libraries; you can clone the TLS git repositories and place them in the `third_party/tls/mbedtls` and `third_party/tls/wolfssl` directories, respectively. Running `make` without any parameters will start a build that includes git checkout, build configuration, and compilation of the mbedTLS library.

The Device SDK supports other TLS libraries through the BSP TLS API. For information about configuring the build process to work with your preferred library, see the porting guide in `doc/porting_guide.md`.  Additionally, check the user guide `doc/user_guide.md` to make sure your TLS implementation meets the security requirements to connect to Cloud IoT Core.

## Stability and QA

19 combinations of compilers and feature sets are continuously built. 58 functional, 23 integration and 199 unit tests are executed after each build. Tests are executed against the TLS libraries [mbedTLS](https://tls.mbed.org) and [wolfSSL](https://www.wolfssl.com).

Branch      | Build status
------------|-------------
master      | [![Build Status][travis-badge]][travis-url]

[travis-badge]: https://travis-ci.com/GoogleCloudPlatform/iot-device-sdk-embedded-c.svg?branch=master
[travis-url]: https://travis-ci.com/GoogleCloudPlatform/iot-device-sdk-embedded-c

## Contributing

For information about contributing to this repository, see
[`CONTRIBUTING.md`](CONTRIBUTING.md).

## Learn more

Review the following documentation:

- [`doc/user_guide.md`](doc/user_guide.md): User guide that covers Device SDK features and usage.
- [`doc/porting_guide.md`](doc/porting_guide.md): Porting guide that provides information about porting the Device SDK to target devices.
- Device SDK [API](https://googlecloudplatform.github.io/iot-device-sdk-embedded-c/api/html/) and [BSP](https://googlecloudplatform.github.io/iot-device-sdk-embedded-c/bsp/html/) references.

## License

Copyright 2018-2020 Google LLC

Licensed under the BSD 3-Clause license.

For more information, see [`LICENSE.md`](LICENSE.md).
