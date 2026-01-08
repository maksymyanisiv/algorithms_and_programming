#include <iostream>
#include <iomanip>
#include <cmath>
 
using namespace std;
 
int main()
{
   double x, xp, xk, dx, y, R;

   // Валідація вводу R
   do {
       cout << "R = "; 
       cin >> R;
       if (R <= 0) {
           cout << "Помилка: R має бути більше 0. Спробуйте ще раз." << endl;
       }
   } while (R <= 0);

   // Валідація вводу xp та xk
   do {
       cout << "xp = "; cin >> xp;
       cout << "xk = "; cin >> xk;
       if (xp >= xk) {
           cout << "Помилка: xp має бути менше xk. Спробуйте ще раз." << endl;
       }
   } while (xp >= xk);

   // Валідація вводу dx
   do {
       cout << "dx = "; 
       cin >> dx;
       if (dx <= 0) {
           cout << "Помилка: dx має бути більше 0. Спробуйте ще раз." << endl;
       }
   } while (dx <= 0);
 
   cout << fixed;
   cout << "================================================" << endl;
   cout << "|" << setw(12) << "x" << " |"
       << setw(12) << "y" << " |"
       << setw(12) << "R" << " |" << endl;
   cout << "================================================" << endl;
 
   x = xp;
   while (x <= xk)
   {
       if (x <= -R)
           y = R;
       else
           if (-R < x && x <= R)
               y = R - sqrt(R * R - x * x);
           else
               if (R <= x && x <= 6)
                   y = ((-3 - R) / (6 - R)) * (x - R) + R;
               else
                   if (6 <= x)
                       y = -9 + x;
       cout << "|" << setw(12) << setprecision(4) << x
           << " |" << setw(12) << setprecision(4) << y
           << " |" << setw(12) << setprecision(4) << R
           << " |" << endl;
 
       x += dx;
    }
 
   cout << "================================================" << endl;
   return 0;
}

