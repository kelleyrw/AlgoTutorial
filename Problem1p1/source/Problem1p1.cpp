#include "SimpleTable.h"
#include <cmath>

// all in microseconds
static const double nmsec_sec     = 1e6;
static const double nmsec_min     = 60*nmsec_sec;
static const double nmsec_hour    = 60*nmsec_min;
static const double nmsec_day     = 24*nmsec_hour;
static const double nmsec_month   = 30*nmsec_day;
static const double nmsec_year    = 365*nmsec_day;
static const double nmsec_century = 100*nmsec_year;

// f(n)^-1 
double fm1_logn (const double t) {return std::exp(t);          }
double fm1_sqrtn(const double t) {return t*t;                  }
double fm1_n    (const double t) {return t;                    }
double fm1_nlogn(const double t) {return -1;/*transendental?*/ }
double fm1_n2   (const double t) {return std::sqrt(t);         }
double fm1_n3   (const double t) {return std::pow(t,(1.0/3.0));}
double fm1_2n   (const double t) {return 2*std::log(t);        }
double fm1_nfac (const double t) {return -1;/*transendental?*/ }

int main()
{
    SimpleTable table;
    table.useTitle();
    table.setTitle("table 1: results from problem 1.1");
    table.setTable()
        (                        "1 s"    ,              "1 min",                "1 hr",              "1 day",              "1 month",              "1 year",              "1 century")
        ("log(n)"   , fm1_logn (nmsec_sec), fm1_logn (nmsec_min), fm1_logn (nmsec_hour), fm1_logn (nmsec_day), fm1_logn (nmsec_month), fm1_logn (nmsec_year), fm1_logn (nmsec_century))
        ("sqrt(n)"  , fm1_sqrtn(nmsec_sec), fm1_sqrtn(nmsec_min), fm1_sqrtn(nmsec_hour), fm1_sqrtn(nmsec_day), fm1_sqrtn(nmsec_month), fm1_sqrtn(nmsec_year), fm1_sqrtn(nmsec_century))
        ("n"        , fm1_n    (nmsec_sec), fm1_n    (nmsec_min), fm1_n    (nmsec_hour), fm1_n    (nmsec_day), fm1_n    (nmsec_month), fm1_n    (nmsec_year), fm1_n    (nmsec_century))
        ("n log n"  , fm1_nlogn(nmsec_sec), fm1_nlogn(nmsec_min), fm1_nlogn(nmsec_hour), fm1_nlogn(nmsec_day), fm1_nlogn(nmsec_month), fm1_nlogn(nmsec_year), fm1_nlogn(nmsec_century))
        ("n^2"      , fm1_n2   (nmsec_sec), fm1_n2   (nmsec_min), fm1_n2   (nmsec_hour), fm1_n2   (nmsec_day), fm1_n2   (nmsec_month), fm1_n2   (nmsec_year), fm1_n2   (nmsec_century))
        ("n^3"      , fm1_n3   (nmsec_sec), fm1_n3   (nmsec_min), fm1_n3   (nmsec_hour), fm1_n3   (nmsec_day), fm1_n3   (nmsec_month), fm1_n3   (nmsec_year), fm1_n3   (nmsec_century))
        ("2^n"      , fm1_2n   (nmsec_sec), fm1_2n   (nmsec_min), fm1_2n   (nmsec_hour), fm1_2n   (nmsec_day), fm1_2n   (nmsec_month), fm1_2n   (nmsec_year), fm1_2n   (nmsec_century))
        ("n!"       , fm1_nfac (nmsec_sec), fm1_nfac (nmsec_min), fm1_nfac (nmsec_hour), fm1_nfac (nmsec_day), fm1_nfac (nmsec_month), fm1_nfac (nmsec_year), fm1_nfac (nmsec_century))
        ;
    table.print();
    return 0;
}
