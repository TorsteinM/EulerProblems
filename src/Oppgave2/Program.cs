using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Oppgave2
{
    class Program
    {
        static void Main(string[] args)
        {
            int dummy, forrige = 1, ny = 2, Res = 0;
            while (ny < 4000000)
            { 
                if (ny % 2 == 0)
                    Res += ny;
                dummy = ny;
                ny += forrige;
                forrige = dummy;

            }

            Console.WriteLine(Res);
        }
    }
}
