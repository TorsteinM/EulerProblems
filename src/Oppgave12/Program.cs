using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Oppgave12
{
    class Program
    {
        static long Triangle(long num)
        {
            return (num * (num + 1) / 2);
        }

        static void Main(string[] args)
        {
            int maxcount = 1;
            int start = 10000;
            int end = 50000;
            Console.WriteLine("Starting.\n");
            for (int tall=start;tall<end;tall++)
            {
                Console.SetCursorPosition(0, Console.CursorTop - 1); 
                Console.WriteLine(String.Format("Progress: {0}%.\tMaximum amount of divisors so far: {1}.",(tall-start)*100/(end-start),maxcount));
                long TrianNum = Triangle(tall);
                List<long> factors = new List<long>();
                factors.Add(1);
                factors.Add(TrianNum);
                double root = Math.Sqrt((double)TrianNum);
                if (root == Math.Floor(root))
                    factors.Add((long)root);

                for (long fact = 2; fact < root; fact++)
                {
                    double div = (double)TrianNum / (double)fact;
                    if (div == Math.Floor(div))
                    {
                        factors.Add(fact);
                        factors.Add(TrianNum / fact);
                    }

                }
                int count = factors.Count;
                if (count > maxcount)
                    maxcount = count;
                if (count > 500 )
                {
                    Console.SetCursorPosition(0, Console.CursorTop - 1); 
                    Console.WriteLine(String.Format("\nFirst triangle number with over 500 divisors: {0}",TrianNum));
                    break;
                }
            }
            Console.SetCursorPosition(0, Console.CursorTop - 1);
            Console.WriteLine(String.Format("Finished.             \nMaximum number of divisors found was {0}. \n\nPush a Key to Exit...",maxcount));
            Console.Read();
        }
    }
}
