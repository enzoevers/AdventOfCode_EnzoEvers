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

A card looks as shown below. Note that the amount of numbers on each side of the `|` can be different.

```
        Winning numbers  Your numbers
Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
```

The number of points of a card is $2^{matchedWinningNumbers - 1}$.

The program will read the input line by line to process a single card.

While reading the numbers from the line they will be stored in a sorted manner.

```
Card sorted 1: 17 41 48 83 86 |  6  9 17 31 48 53 83 86
```

After this there are two sorted vectors. Now the program gets the first item from the winning number vector. The program iterates over the 'your number' vector until a match is found. It a match was found the program gets the second items from the winning number vector and continues iterating and comparing this with the 'your number' vector. This continues until the end of either of the vectors is met.
