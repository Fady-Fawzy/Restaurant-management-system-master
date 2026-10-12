# Restaurant Simulation

A C++ console simulation of restaurant order scheduling and resource allocation. Orders progress through pending, cooking, ready, service/delivery, and completion stages while chefs, tables, and scooters are assigned.

## Features and design

The simulation handles delivery, takeaway, dine-in, and combo orders, request and cancellation actions, interactive/silent modes, and output reports. `Restaurant` orchestrates each time step; order subclasses represent different service rules. Custom linked queues, priority queues, and array stacks support scheduling and state transitions. The queue owns its nodes; it does not own objects referenced by pointer payloads.

## Source layout

The original folder layout is preserved:

```text
Restaurant-management-system-master/
  Restaurant management system.sln
  Restaurant management system/
    main.cpp, Restaurant.cpp/.h, UI.cpp/.h
    Order.cpp/.h and order subclasses
    Chef.cpp/.h, Table.cpp/.h, Scooter.cpp/.h
    RequestAction.cpp/.h, CancelAction.cpp/.h
    LinkedQueue.h, PriQueue.h, ArrayStack.h
    Input1.txt ... Input6.txt and sample output reports
```

`tests/data_structures.cpp` checks FIFO/copy/reuse semantics, priority ordering and ties, stack behavior, and queue node lifetime. `CMakeLists.txt` offers a portable build without altering the Visual Studio project.

## Build and run

Use a C++17 compiler and CMake 3.16+:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

Run `restaurant` from the build directory (Windows multi-configuration builds may place it in `build/Debug/`). When prompted, supply the path to a bundled input file, a new output filename, and mode `2` for silent execution. For example, from `build/` on Linux:

```bash
cp "../Restaurant-management-system-master/Restaurant management system/Input1.txt" Input1.txt
printf 'Input1.txt\nresult.txt\n2\n' | timeout 30 ./restaurant
```

Alternatively, open the original solution in Visual Studio. Toolset requirements differ between configurations (`v143`/`v145`); use an installed toolset compatible with the selected configuration. There are no runtime API keys or external dependencies.

## Verification and limitations

CI builds the executable and runs data-structure tests under AddressSanitizer/UndefinedBehaviorSanitizer. The bundled Input1 scenario exceeded a 30-second timeout in silent mode; the original unmodified executable also timed out. CI therefore does not claim successful scenario completion. The regression tests cover data structures, not every scheduling rule or the accuracy of sample output files.

Input1 termination, missing/malformed input handling, and full-simulation pointer ownership need further review. On Windows, use a process timeout appropriate to your shell when investigating sample runs. Existing compiler warnings are recorded in the audit; they are not hidden with warning suppression. Further work should add exact expected-output fixtures, malformed input tests, and a full simulation memory audit before claiming production readiness.

## Credits

The executable identifies this as **Team 15**. Existing source attribution, including the stack template attribution, is preserved. This repository does not establish individual authorship of every component.
