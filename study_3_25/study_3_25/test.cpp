#include <iostream>
using namespace std;
static int months[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
int Getmonth(int year, int month)
{
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
    {
        return 29;
    }
    else
    {
        return months[month];
    }
}

int main() {
    int n;
    int year, month, day, plus;
    cin >> n;
    while (n--) {
        cin >> year >> month >> day >> plus;
        while (plus--)
        {
            if (day == Getmonth(year, month)) 
            {
                if (month == 12) 
                {
                    year++;
                    month = 1;
                    day = 1;
                }
                else {
                    month++;
                    day = 1;
                }
            }
            else {
                day++;
            }
        }
        printf("%d-%02d-%02d\n", year, month, day);
    }
    return 0;
}

//int main() {
//    int d1, d2;
//    cin >> d1 >> d2;
//    if (d1 < d2)
//    {
//        swap(d1, d2);
//    }
//    int cou = 1;
//    while (1)
//    {
//        if (d1 == d2)
//            break;
//        if (d2 % 100 == Getmonth(d2 / 10000, d2 / 100 % 100))
//        {
//            if (d2 / 100 % 100 == 12)
//            {
//                d2 += 10000 - 1130;
//            }
//            else
//            {
//                d2 = d2 / 100 * 100;
//                d2 += 101;
//            }
//        }
//        else
//        {
//            d2++;
//        }
//        cou++;
//    }
//    cout << cou << endl;
//}