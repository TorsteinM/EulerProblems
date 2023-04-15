using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Oppgave__24
{
    class Program
    {
        static int fact(int n)
        {
           if (n == 0)
               return 1;
           if(n==1)
             return 1;
           int result;

           result = fact(n-1) * n;
           return result;

        }

        static void Main(string[] args)
        {
            int num = 999999;
            UInt64 res = 0;

            List<int> liste = new List<int> { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            while (liste.Count>0)
            {
                int tall = fact(liste.Count() -1);
                int faktor = num / tall;
                num -= faktor * tall;
                int tegn=liste[Convert.ToInt32(faktor)];
                res*=10;
                res+=Convert.ToUInt64(tegn);

                liste.Remove(tegn);
            }
            Console.WriteLine(res);
            Console.Read();

        }
    }
}
