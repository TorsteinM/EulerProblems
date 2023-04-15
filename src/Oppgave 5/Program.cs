using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Oppgave_5
{
    class Program
    {
        static void Main(string[] args)
        {
            List<int> primes = new List<int>();
            primes.Add(2);
            primes.Add(3);
            for (int i = 4; i < 18;i++ )
            {
                primes.Add(i);
            }
            primes.Add(18);
            primes.Add(19);
            primes.Add(20);
            primes.Reverse();

            int start = 96996900;
            int end = 3*start;

            for (int i = start; i < end; i++)
            {
                bool evenDis = true;
                foreach(var num in primes)
                {
                    double div=(double)i/(double)num;
                    if (div != Math.Floor(div))
                    {
                        evenDis = false;
                        break;
                    }
                }
                if (evenDis)
                {
                    Console.WriteLine(i);
                    break;
                }
                    
            }
            Console.WriteLine("Not Found\n");
            Console.Read();
        }
    }
}
