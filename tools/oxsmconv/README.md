# oxsmconv

This is a utility to convert popular 3D model formats to the OXide Static Model .oxsm binary format.

## Building

```bash
cmake --build build --config Debug  # Debug
cmake --build build --config Release  # Release
```

## Usage

Show help:

```bash
oxsmconv -h      # Or,
oxsmconv --help
```

Convert an OBJ model to an OXSM model:

```bash
oxsmconv --format obj cube.obj cube.oxsm
```

## Formats

| Option Name | Format        |
| ----------- | ------------- |
| `obj`       | Wavefront OBJ |

## See Also

- [.oxsm format specification](../../docs/file-format-specs/OXideStaticModel.md)
