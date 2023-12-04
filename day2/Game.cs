using System.IO;
using System.Numerics;

namespace GameAoC
{
    public class Game
    {
        public int getAnswer(in string constraintsFilePath, in string gamesFilePath)
        {
            RGBCount constraints = processConstraints(constraintsFilePath);
            return processGames(constraints, gamesFilePath);
        }

        private RGBCount processConstraints(in string constraintsFilePath)
        {
            int lineCount = File.ReadLines(constraintsFilePath).Count();
            if (lineCount != 1)
            {
                throw new FormatException("Constraints file is expected to have only 1 line");
            }

            RGBCount constraints = new RGBCount();

            StreamReader sr = new StreamReader(constraintsFilePath);

            try
            {
                string line = sr.ReadLine();

                // The constraint only has a single line
                if (line != null)
                {
                    // Note that the constraints file has the same layout as
                    // a single round in a game.
                    parseRoundInGame(line, ref constraints);
                }
            }
            finally
            {
                sr.Close();
            }


            return constraints;
        }

        private int processGames(in RGBCount constraints, in string gamesFilePath)
        {
            int sum = 0;

            StreamReader sr = new StreamReader(gamesFilePath);
            try
            {
                string line = sr.ReadLine();

                while (line != null)
                {
                    string[] mainSubstring = splitGameInIdAndRound(line);
                    int gameId = parseGameId(mainSubstring[0]);
                    bool gameIsPossible = parseGameRounds(constraints, mainSubstring[1]);
                    if (gameIsPossible)
                    {
                        Console.WriteLine($"gameId: {gameId}");
                        sum += gameId;
                    }

                    line = sr.ReadLine();
                }
            }
            finally
            {
                sr.Close();
            }

            return sum;
        }

        private string[] splitGameInIdAndRound(in string line)
        {
            // TODO: it is known that the game ID is near the beginning of the line.
            // Check the while string for ':' this isn't really efficient. But it's easy 
            string[] subStrings = line.Split(':');
            if (subStrings.Length != 2)
            {
                throw new FormatException();
            }

            subStrings[0] = subStrings[0].Trim();
            subStrings[1] = subStrings[1].Trim();

            return subStrings;
        }

        private int parseGameId(in string gameIdString)
        {
            string[] finerSubs = gameIdString.Split(' ');
            if (finerSubs.Length != 2)
            {
                throw new FormatException();
            }

            int gameId = -1;
            try
            {
                gameId = int.Parse(finerSubs[1]);
            }
            catch (FormatException e)
            {
                Console.WriteLine(e.Message);
            }

            return gameId;
        }

        private bool parseGameRounds(in RGBCount constraints, in string roundsString)
        {
            string[] rounds = roundsString.Split(';');

            bool gameIsPossible = true;

            RGBCount rgbCount = new RGBCount();

            foreach (string round in rounds)
            {
                parseRoundInGame(round.Trim(), ref rgbCount);
                if (!(rgbCount <= constraints))
                {
                    gameIsPossible = false;
                    break;
                }
            }

            return gameIsPossible;
        }

        private void parseRoundInGame(in string rgbString, ref RGBCount rgbCount)
        {
            string[] subStrings = rgbString.Split(',');

            foreach (string sub in subStrings)
            {
                processColorInRound(sub.Trim(), ref rgbCount);
            }
        }

        // It is assumed that the whitespace around colorInfo has been trimmed
        private void processColorInRound(in string colorInfo, ref RGBCount rgbCount)
        {
            string[] finerSubs = colorInfo.Split(' ');
            if (finerSubs.Length != 2)
            {
                throw new FormatException();
            }

            int count = 0;
            try
            {
                count = int.Parse(finerSubs[0]);
            }
            catch (FormatException e)
            {
                Console.WriteLine(e.Message);
            }

            switch (finerSubs[1])
            {
                case "red":
                    {
                        rgbCount.rCount = count;
                        break;
                    }
                case "green":
                    {
                        rgbCount.gCount = count;
                        break;
                    }
                case "blue":
                    {
                        rgbCount.bCount = count;
                        break;
                    }
                default:
                    {
                        throw new FormatException();
                    }
            }
        }
    }
}
