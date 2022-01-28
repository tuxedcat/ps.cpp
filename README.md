# pslib (Problem Solving Library)

## Interface
  1. [s, e) half opened range
  2. 0-based index
  3. Support negative index (same as python)

## Getting Started
  Requirements: c++20, g++
  1. git clone https://github.com/tuxedcat/pslib  
  2. cd pslib  
  3. cp src/tpl.cpp src/main.cpp //main.cpp에 템플릿코드 복사  
  4. source tool/build.sh src/main.cpp D //실행파일 res/a.out과 병합된코드 res/submit.cpp가 생성된다. (디버그빌드)  
  5. source tool/build.sh src/main.cpp R //실행파일 res/a.out과 병합된코드 res/submit.cpp가 생성된다. (릴리즈 빌드) 

성공적으로 컴파일이 되었다면 ./a.out 으로 실행할 수 있고, submit.cpp파일을 제출하면 된다.
