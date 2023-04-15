using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Oppgave7
{
    class Program
    {
        static void Main(string[] args)
        {
            List<int> primes = new List<int>();
            primes.Add(2);
            primes.Add(3);
            int nextPrime = 5;
            while (primes.Count < 100001)
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
                    primes.Add(nextPrime);
                }
                nextPrime += 2;

            }
        }
    }
}
