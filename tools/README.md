# OxideNDS Tools

These tools are converters and other utilities made for OxideNDS. All of the current tools are made in C++ with the CMake build system.

You can run `make Debug` or `make Release` in this `tools` directory to build all of the tools at once, or `make bin` to build all tools in Release mode and move the binaries to `tools/bin`, which you can then add to your PATH if you want to,

Note that any OxideNDS-specific file formats are documented in [docs/file-format-specs](../docs/file-format-specs), and keep in mind that you can always use your own.

Below is a summary of every tool's purpose, current state, and a usage example. More detailed information can be found in the relevant tool's README.md.

| Tool                 | Purpose                                               | State                    | Example                                    |
| -------------------- | ----------------------------------------------------- | ------------------------ | ------------------------------------------ |
| [oxsmconv](oxsmconv) | Converts popular 3D model formats to the OXSM format. | Supports Wavefront .OBJ. | `oxsmconv cube.obj cube.oxsm --format obj` |

## Dependencies

All of the tools require the header-only cxxopts library to be in your include path, use for parsing command-line arguments. Further dependencies are specified in the relevant tool's README.md.
