# Tower of Hanoi Game

This project is a game developed using the Allegro 5 library, primarily targeting Windows platforms.

## About the Game

The Tower of Hanoi is a classic mathematical puzzle consisting of three rods and a number of disks of different sizes. The objective is to move all the disks from the first rod to the third rod, following these rules:

- Only one disk can be moved at a time.
- A disk can only be placed on top of a larger disk or on an empty rod.
- Disks must be moved using the three rods as intermediate steps.

The puzzle is often used to teach recursive algorithms and problem-solving techniques.

## Platform Compatibility

- The code uses Windows-specific Allegro extensions (`winalleg.h`), so it currently only compiles and runs on Windows.
- Running or compiling on macOS or Linux will likely cause errors due to platform-specific dependencies.

## Running the Project

To build and run the project on Windows:

1. Install Allegro 5 and its dependencies.
2. Compile using a compatible compiler (e.g., MSVC, MinGW).
3. Run the executable.

## Contribution and Portability

Contributions to improve cross-platform compatibility are welcome. If you want to adapt the project to macOS or Linux, please feel free to submit a pull request.
