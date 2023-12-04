using System.IO;

namespace NamespaceInputParser
{
    public class InputParser
    {
        public void readFile(string filePath)
        {
            try
            {
                StreamReader sr = new StreamReader(filePath);

                string line = sr.ReadLine();

                while (line != null)
                {
                    Console.WriteLine(line);
                    line = sr.ReadLine();
                }

                sr.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine("Exception: " + e.Message);
            }
            finally
            {
                Console.WriteLine("Executing finally block.");
            }
        }
    }
}