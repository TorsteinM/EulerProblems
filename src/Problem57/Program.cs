using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Problem57
{
    class Program
    {
        static double recur(int rank)
        {
            if (rank==0){
                return 2;
            }
            else
            {
                return 2+1/recur(rank-1);
            }
        }

        static void Main(string[] args)
        {
            double res = 0;
            for (int rank = 1; rank < 20; rank++)
            {
                res = recur(rank);
                Console.Write(Convert.ToString(res)+"\n");

            }
            Console.Read();
        }
    }
}
