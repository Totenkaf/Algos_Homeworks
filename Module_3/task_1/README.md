## __1) Склонируйте репозиторий на локальную машину:__

## __2) В папке task_1 соберите проект:__
```
- mkdir build && cd build
- cmake -DBUILD_TESTS=ON ..
- make
```
Флажок -DBUILD_TESTS=ON создаст юнит-тесты  

## __3) В папке build запустите проект:__
```
- ./run_graphs
```

## __4) В папке build запустите юнит-тесты:__
```
- cd graphs/test
- ./unit_test
```