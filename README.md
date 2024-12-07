# ComplexNumber
Implement complex numbers in C++

# Устройство проекта: 
- Заголовочный файл расположен в `include/complexNumber.h`. Он по сути выполняет роль интерфейса для моего шаблоного класса `ComplexNumber`. 
- Файл с реализацией расположен в `src/complexNumber.tpp`, там прописана реализация для методов класса и дружественных функций.
`.tpp` потому что реализуем шаблонный класс.
- Тесты прописаны c помощью фрейма `Catch2`. Расположены, очевидно, в `tests/test_complexNumber.cpp`.
- Для удобства добавил `main.cpp` и прописал его запуск в `tasks.json`, чтобы вы могли потестить что-то своё. 

# Как спиздить у меня проект :)?
Клонируете мой реп себе в проект в VS code c помощью команды в терминал `git clone https://github.com/VadimDenisovich/ComplexNumber.git`
Но лучше склонируйте и уберите всё, кроме папки `build`, `lib` и `СMakeList.txt`, а остальную реализацию напишите сами. Так полезнее. 

# Если хотите сделать всё сами
1) То вам нужно для начала загрузить CMake extension (жмакаем Ctrl + Shift + X в VScode и пишем `CMake`) и сам Cmake (https://cmake.org/download/)  
2) Добавить в свой проект файл `CMakeList.txt` и туда вписать всё, как у меня в одноименном файле (это конфигуратор)
3) Далее создать папку `lib` и прописать в терминале `git clone https://github.com/catchorg/Catch2.git`
4) Чтобы запустить тесты нужно сбилдить эту папку `lib/Catch2` 
5) Пишите в терминале `cd lib/Catch2`
6) Далее пишите `cmake -B build -S . -DBUILD_TESTING=OFF`
7) А затем `sudo cmake --build build/ --target install` (если вы на win, то не забудьте включить sudo, там терминал вам сам всё предложит, останется только перейти)
8) Напишите свой проект с разбиением на заголовочный файл `.h` и реализационный `.cpp` или `.tpp`.
9) Напишите тесты с помощью гпт на Catch2 в `.cpp` файл, пример реализации можете чекнуть у меня. 
10) Откройте новый терминал (обязательно! он должен быть в папке вашего проекта, где расположен `CMakeList.txt`)
11) Пропишите команды `cmake ..` и после её выполнения `cmake --build .`
12) Если всё гуд, то поздравляю! Пишите `ctest` или `ctest --verbose` (для полной выкладки с инфой) и кайфуйте от готово проекта. 