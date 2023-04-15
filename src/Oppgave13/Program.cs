using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Oppgave13
{
    class Program
    {
        static void Main(string[] args)
        {
            
            double res = 0;
            string[] Tall= System.IO.File.ReadAllLines("D:\\Euler\\Oppgave13\\numbers.txt");
            
            for (int i=40; i>=0; i-=10)
            {
                res=res/10000000000;
                foreach(string num in Tall)
                {
                    res += Convert.ToDouble(num.Substring(i,10));
                }
            }
        }
    }
}
