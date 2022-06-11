#!/usr/bin/python3
# -*- coding: utf-8 -*-

import os
import sys

project_path = os.getcwd()
build_path = project_path + '/build'

cmake_p = 'cmake'
build_mode = 'Debug'
generator_opt = '-G "Unix Makefiles"'

cmake_config_cmd = f'{cmake_p} {generator_opt} -S {project_path} -DCMAKE_BUILD_TYPE={build_mode} -B {build_path}'
cmake_build_cmd = f'{cmake_p} --build {build_path} --config {build_mode} --parallel 12 --target all'
cmake_clean_cmd = f'{cmake_p} --build {build_path} --target clean -- -j 12'


def main():
    if sys.argv[1] == '--config':
        print(cmake_config_cmd)
    elif sys.argv[1] == '--build':
        print(cmake_build_cmd)
    elif sys.argv[1] == '--clean':
        print(cmake_clean_cmd)


if __name__ == '__main__':
    main()
