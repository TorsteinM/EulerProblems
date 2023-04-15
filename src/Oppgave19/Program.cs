using System;
using System.Globalization;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Oppg19
{
    class Program
    {
        static void Main(string[] args)
        {
            DateTime minDag = new DateTime(1901, 1, 1);
            DateTime sisteDag = new DateTime(2000, 12, 31);
            Calendar minKal = CultureInfo.InvariantCulture.Calendar;
            int antall=0;

            while (minDag < sisteDag)
            {
                minDag=minDag.AddDays(1);
                if (minKal.GetDayOfWeek(minDag) == DayOfWeek.Sunday)
                    if (minKal.GetDayOfMonth(minDag) == 1)
                        antall++;

            }

        }
    }
}
