cmake_minimum_required(VERSION 2.8)

project(cworld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -lSDL -lGL -lGLU")

add_executable(cworld main.cpp FreeFlyCam.cpp
    #znoise
    znoise/MixerBase.cpp
    znoise/NoiseBase.cpp
    znoise/NoiseTools.cpp
    znoise/Simplex.cpp
    znoise/Perlin.cpp
    znoise/Worley.cpp
    znoise/FBM.cpp
    znoise/HybridMultiFractal.cpp
    
    #map
    map/map.cpp
    map/water.cpp
    map/planet.cpp
    
    #crea
    crea/crea.cpp
    )
    
    
