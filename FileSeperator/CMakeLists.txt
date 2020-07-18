cmake_minimum_required(VERSION 3.16)
project(FileSeperator C)

set(CMAKE_C_STANDARD 11)

add_executable(FileSeperator main.c printHelper.h fileHelper.h pythagoreanMeans.h kmeans.h linearRegression.h usefulStats.h SUBMENU_LinearRegression.h globalDefinitions.h)