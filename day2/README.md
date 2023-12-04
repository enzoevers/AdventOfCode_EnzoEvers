## Run

```bash
$ dotnet run
```

## Strategy

1. Get bag contents from `bagContents.txt`
2. Read line from `input.txt`
3. Get game ID
4. Separate line in subsets
5. For each subset check if it can happen within the bag contents
6. If it can happen, add the game ID to the running sum
7. Go back till 2 until all lines read
