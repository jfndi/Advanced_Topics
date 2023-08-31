# Advanced_Topics
Please, note that most of the programs in this git submodule won't compile.
This is caused by the fact that, at least on Ubuntu and Debina the <format>
header file is not present. It will be available soon (it will be part of
one of the gcc 12 updates as far as I know).
That being said, to be on the safe side use C++20 standard. With gcc use the
-std=g++20 switch and with Visual Studio, either right click on the project in
the Solution Explorer -> Properties -> General -> C++ Language Standard ->
ISO C++20 Standard, or use the switch /std:c++20.
Heavely based on the LinkedIn course "Adavnced Topics in C++" by Bill Weinman