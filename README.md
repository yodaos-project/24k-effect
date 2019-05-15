# 24K-Effect

24K-Effect is a software written in C that can use js to write lighting and sound effects.
It is designed to work well with very little memory.

## prepare

24K Depends on Jerryscript. you need clone jerryscript project to your pc first.

```shell
$ cd ~/workspace
$ git clone git@github.com:pando-project/jerryscript.git
```

## install

clone 24K project to your pc.

```shell
$ cd ~/workspace
$ git clone git@github.com:yodaos-project/24k-effect.git
```

Now we need to modify the configuration file. Edit `CMakeLists.txt`:

```txt
SET(JERRY_PATH /Users/lan/Documents/workspace/jerryscript)
```

find `JERRY_PATH`. You need to replace jerry's path with the real path of the 24K project on your computer.

Now we can start the installation.

```shell
$ cmake .
$ make
```

If nothing happens, the effect executable is generated under the root directory.

## run

```shell
$ ./effect
```

24K will load `example/render.js` and run it. You don't have real lighting on your computer, so it doesn't really work. You just see some logs.

Someday, I may be able to transplant real lighting devices to computers.

## component

Component is a cmake project that contains `CMakeLists.txt` files.

Component is stored in the component directory by default.

All components are compiled into a static library and linked to 24K-Effect executable. You can extend the function of 24K through component.

A minimum CMakeLists.txt file is as follows:

```txt
cmake_minimum_required(VERSION 3.5)
SET(COMPONENT_NAME your_component_name)

file(GLOB SOURCE_SRC *.c)

add_library(${COMPONENT_NAME} ${SOURCE_SRC})

register_component()
```

Don't forget to call register_component. It lets me know that I want to compile your component into a binary file.

## todo

- timer. Mainly used to implement the setTimeout function of JS.
- Subprocess management. such as suspend, continue, kill. now only have fork.
- Lighting that can run on a computer. So we can debug effects on pc.
- etc...