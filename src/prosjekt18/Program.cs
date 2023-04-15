using System;
using System.Collections.Generic;
using System.Linq;



namespace prosjekt18
{
    class Program
    {

        static void Main(string[] args)
        {
            //Leser inn triangel fra fil:
            
            string[] Tall = System.IO.File.ReadAllLines("D:\\Euler\\prosjekt18\\p067_triangle.txt");
            List<int[]> Rekker = new List<int[]>();
            foreach(string streng in Tall )
            {
                int antall = (streng.Count() +1)/3;
                int[] Rekke = new int[antall];
                for(int i=0; i<antall; i++)
                {
                    Rekke[i] = Convert.ToInt32(streng.Substring(i*3, 2));

                }

                Rekker.Add(Rekke);                                      
            }


            
   //         int subtri = 4;
            int[] indekser={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4}; //must be changed for subtriangels larger than 5
            List<int[]> vekter= new List<int[]>();
            for (int i = 0; i < 5; i++)
            {
                vekter.Add(new int[(int)Math.Pow(2,i)]);
            }
            for (int subtri = 2; subtri < 6; subtri++)
            {
                int iter = 0;
                System.Diagnostics.Stopwatch clock = System.Diagnostics.Stopwatch.StartNew();
                for (int i = Rekker.Count - subtri; i > -1; i -= subtri - 1)
                {
                    for (int j = 0; j < Rekker[i].Count(); j++)
                    {
                        vekter[0][0] = Rekker[i][j];
                        for (int rad = 1; rad < subtri; rad++)
                        {
                            for (int vekt = 0; vekt < (int)Math.Pow(2, rad); vekt += 2)
                            {
                                vekter[rad][vekt] = vekter[rad - 1][vekt / 2] + Rekker[i + rad][j + indekser[vekt]];
                                vekter[rad][vekt + 1] = vekter[rad - 1][vekt / 2] + Rekker[i + rad][j + indekser[vekt + 1]];
                            }
                        }
                        Rekker[i][j] = vekter[subtri - 1].Max();
                        iter++;
                    }

                }
                if (subtri == 4)
                    Rekker[0][0] += Rekker[1].Max();
                Console.WriteLine("Result {0}. \nExecution time: {1} ms.\n{3}by{3} sub-triangle iterations: {2}.\n\n", Rekker[0][0], (float)clock.ElapsedTicks / (float)10000, iter, subtri);
            }

            Console.Read();
        }
    }
}
