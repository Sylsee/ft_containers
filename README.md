# ft_containers

## Description

`ft_containers` is a project that aims to recreate C++ Standard Template Library (STL) containers: `vector`, `stack`, `map`, and `set`. This project is designed to help developers understand the inner workings of these fundamental data structures and is not meant to replace the STL but to be a teaching and learning tool.

## Installation

To install `ft_containers`, clone the repository to your local machine:

```sh
git clone git@github.com:Sylsee/ft_containers.git
cd ft_containers
```

Compile the project using the `make` command:

```sh
make
```

## Usage

After compiling, you can use the containers in your C++ code:

```cpp
#include "ft_containers/vector.hpp"

int main() {
    ft::vector<int> vec;
    vec.push_back(10);

    // ...
}
```

## Containers

- `ft::vector`: Similar to `std::vector`. It is a dynamic array that grows as needed.

- `ft::stack`: Similar to `std::stack`. It is a container adapter that gives the programmer the functionality of a stack - specifically, a FILO (first-in, last-out) data structure.

- `ft::map`: Similar to `std::map`. It is an associative container that stores elements formed by a combination of a key value and a mapped value.

- `ft::set`: Similar to `std::set`. It is an associative container that contains a sorted set of unique objects.

## License

`ft_containers` is licensed under the [MIT license](LICENSE).
