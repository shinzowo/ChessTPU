Для сборки необходимы CMake, g++. Сборка протестирована только для Windows.

Для сборки текущей версии из корневой директории в командной строке выполните:

``
cmake -S ./testing/simpleGUI -B ./build -DCMAKE_CXX_COMPILER=g++
``
``
cmake --build ./build
``

Исполняемый файл будет находиться в `./build`