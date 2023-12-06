## Test

```bash
$ make test && ./out/test
```

## Run app

```bash
$ make app && ./out/app input.txt
```

## Strategy

### Part 1

It is required to map a seed ID to a location ID. This location is found by doing multiple consecutive translations:

1. seed-to-soil
2. soil-to-fertilizer
3. fertilizer-to-water
4. water-to-light
5. light-to-temperature
6. temperature-to-humidity
7. humidity-to-location

A mapping:

```
seed-to-soil map:
50 98 2
52 50 48
```

means:

| seed  | soil  |
| ----- | ----- |
| 98-99 | 50-51 |
| 50-97 | 52-99 |

This mapping can be stored in the following structs:

```c++
struct Mapping {
    int srcStartId;
    int dstStartId;
    int range;

    // Mapping functions
};

struct MultiMap {
    std::vector<Mapping> mappings;

    // Mapping functions
};
```

In total the program would have 7 `MultiMap` struct instances. For each seed ID the location is identified by calling the 7 mapping functions consecutive.

### Part 2
