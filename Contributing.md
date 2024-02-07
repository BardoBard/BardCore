# Contributing

As this is an open-source project, any contributions are welcome, as long as it follows these guidelines below.

Follow the [Build](https://github.com/BardoBard/BardCore/wiki/Installation#Build) instructions to get started with the project. \
Due to the fact that this project is a Visual Studio project, it's windows only, but the code should be cross-platform. \
Personally I use Jetbrains, but any IDE should work, as long as it follows the [conventions](#conventions).

## Conventions

This is a c++ project, which means that we'll be following basic c++ conventions, such as:

### General c++ conventions

- Use of `#pragma once` instead of include guards.
- Use of `#include <header>` instead of `#include "header"`.
- Use of `nullptr` instead of `NULL`.
- Use of `std::` instead of `using namespace std;`.
- Use of `auto` only when the type is obvious, preferably use the actual type.
- Use of `const` on parameters that are not meant to be modified.
- Use of reference`&` on non-primitive parameters that are `const`.
- Absolutely no use of c-style casts, use `static_cast`, `dynamic_cast`, `const_cast` and `reinterpret_cast` instead.

### Formatting

- Use of single tabs for indentation, with a tab size of 4.
- Use of space after pointers and references, e.g `int* ptr`.
- Use of space after commas, e.g `int a, int b`.
- Use of space after keywords, e.g `if (condition)`.
- No brackets for single-line `if` statements.
- Use of space after operators, e.g `int a = 5 + 5`.
- No or one space after `//`;

### Naming

- Use of [`snake_case`](https://en.wikipedia.org/wiki/Snake_case) for variables, functions, classes and directories.
- Use of [`UPPER_SNAKE_CASE`](https://en.wikipedia.org/wiki/Snake_case) for defines.
- Use of [`PascalCase`](https://en.wikipedia.org/wiki/Pascal_case) for generic type parameters, e.g `T`.
- Private/protected members should be postfixed with an underscore, e.g `int value_`.

### Comments

- Use `//` for single-line comments.
- Use `/* */` for multi-line comments.
- Use `/** */` for documentation comments, using doxygen style.
- For doxygen use ` \ ` instead of `@` for commands, e.g `\param` instead of `@param`.
- Use of `\note` for notes like formulas, references, etc.
- Comment only when necessary, and when it adds value to the code, like a formula, or a complex algorithm.

### Classes

- Variables don't have to be private, it's implementation dependent, for example if the variable can hold any value
  without breaking the class, it can be public.


- All classes are within the `bardcore` namespace, and should be named accordingly.
- Always use documentation comments for classes, explaining what the purpose of the class is.
- Use of `final` should be used when a class is not meant to be inherited from.
- Constructors and destructors should where possible be `explicit` and `constexpr`.
- Almost always add move semantics to classes e.g move constructor, move assignment operator.
- Almost always use assignment operator overloads, they are default constexpr and noexcept.
- Use of operator overloads should be used when it makes sense.

- Exception classes should be inherited from `bard_exception`.

### Functions

- Use of `constexpr` and `noexecpt` where possible.
- Use of `override` should always be used when overriding a function.
- Use [`NODISCARD`](https://github.com/search?q=repo%3ABardoBard%2FBardCore+NODISCARD+path%3A*%2Fbardcore.h&type=code)
  when a function returns a value that should not be discarded.
- Use [`INLINE`](https://github.com/search?q=repo%3ABardoBard%2FBardCore+INLINE+path%3A*%2Fbardcore.h&type=code) when a
  function should be inlined.
- Always use documentation comments for functions.

## Testing

This project uses Google Test for testing, and all code should be well tested. \
When adding new code, make sure to add tests that cover the new code. \
When fixing a bug, make sure to add a test that reproduces the bug.

The github environment has a CI/CD pipeline that runs the tests on every pull request, if the tests fail, the pull request will be rejected.

## Pull requests

If you want to contribute to this project, fork the repository, and make a pull request with the changes you want to make.

Make sure to follow the [conventions](#conventions) when making changes. \
Follow the [testing](#testing) guidelines when adding new code or fixing bugs. \
Make sure to add a description of the changes you made in the pull request. \
Make sure to add documentation comments to the code you added or changed.

## Feature requests

If you have a feature request, please open an issue with the `feature request` label, and describe the feature you want to be added. \
If you want to implement the feature yourself, please follow the [pull request](#pull-requests) guidelines.

# Thank you for contributing!

If you have any questions, feel free to ask in the [discussions section](https://github.com/BardoBard/BardCore/discussions/53).
