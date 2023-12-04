using System.IO;
using System.Numerics;

namespace GameAoC
{
    public class Game
    {
        public void getAnswer(in string constraintsFilePath, in string gamesFilePath)
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

                if (line != null)
                {
                    constraints = parseSubset(line);
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
                    int gameId = parseGameId(line);

                    parseSubset(line);
                    line = sr.ReadLine();
                }
            }
            finally
            {
                sr.Close();
            }

            return sum;
        }

        private int parseGameId(in string line)
        {
            // TODO: it is known that the game ID is near the beginning of the line.
            // Check the while string for ':' this isn't really efficient. But it's easy 
            string[] subStrings = line.Split(':');
            if (subStrings.Length != 2)
            {
                throw new FormatException();
            }

            string[] finerSubs = subStrings[0].Trim().Split(' ');
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

        private RGBCount parseSubset(in string rgbString)
        {
            string[] subStrings = rgbString.Split(',');

            RGBCount rgbCount = new RGBCount();

            foreach (string sub in subStrings)
            {
                processSubString(sub.Trim(), ref rgbCount);
            }

            return rgbCount;
        }

        // It is assumed that the whitespace around colorInfo has been trimmed
        private void processSubString(in string colorInfo, ref RGBCount rgbCount)
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
