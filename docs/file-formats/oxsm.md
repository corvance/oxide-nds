# **OX**ide **S**tatic **M**odel (.oxsm)

The .oxsm format is the engine's standard format for static models/meshes.
It contains the mesh vertices, textured coordinates and normal vertices, and indices (mesh/texture/normal).

A converter tool currently exists to create .oxsm files from Wavefront OBJ (.obj) models. Conversion from other formats it planned for a future release.

## Non-primitive Datatypes used

Note that the following datatypes are all identical in that they are just short ints (signed 16s), `typedef`'d to these names in libnds. It is in their interpretation that they differ.
The conversions from float32, int and fixed32 (f32) values can be found later in this specification.

- v16 - 4.12 fixed point format vertex component (usually representing X, Y or Z).
- t16 - 12.4 fixed point format texture coordinate component (usually representing X or Y).
- v10 - .10 fixed point format normal vertex component (usually representing X, Y or Z).

## Format

| Section              | Datatype | # Items (*n*) | Size (bytes) | Purpose                                                                                          |
| -------------------- | -------- | ------------- | ------------ | ------------------------------------------------------------------------------------------------ |
| Header               | `u32`    | 4             | 16           | Number of mesh vertices, number of texture coords, number of normal vertices, number of indices. |
| Mesh Vertex Coords   | `v16`    | ?             | *n* * 2      | Mesh vertex coords, repeating X, Y and Z, such that 3 v16 items makes up one vertex.             |
| Texture Coords       | `t16`    | ?             | *n* * 2      | Texture coords, repeating X and Y, such that 2 t16 items makes up one 2D vertex.                 |
| Normal Vertex Coords | `v10`    | ?             | *n* * 2      | Normal vertex coords, repeating X, Y and Z, such that 3 v16 items makes up one vertex.           |
| Indices              | `u32`    | ?             | *n* * 4      | Indices repeating Mesh / Texture / Normal, such that 3 u32s makes up one index.                  |

## Datatype conversions

The following is pseudocode demonstrating conversion from int (signed 32-bit on the NDS), float32 and fixed32 (f32). Be careful not to mix up float32 and fixed32/f32.

| Result Type | Int Conversion | Float32 Conversion                               | Fixed32 Conversion |
| ----------- | -------------- | ------------------------------------------------ | ------------------ |
| v16         | `n << 12`      | `n * (1 << 12)`                                  | `n`                |
| t16         | `n << 4`       | `n * (1 << 4)`                                   | `n >> 8`           |
| v10         | `n << 9`       | `if (n > 0.998) { 0x1FF } else { n * (1 << 9) }` | `n >> 3`           |
