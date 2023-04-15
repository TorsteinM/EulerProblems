using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Oppgave3
{
    class Program
    {

        static void Main(string[] args)
        {
            long res = 0, nr = 600851475143;


            List<int> primes = new List<int>();
            int nextPrime = 599;
            while (primes.Count < 50000)
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

           
            Console.Write("\nMathing primes...");
            foreach(var prime in primes)
            {
                if (nr % prime == 0)
                {
                    nr = nr / prime;
                    if (prime > res)
                        res = prime;
                }

            }
 
            Console.Write("\nResult: ");
            Console.Write(res);
            Console.Read();
        }
    }
}
