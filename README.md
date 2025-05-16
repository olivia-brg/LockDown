# LockDown
Password Manager - Personnal project for educationnal purpose

## HOW TO BUILD

Using VCPKG and CMake

### Prerequisites

- Install:
  - [CMake](https://cmake.org/download/)
  - [VCPKG](https://github.com/microsoft/vcpkg)
  - Crypto++ library (via VCPKG)

- Set environment variable:
  - Variable: `VCPKG_ROOT` | `C:\path\to\vcpkg`
- Add to Path:
  - `%VCPKG_ROOT%`

- First build: execute `"vcpkg install cryptopp"`

### General Instructions

1. Launch PowerShell
2. Navigate to the build directory
3. Execute the command:
	`cmake .. -DCMAKE_TOOLCHAIN_FILE="\$env\:VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake" -DCMAKE_BUILD_TYPE=Debug`
4. Execute the command:
	`cmake --build . --config Debug`

### Troubleshooting

If you encounter configuration errors, ensure that environment variables are set correctly.
Verify that all dependencies are installed correctly.
