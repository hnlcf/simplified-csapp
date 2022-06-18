#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
import sys

project_path = os.getcwd()
build_path = project_path + '/build'

cmake_p = 'cmake'
build_mode = 'debug'
generator_opt = '-G "Unix Makefiles"'

cmake_config_cmd = f'{cmake_p} {generator_opt} -S {project_path} -DCMAKE_BUILD_TYPE={build_mode} -B {build_path}'
cmake_build_cmd = f'{cmake_p} --build {build_path} --config {build_mode} --parallel 12 --target all'
cmake_clean_cmd = f'{cmake_p} --build {build_path} --target clean'
cmake_test_cmd = f'ctest -C {build_mode} --verbose'


def main():
    if sys.argv[1] == '--config':
        os.system(cmake_config_cmd)
    elif sys.argv[1] == '--build':
        os.system(cmake_build_cmd)
    elif sys.argv[1] == '--clean':
        os.system(cmake_clean_cmd)
    elif sys.argv[1] == '--test':
        os.system(cmake_build_cmd)
        os.system(f'cd {build_path} && {cmake_test_cmd}')


if __name__ == '__main__':
    main()
