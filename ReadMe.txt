SBSA Code

Contents
=============================================================
 0: To Do
 1: Introduction
 2: Development Guidelines
 3: Requirements
 4: Windows: Installation
 5: Windows: Compiling & Linking

0: To Do 
=============================================================


1: Introduction
=============================================================
Tools used in the calcuation of early warning triggers for sector ratings

2: Development Guidelines
=============================================================
Use 4 spaces instead of tabs for indentation rules 
All committed code must have a comprehensive set of tests. Test classes should be created in the same directory as the original code using the boost testing framework

3: Requirements
=============================================================
This code has been built and tested using
1) Microsoft Visual Studio 2015 Community edition; As this was an upgrade from 2010, there is a need to include two additional variables in the include directory, namely 
2) Boost 1.62.0 (using an environmental variable “boost” set to point to the root boost directory and "boostlib" pointing to the folder holding the compiled libraries - usually something equivalent to “$(boost)lib32-msvc-14.0\”

4: Windows: Installation 
=============================================================
Variables used:
        SBSA = e:\code\


5: Windows: Compiling & Linking 
=============================================================

