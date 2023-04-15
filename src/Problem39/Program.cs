using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Problem39
{
    class Program
    {
        static void Main(string[] args)
        {
            int Candidate=0,CandiRes,MaxRes = 0;

            for (int p = 3; p < 1000; p++)
            {
                CandiRes = 0;
                for (int a = 1; a < p / 2; a++)
                {
                    for (int b=p/2; b>=a; b-- ){

                        if (p == a + b + Math.Sqrt(Math.Pow(a, 2) + Math.Pow(b, 2)))
                        {
                            CandiRes++;
                        }
                    
                    }
                }
                if (CandiRes > MaxRes)
                {
                    MaxRes = CandiRes;
                    Candidate = p;

                }


            }
            Console.Write(Convert.ToString(Candidate));
            Console.Read();

        }
    }
}
