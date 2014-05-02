require 'mkmf-rice'

$CXXFLAGS = '-std=c++0x -O3 -g -Wall' # TODO: -Werror

create_makefile 'tasks_generator/tasks_generator'
