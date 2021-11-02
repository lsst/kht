cmake_minimum_required(VERSION 3.14)
project(kht)

find_package(pybind11 REQUIRED)

include_directories("../../include/kht/")
include_directories($ENV{CONDA_PREFIX}/include/eigen3)

set(PYTHON_MODULE_EXTENSION ".so")

pybind11_add_module(pykht kht.cc)
target_link_libraries(pykht PUBLIC kht)
configure_file(khtContinued.py khtContinued.py COPYONLY)
configure_file(__init__.py __init__.py COPYONLY)

