using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;


namespace Oppgave26         // Sol: 983
{
    class Program
    {
        static void Main(string[] args)
        {
            int num=0;
            BigInteger biggest = new BigInteger();
            for (int i = 1; i < 1000; i++)
            {
                BigInteger nines = new BigInteger(9);

                for (int j = 0; j < 1200;j++ )
                {
                    if (nines % i == 0)
                    {
                        if (nines > biggest)
                        {
                            biggest = nines; 
                            num = i;                            
                        }
                        break;                           
                    }
                    nines = nines * 10 + 9;
                }
            }           
            Console.Write("Number: " + Convert.ToString(num) + "\nWith Recurrent cycle: " + Convert.ToString(biggest).Length);
            Console.Read();
 
        }
    }
}
