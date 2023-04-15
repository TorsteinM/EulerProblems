using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Oppgave9
{
    class Program
    {
        static void Main(string[] args)
        {
            for(int c=800;c>100;c--)
            {
                for(int b=c/10;b<c;b++)
                {
                    for (int a = 1; a < b; a++)
                        if ((a * a) + (b * b) == (c * c) && (a + b + c) == 1000)
                            Console.WriteLine((a * b * c));
                }
            }
            Console.Read();
        }
    }
}
