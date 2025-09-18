/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: 
 * Usage: 
 */
#pragma once

{
  "shell_cmd": "g++ -std=c++20 -DLOCAL -Wall -Wshadow \"$file\" -o \"$file_base_name\" && timeout 5s ./$file_base_name < input.txt > output.txt 2> error.txt",
  "file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
  "working_dir": "${file_path}",
  "selector": "source.c++"
}