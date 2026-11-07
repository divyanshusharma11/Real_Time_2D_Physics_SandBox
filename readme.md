# Real-Time 2D Physics Sandbox

A real-time particle physics simulation developed using **C++17 and Raylib**. The project focuses on simulating thousands of particles through gravity, collision detection, and efficient rendering.

## Problem Statement

As the number of particles increases, collision detection and physics calculations become computationally expensive. Traditional brute-force collision detection (O(n²)) can significantly reduce simulation performance.

This project aims to build a physics engine from scratch, implementing efficient collision detection, particle movement, and optimization techniques to maintain smooth real-time performance.

## Key Features

- Real-time particle simulation.
- Gravity and Verlet integration.
- Particle collision detection and resolution.
- Circular boundary constraints.
- Speed-based dynamic particle colours.
- Interactive particle spawning using mouse input.
- Real-time FPS and particle count monitoring.
- Spatial hashing for collision optimization (planned).

## Tech Stack

| Technology | Purpose |
|---|---|
| C++17 | Core development |
| Raylib | Graphics and rendering |
| CMake | Build system |
| Git & GitHub | Version control and collaboration |
| Visual Studio Code | Development environment |

## Project Architecture

```text
Project/
├── CMakeLists.txt
├── README.md
├── main.cpp
└── src/
    ├── solver.hpp
    └── ui.hpp
```

- **solver.hpp:** Particle management, gravity, Verlet integration, and collision handling.
- **ui.hpp:** Rendering helpers, speed-based colours, and HUD.
- **main.cpp:** Integrates physics, rendering, and user interaction.

## Team Responsibilities

| Developer | Responsibilities |
|---|---|
| Divyanshu | UI, rendering, HUD, dynamic colours, mouse interaction |
| Ashwani | Physics engine, particle management, gravity, collision detection |

## Development Roadmap

1. Project setup and core particle simulation.
2. Verlet integration and gravity.
3. Collision detection and resolution.
4. Rendering and user interaction.
5. Spatial hashing and performance optimization.
6. Benchmarking and final demonstration.

## Performance Goals

- Maintain approximately 60 FPS.
- Scale simulation to 10,000–20,000+ particles.
- Reduce collision checks from O(n²) to approximately O(n) using spatial hashing.

*Performance targets will be validated through benchmarking.*

## Collaboration

Development follows a GitHub-based workflow using feature branches, commits, Pull Requests, code reviews, and merges.

## Contributors

- **Divyanshu**
- **Ashwani**