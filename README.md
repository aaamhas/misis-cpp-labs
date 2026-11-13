# Лабораторные работы по C++ · МИСиС

В `prj.labs/` у каждой лабораторной своя папка и цель CMake. Тесты добавляются в `prj.test/`, библиотека doctest лежит в `prj.thirdparty/doctest/`.

## Порядок работ

1. [`Complex`](prj.labs/complex/)
2. [`rational`](prj.labs/rational/)
3. [`arrayd`](prj.labs/arrayd/)
4. [`stacka`](prj.labs/stacka/)
5. [`stackl`](prj.labs/stackl/)
6. [`queuea`](prj.labs/queuea/)
7. [`queuel`](prj.labs/queuel/)
8. [`bitsetd`](prj.labs/bitsetd/)
9. [`arrayt`](prj.labs/arrayt/)
10. [`dio`](prj.labs/dio/)

## Сборка

Из корня проекта:

```powershell
cmake -S . -B build
cmake --build build --config Debug
```

Для первой лабораторной начни с `prj.labs/complex/complex.hpp` и `prj.labs/complex/complex.cpp`. Чтобы собрать только её, добавь к команде сборки `--target complex`. Когда напишешь тест, зарегистрируй его по примеру в `prj.test/CMakeLists.txt` и запусти `ctest --test-dir build -C Debug --output-on-failure`.

Структура основана на учебных репозиториях Д. В. Полевого ([осень](https://github.com/dvpsun/misis2025f-25-00-polevoi-d-v), [весна](https://github.com/dvpsun/misis2026s-25-00-polevoi-d-v)).
