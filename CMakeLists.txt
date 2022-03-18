cmake_minimum_required(VERSION 3.10)

#sets project name
project(Projekt_1)

#creates a variable called SOURCES that contains all paths to files listed after it. In our case those are source and inc files
set(SOURCES src/main.cpp src/heap.cpp inc/heap.hh)

#creates an executable based on the name of the project and given sources
add_executable(${PROJECT_NAME} ${SOURCES})

#you need to include directories. for whatever reason, i did not need to include the src/ directory (maybe because it sees main() automatically and 
# where its located), but just to be safe, include all directories used in this here commad
target_include_directories(${PROJECT_NAME} PUBLIC inc/ )