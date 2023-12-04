using GameAoC;

Game game = new Game();

int answer = game.getAnswer("./bagContents.txt", "./input.txt");

Console.WriteLine($"Answer: {answer}");
