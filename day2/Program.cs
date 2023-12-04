using GameAoC;

Game game = new Game();

int answerPart1 = game.getAnswerPart1("./bagContents.txt", "./input.txt");
int answerPart2 = game.getAnswerPart2("./input.txt");

Console.WriteLine($"Answer part 1: {answerPart1}");
Console.WriteLine($"Answer part 2: {answerPart2}");