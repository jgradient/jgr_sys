jgr_sys
=======

Cross-platform library abstracting low-level system services. The primary 
platforms of interest are Linux and Windows.

Installation
------------

[CMake](http://www.cmake.org/) build system is used to build and install the 
library.

Requirements:
- C compiler

  Known to compile with gcc versions 4.7.2, 4.8.3 and Visual Studio 2012

- CMake 2.8 or later
- [Doxygen](http://www.doxygen.org/) 1.8 or later (optional)

  Used to generate the HTML documentation.

Detailed Steps on a Linux-like system:
1. Create a build directory

       mkdir build
       cd build

2. Run `cmake` or `ccmake` with any desired options

        cmake ..

3. Compile and install

        make install

Documentation
-------------

Library headers are documented in-source.

HTML documentation is generated with [Doxygen](http://www.doxygen.org/) if it 
is found by CMake during configuration. It is installed into 
`${CMAKE_INSTALL_PREFIX}/share/doc/jgr_sys`.

License
-------

The library is licensed under the GNU Affero General Public License.

Bugs/Issues
-----------

Use GitHub [issue tracker](https://github.com/jgradient/jgr_sys/issues) to report bugs.

Other Questions
---------------

Post your question to the [Q&A forum](https://groups.google.com/d/forum/jgr_sys-users).
