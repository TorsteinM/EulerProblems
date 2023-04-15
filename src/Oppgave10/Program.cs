using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Oppgave10
{
    class Program
    {
        static void Main(string[] args)
        {
            long primes = 5;
            int nextPrime = 5;
            while (nextPrime < 2000001)
            {
                int sqrt = (int)Math.Sqrt(nextPrime);
                bool isPrime = true;
                for (int i = 2; i <= sqrt; i++)
                {
                    if (nextPrime % i == 0)
                    {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime)
                {
                    primes += nextPrime;
                }
                nextPrime += 2;

            }
            Console.WriteLine(primes);
            Console.Read();

        }
    }
}
