using System;
using System.IO;

namespace Lab9 {
    
    class Program {

        static void Main() {
            string logFile = "log.txt";
            LogMessage(logFile, "[INFO] Program started.");

            Console.WriteLine("Enter a number of barrels(< 100):");

            int n;
            while (true) {
                string? input = Console.ReadLine();
                if (int.TryParse(input, out n) && n > 0 && n < 100) {
                    Console.WriteLine($"You entered {n}. Generating barrels...");
                    LogMessage(logFile, $"[INFO] User entered valid input: {n}");
                    break;
                } else {
                    Console.WriteLine("Invalid input. Please enter a positive integer lower than 100:");
                    LogMessage(logFile, $"[ERROR] Invalid input {input}. User must enter a positive integer lower than 100.");
                }
            }

            Console.WriteLine("Press Enter to get the next number.\nWrite <exit> to end the game.");

            int[] barrel = CreateRandomArray(n, logFile);
            int k = 0;

            while (k < n) {
                Console.Write("Your action: ");
                string? exit = Console.ReadLine();

                if (exit?.ToLower() == "exit") {
                    Console.WriteLine("Exiting the game. Thanks for playing!");
                    LogMessage(logFile, "[INFO] User exited the game.");
                    break;
                }

                Console.WriteLine($"Barrel {k + 1}: {barrel[k]}");
                LogMessage(logFile, $"[INFO] Barrel {k + 1} retrieved: {barrel[k]}");
                k++;

                if (k == n) {
                    Console.WriteLine("You have got all barrels.");
                    LogMessage(logFile, "[INFO] User retrieved all barrels.");
                    break;
                }
            }

            LogMessage(logFile, "[INFO] Program ended.");
        }

        static int[] CreateRandomArray(int n, string logFile) {
            LogMessage(logFile, "[INFO] Creating and shuffling barrels...");

            int[] array = new int[n];
            for (int i = 0; i < n; i++) {
                array[i] = i + 1;
            }

            Random random = new Random();
            for (int i = array.Length - 1; i > 0; i--) {
                int j = random.Next(0, i + 1);
                (array[i], array[j]) = (array[j], array[i]);
            }

            LogMessage(logFile, "[INFO] Barrels shuffled successfully.");
            return array;
        }

        static void LogMessage(string filePath, string message) {
            string timestamp = DateTime.Now.ToString("dd.MM.yyyy HH:mm:ss");
            string logEntry = $"{timestamp}: {message}";

            try {
                File.AppendAllText(filePath, logEntry + Environment.NewLine);
            } catch (Exception ex) {
                Console.WriteLine($"Failed to write to log file: {ex.Message}");
            }
        }
    }
}
