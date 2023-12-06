## Strategy

The calculation for the distance is:

```
distance = (total_ms - hold_ms) * hold_ms
         = -(hold_ms^2) + (total_ms * hold_ms)
```

To win a minimum distance is required (`min_distance`):

```
distance > min_distance = -(hold_ms^2) + (total_ms * hold_ms) > min_distance
=> -(hold_ms^2) + (total_ms * hold_ms) > min_distance
=> (hold_ms^2) - (total_ms * hold_ms) < -min_distance
=> (hold_ms^2) - (total_ms * hold_ms) + min_distance < 0
```

Since all values are integers and the amount of different ways to win is required to know,
the `< 0` part can be replaces with `= -1`. This will result is either:

- `0` solution for `hold_ms`: no win possible
- `1` solution for `hold_ms`: one way of winning possible
- `2` solution2 for `hold_ms`: more than one way of winning possible

So finding the roots (in `hold_ms`) for the following

```
(hold_ms^2) - (total_ms * hold_ms) + min_distance = -1
=> (hold_ms^2) + (-total_ms * hold_ms) + (min_distance + 1) = 0
```

Roots are:

$$
\text{hold\\_ms} = \frac{\text{total\\_ms} \pm \sqrt{\left(-\text{total\\_ms}\right)^2 - \left(4 \cdot 1 \cdot \left(\text{min\\_distance} + 1\right)\right)}}{2 \cdot 1}
$$

Since it's possible that the result for `hold_ms` is a non-integer rounding is needed.

For the smaller `hold_ms` it's needed to round up and or the bigger `hold_ms` it's needed to round down. This due to the fact that we the result should be `>` and not `>=`.

$$
\text{hold\\_ms} = \left\lceil\frac{\text{total\\_ms} - \sqrt{\left(-\text{total\\_ms}\right)^2 - \left(4 \cdot 1 \cdot \left(\text{min\\_distance} + 1\right)\right)}}{2 \cdot 1}\right\rceil
$$

$$
\text{hold\\_ms} = \left\lfloor\frac{\text{total\\_ms} + \sqrt{\left(-\text{total\\_ms}\right)^2 - \left(4 \cdot 1 \cdot \left(\text{min\\_distance} + 1\right)\right)}}{2 \cdot 1}\right\rfloor
$$

From the [AoC example](https://adventofcode.com/2023/day/6):

```
Time:      7  15   30
Distance:  9  40  200
```

For round one `total_ms = 7`:

| `hold_ms` | `distance`                     |
| --------- | ------------------------------ |
| `0`       | -(`0`^2) + (`7` \* `0`) = `0`  |
| `1`       | -(`1`^2) + (`7` \* `1`) = `6`  |
| `2`       | -(`2`^2) + (`7` \* `2`) = `10` |
| `3`       | -(`3`^2) + (`7` \* `3`) = `12` |
| `4`       | -(`4`^2) + (`7` \* `4`) = `12` |
| `5`       | -(`5`^2) + (`7` \* `5`) = `10` |
| `6`       | -(`6`^2) + (`7` \* `6`) = `6`  |
| `7`       | -(`7`^2) + (`7` \* `7`) = `0`  |

This fold with the data from the example.

The roots are:

$$
\text{hold\\_ms} = \frac{7 \pm \sqrt{\left(-7\right)^2 - \left(4 \cdot \left(9 + 1\right)\right)}}{2}
$$

$$
\text{hold\\_ms} = \frac{7 \pm \sqrt{49 - 40}}{2}
$$

$$
\text{hold\\_ms} = \frac{7 \pm 3}{2}
$$

$$
\text{hold\\_ms} = \frac{7 \pm 3}{2}
$$

$$
\text{hold\\_ms} = \left\lceil\frac{7 - 3}{2}\right\rceil \lor \text{hold\\_ms} = \left\lfloor\frac{7 + 3}{2}\right\rfloor
$$

$$
\text{hold\\_ms} = 2 \lor \text{hold\\_ms} = 5
$$

Between these two values for `hold_ms` it is indeed possible to win.

## Solution

For the given input the answer should be:

```
Input:

Round:        0      1      2      3
Time:        53     89     76     98
Distance:   313   1090   1214   1201
```

### Round 0

$$
\text{hold\\_ms} = \frac{53 \pm \sqrt{\left(-53\right)^2 - \left(4 \cdot \left(313 + 1\right)\right)}}{2}
$$

$$
\text{hold\\_ms} = 7 \lor \text{hold\\_ms} = 46
$$

Possible wins: $46 - 7 + 1 = 40$

### Round 1

$$
\text{hold\\_ms} = \frac{89 \pm \sqrt{\left(-89\right)^2 - \left(4 \cdot \left(1090 + 1\right)\right)}}{2}
$$

$$
\text{hold\\_ms} = 15 \lor \text{hold\\_ms} = 74
$$

Possible wins: $74 - 15 + 1 = 60$

### Round 2

$$
\text{hold\\_ms} = \frac{76 \pm \sqrt{\left(-76\right)^2 - \left(4 \cdot \left(1214 + 1\right)\right)}}{2}
$$

$$
\text{hold\\_ms} = 23 \lor \text{hold\\_ms} = 53
$$

Possible wins: $53 - 23 + 1 = 31$

### Round 3

$$
\text{hold\\_ms} = \frac{98 \pm \sqrt{\left(-98\right)^2 - \left(4 \cdot \left(1201 + 1\right)\right)}}{2}
$$

$$
\text{hold\\_ms} = 15 \lor \text{hold\\_ms} = 83
$$

Possible wins: $83 - 15 + 1 = 69$

### Total possible ways

Total possible ways to win: $40 \cdot 60 \cdot 31 \cdot 69 = 5133600$

## Part 2

The input now is:

```
Input:

Time:              53897698
Distance:   313109012141201
```

$$
\text{hold\\_ms} = \frac{53897698 \pm \sqrt{\left(-53897698\right)^2 - \left(4 \cdot \left(313109012141201 + 1\right)\right)}}{2}
$$

$$
\text{hold\\_ms} = 6623214 \lor \text{hold\\_ms} = 47274484
$$

Possible wins: $47274484 - 6623214 + 1 = 40651271$
