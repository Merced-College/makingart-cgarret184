[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=22335415)
# cpp_makingArt

This small project generates a `mandelbrot.html` file using a single C++ source file (`main.cpp`). Below are step-by-step instructions students can follow to build, run, and preview the output.

## Requirements

- A C++ compiler that supports C++17 (e.g. `g++` or `clang++`).
- `make` (optional, but a `Makefile` is included).

## Build & Run (quick)

1. Build using `make` (recommended):

   ```bash
   make
   ```

   Or compile directly with `g++`:

   ```bash
   g++ -std=c++17 -O2 -o mandelbrot main.cpp
   ```

2. Run to generate the HTML:

   ```bash
   make run
   # or
   ./mandelbrot
   ```

   This will create `mandelbrot.html` in the project directory and print a message to the console.

3. Preview the output

- In a cloud IDE: right-click `mandelbrot.html` in the file explorer and select **Preview** or **Open in Browser**.
- From the terminal (host browser):

  ```bash
  $BROWSER file://$PWD/mandelbrot.html
  ```

- Or serve the directory and open it in a browser:

  ```bash
  python3 -m http.server 8000
  # then open http://localhost:8000/mandelbrot.html
  ```

4. Clean build artifacts:

   ```bash
   make clean
   ```

## Makefile details and explanation

The repository includes a simple `Makefile` to make building and running easier. Below is the file content and an explanation of each part:

```makefile
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGET = mandelbrot
SRC = main.cpp

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) mandelbrot.html
```

Explanation:

- **Variables**
  - `CXX` — the C++ compiler used (default: `g++`). Change this to `clang++` if you prefer.
  - `CXXFLAGS` — compiler flags: `-std=c++17` sets the language standard, `-O2` enables optimizations, and `-Wall -Wextra` enable common warnings.
  - `TARGET` — the output binary name (`mandelbrot`).
  - `SRC` — the source file(s) to compile (`main.cpp`).

- **`.PHONY`**: declares `all`, `clean`, and `run` as phony targets (not actual files) so `make` always executes their recipes.

- **Targets**
  - `all` (default): depends on `$(TARGET)` and builds the program.
  - `$(TARGET)`: the rule that builds the binary from `$(SRC)` using the command `$(CXX) $(CXXFLAGS) -o $@ $^` where `$@` is the target name and `$^` are the prerequisites (sources).
  - `run`: depends on `$(TARGET)` and then runs `./$(TARGET)` to generate `mandelbrot.html`.
  - `clean`: removes the binary and the generated `mandelbrot.html` file (`rm -f $(TARGET) mandelbrot.html`).

Usage examples:

- Build: `make` (or `make all`)
- Build and run: `make run` (or `make && ./mandelbrot`)
- Clean: `make clean`


