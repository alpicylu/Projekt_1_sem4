cmake_minimum_required(VERSION 3.10)

#sets project name
project(Projekt_1)

#Adds the "-g" flag that includes debug info. If i were to somehow manually start the debugger with the executable file "Projekt_1" then it would be useful,
#but i rely on the automated solution provied by VSC. The tasks.json file generated by the debugger already adds this flag. 
#set(CMAKE_CXX_FLAGS "-g")

#creates a variable called SOURCES that contains all paths to files listed after it. In our case those are source and inc files
set(SOURCES src/main.cpp inc/heap.hh inc/packet.hh inc/person.hh src/person.cpp inc/debug.hh)

#creates an executable based on the name of the project and given sources
add_executable(${PROJECT_NAME} ${SOURCES})

#you need to include directories. for whatever reason, i did not need to include the src/ directory (maybe because it sees main() automatically and 
# where its located), but just to be safe, include all directories used in this here commad
target_include_directories(${PROJECT_NAME} PUBLIC inc/ src/)