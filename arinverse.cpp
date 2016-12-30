/*
 * arinverse.cpp
 *
 *  Created on: 30-Dec-2016
 *      Author: ashish
 */

#include <armadillo>
#include <iostream>

using namespace std;
using namespace arma;
/*
 * Use case for armadillo linear regression.Match this with Scipy linear
 * regression
 * Spline Regression
 */
int main()
{
  int N = 15, knots = 3, degree = 3;  // No of Knots
  double knotposition[1] = {0};
  colvec m = colvec(N);
  colvec Y = colvec(N);
  colvec weights = colvec(N);
  mat w = mat(N, N, fill::eye);
  mat knot = mat(N, 0);
  mat knot1 = mat(N, knots - 1, fill::ones);
  mat X = mat(N, 0);
  m = {-0.158477440338,  -0.12001115951,   -0.101319026498, -0.0829698878299,
       -0.0649513823272, -0.0472518052278, -0.029860062516, -0.0127656291567,
       0.00404148915972, 0.0205707911109,  0.0368313119827, 0.0528316533292,
       0.0685800102973,  0.0840841968333,  0.099351668964};
  Y = {0.19357505,  0.06199442,  0.05568028,  0.03735449,
       0.02154209,  0.01434964,  0.00768336,  0.0026886,
       -0.00085119, -0.00336763, -0.00562633, -0.00404936,
       0.00620552,  0.01442895,  0.02548299

  };

  weights = {0.00824981, 0.00090933, 0.00343863, 0.00713315,
             0.01731971, 0.05311524, 0.12936418, 0.22869398,
             0.2626523,  0.18343916, 0.07515594, 0.02075028,
             0.00691378, 0.00206783, 0.00079667

  };

  w.diag() = weights;
  colvec m2 = ones(N);
  for (int i = 0; i < knots - 1; i++)
  {
    colvec c = colvec(N);
    if (i == 0)
      c = m - m.min();
    else
    {
      c = m - knotposition[i - 1];  // Change this w.r.t knot position
      c.transform([](double v) { return v > 0 ? v : 0; });
    }

    knot.insert_cols(i, c);
  }
  int nvars = degree + knots - 1;
  for (int i = 0; i < nvars; i++)
  {
    if (i < degree)
    {
      m2 = m2 % m;
      X.insert_cols(i, m2);
      knot1 = knot1 % knot;  // Potential Problem
    }
    else
    {
      X.insert_cols(i, knot1.col(i - degree));
    }
  }
  // cout << knot1 << endl << X << endl;
  // cout << armay << endl << m << m2 << m3;
  colvec A = pinv(X.t() * w * X) * (X.t() * w * Y);
  colvec res = Y - X * A;
  // std.errors of coefficients
  double s2 = std::inner_product(res.begin(), res.end(), res.begin(), 0.0) /
              (N - nvars);

  arma::colvec std_err =
      arma::sqrt(s2 * arma::diagvec(arma::pinv(arma::trans(X) * X)));
  /*
   * Spline Regression Algorithm
   * http://people.stat.sfu.ca/~cschwarz/Consulting/Trinity/Phase2/TrinityWorkshop/Workshop-handouts/TW-04-Intro-splines.pdf
   */
  cout << X << endl << A << endl << res << endl << std_err;

  return 0;
}
