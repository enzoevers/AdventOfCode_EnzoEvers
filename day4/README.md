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

The number of points of a card depends on the matched winning number (W): $2^{W - 1}$.

The program will read the input line by line to process a single card.

While reading the numbers from the line they will be stored in a sorted manner.

```
Card sorted 1: 17 41 48 83 86 |  6  9 17 31 48 53 83 86
```

After this there are two sorted vectors. Now the program gets the first item from the winning number vector. The program iterates over the 'your number' vector until a match is found. If a current winning number is less than the one of my numbers, the next winning number is checked instead. It a match was found the program gets the second items from the winning number vector and continues iterating and comparing this with the 'your number' vector. This continues until the end of either of the vectors is met.

### Part 2

For part two the number of total scratch cards needs to be determined, taking into account all the copies. Additionally, there are no more cards than there are in the input. So if the last card ID is 10, then there can be no card 11.

First it's required to know how much matched winning numbers a card has. This indicated which cards get a copy.

When starting from card 1 and going down (increasing ID), the IDs `<=` the current ID cannot be copied anymore.

At the start of the program there is a vector that maps card IDs to their total count (1 + number of copies). The index of the map is `the card ID - 1` (card IDs start at 1). Whenever the match-count of a card is found the copy count for the next match-count number of IDs is increased by `1 * number_of_copies_of_current_card`.

The total number of cards is then the
