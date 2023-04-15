using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Oppgave4
{
    class Program
    {
        static int Reverse(int num)
        {
            int rev_num = 0;
            while(num > 0)
            {
                rev_num = rev_num*10 + num%10;
                num = num/10;
            }
            return rev_num;
        }


        static void Main(string[] args)
        {

            int res = 0;
            int start = 100, stop = 1000;

            for (int i=start; i<stop; i++)
            {
                for (int j = start; j < stop; j++)
                {
                    int num = i * j;
                    if (num == Reverse(num))
                        if (num > res)
                            res = num;



                }
            }
        }
    }
}
