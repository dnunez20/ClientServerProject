cmake_minimum_required(VERSION 3.12)
project(CNProjectsOctober C)

set(CMAKE_C_STANDARD 99)

add_executable(CNProjectsOctober getfile_server.c getfile_client.c)