# Disclaimer

Using Libcurl and Boost, I implement the basic REST API functions in C++. This is a more casual project that I did in preperation for one of my interviews for their "Integration Round". I used Visual Studio and after a lot of pain to figure out how to get Boost and Libcurl to work properly, I made the program and figured out the CMake. The README below is the README given by the company (whose name I have hidden), which shows how to set this up in Visual Studio along with Libcurl and Boost, along with the CMake file given. Here onwards is the file by the company. Keep in mind, the file **helloworld.cpp** is entirely coded by me and has no relation to the rest of the files, which were not done by me.

# Integration Round

Thanks for interviewing at X. To make sure that we can use our time best in the interview, we'd like to have you do some setup in advance.

We've noticed that more often than not, we've had to spend a significant portion of the interview helping candidates setup a CMake-based C++ environment on their personal laptops.

We've created a (rather ad-hoc) CMake project to help candidates determine if their laptops were setup to write C++, so interviews can be about evaluating the candidate, and not the way their environment is setup.

# Getting ready
First, clone this repository to your computer (creating a fork of the repository is not necessary). Next, ensure that you have `cmake`, a C++ compiler and `libcurl` installed.

## Linux or macOS
- If you're using Debian or Ubuntu, you likely want to run
```
# One command, spread over several lines...
sudo apt-get install \
  cmake build-essential \
  libboost-all-dev \
  libcurl4-openssl-dev libcurlpp-dev
```
- If you're using macOS with HomeBrew installed, you might want to run `brew install cmake curl`.

If you can run these commands, your development environment is probably ready for X's C++ interview questions:

```powershell
$ cmake --version
$ git clone [project URL]
$ cd [into the project]
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./hello
```

## Windows (Visual Studio)
- Make sure you have the **C++ CMake tools for Windows** installed. These should automatically be there if you selected C++ as a language when installing Visual Studio. There are more instructions on installing `CMake` in Visual Studio [here](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019#installation).
- Install `libcurl` using `vcpkg`. Open Windows PowerShell and run the following
    ```
    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    .\bootstrap-vcpkg.bat
    .\vcpkg.exe integrate install
    .\vcpkg.exe install --triplet x64-windows curl[tool]
    ```
- Optionally, you can also install [boost](https://www.boost.org/) via `vcpkg` if you would like to use it. (This will take a while, 30mins or more!) 
    ```
    vcpkg install --triplet x64-windows boost
    ```
- Setup the project in Visual Studio
    - Make sure you open the folder with this repository via **File > Open > Folder** menu item and Visual Studio should automatically detect and run `cmake.exe`.
    - Double click on `CMakeLists.txt` and that should trigger a build. The output window should not show any errors once CMake completes.
    - There are more details on using CMake with Visual Studio [here](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019#ide-integration).  

- You should now be able to right click on `helloworld.cpp` in Solution Explorer and be able to `compile` and `debug`(run) the code

## Other platforms or if you want to debug
- You can find installation instructions for `CMake` [here](https://cmake.org/install/).
- You can find installation instructions for `libcurl` [here](https://curl.haxx.se/docs/install.html).
