using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Oppgave16
{
    class Program
    {
        static void Main(string[] args)
        {
            string str=Convert.ToString(Math.Pow(2,1000));
            int res=0;
            for( int i=0;i<str.Count();i++)
            {
                res += Convert.ToInt32(str.Substring(i, 1));
            }

            
        }
    }
}
