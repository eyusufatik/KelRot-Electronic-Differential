#include <math.h>

struct Coefficients
{
public:
    float leftK;
    float rightK;
};

/*

  <- angle measured here = aL
\------\  <- angle measured here = aR
   |  
   |  L
   |
|------|
  - W -

turning left:
r = L|cotaL| = L|cotaR| - W

turning right:
r = L|cotaR| = L|cotaL| - W

in-out analogy:
r = L|cotaIn| = L|cotaOut| - W

rin = sqrt(r^2 + L^2)
rout = sqrt((r+W)^2 + L^2)

rin     rout
---- = ------
Vin      Vout
*/

class Differential
{
private:
    float L; // distance between front and rear tear centers.
    float W; // distance between rear wheels

    inline double cot(double angle)
    {
        return 1 / tan(angle);
    }

public:
    Differential(float length, float width)
    {
        this->L = length;
        this->W = width;
    }
    // encoder will be on left wheel, steering left means positive angle.
    Coefficients getWheelCoefficients(double angle)
    {
        double r = 15;
        if (angle > 0)
        { // steering left, "alpha in" is the left wheel angle
            r = L * fabs(cot(angle));
        }
        else
        { // steering right, "alpha out" is the left wheel angle
            r = L * fabs(cot(angle));
        }
        double rIn = sqrt(pow(r, 2) + pow(L, 2));      // turning left rIn is the radius for left wheel; turning right rIn is the radius for right wheel
        double rOut = sqrt(pow(r + W, 2) + pow(L, 2)); // turning left rOut is the radius for right wheel; turning right rOut is the radius for left wheel

        Coefficients coefs;
        if (angle > 0)
        {
            coefs.rightK = 1.0;
            coefs.leftK = rIn / rOut;
        }
        else
        {
            coefs.leftK = 1.0;
            coefs.rightK = rIn / rOut;
        }
    }
};