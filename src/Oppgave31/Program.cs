using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Oppgave31
{
    class Program
    {
        static void Main(string[] args)
        {
            int res=0;
            for (int tohundre = 0; tohundre < 2; tohundre++)
            {
                for (int etthundre = 0; etthundre < 3; etthundre++)
                {
                    for (int femti = 0; femti < 5; femti++)
                    {
                        for (int tjue = 0; tjue < 11; tjue++)
                        {
                            for (int ti = 0; ti < 21; ti++)
                            {
                                for (int fem = 0; fem < 41; fem++)
                                {
                                    for (int to = 0; to < 101; to++)
                                    {
                                        for (int en = 0; en < 201; en++)
                                        {
                                            if (tohundre * 200 + etthundre * 100 + femti * 50 + tjue * 20 + ti * 10 + fem * 5 + to * 2 + en == 200)
                                            {
                                                res++;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            Console.WriteLine(res);
            Console.Read();
        }
    }
}
