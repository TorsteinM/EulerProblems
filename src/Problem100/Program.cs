using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

namespace Problem100
{
    class Program
    {
        static void Main(string[] args)
        {

            UInt64 oldT = 4;
            UInt64 T = 10;
            while (true)
            {
                T++;
                UInt64 B = Convert.ToUInt64(Math.Ceiling(Convert.ToDouble(T) / Math.Sqrt(2)));
                if (2*B*(B-1) == T*(T-1))
                {

                    
                    if (T > 1000000000000)
                    {
                        
                        break;
                    }
                    Console.Write(B + "\n");
                    T = Convert.ToUInt64((double)T * (double)T / (double)oldT);
                    oldT = T;
                }
                
            }

            Console.Read();
        }
    }
}
