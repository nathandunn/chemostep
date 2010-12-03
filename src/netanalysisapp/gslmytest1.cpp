#include <iostream>
using std::cout ; 
using std::endl ; 


// gsl stuff
#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multimin.h>
//#include <gsl/gsl_blas.h>
//#include <gsl/gsl_multifit_nlin.h>


double targetVector[50] =  { 0.0,0.092784013,0.17221333,0.239779511,0.296821414,0.344540247,0.384013169,0.416205572,0.441982164,0.462116984,0.477302437,0.488157453,0.495234848,0.499027967,0.49997668,0.498472785,0.494864892,0.489462816,0.482541543,0.474344808,0.465088316,0.454962642,0.444135851,0.432755851,0.420952517,0.408839596,0.39651643,0.384069496,0.371573803,0.359094136,0.346686184,0.334397543,0.322268628,0.310333482,0.298620508,0.28715312,0.275950332,0.26502728,0.254395695,0.24406432,0.234039289,0.224324456,0.214921703,0.205831198,0.197051637,0.188580456,0.180414016,0.17254777,0.164976412,0.157694007  } ; 


// A[ exp(-b1 t) - exp(-b2 t)] 
// v[0] = A, v[1] = b1, v[2] = b2
double funOverDamp( const gsl_vector *v, void *params){
  double A = gsl_vector_get(v,0) ;
  double b1 = gsl_vector_get(v,1) ;
  double b2 = gsl_vector_get(v,2) ;

//  cout << "A: " << A << endl ;
//  cout << "b1: " << b1 << endl ;
//  cout << "b2: " << b2 << endl ;

  double value ; 

  // if it is a vector, this could be done VERY fast, or using BLAS and can be done as a derivative
  double error = 0 ; 
  for(int i = 0 ; i < 50 ; i++){
      value =  (A * (  exp(- b1 * i) - exp( -b2 *  i ) ))  ;
//      cout << i << " value: "<< value << " vs target: " << targetVector[i] << endl ; 
      error += fabs( value - targetVector[i]) ; 
  }

  return error ; 

}


// d A[ exp(-b1 t) - exp(-b2 t)]  / dt = 
// -A [ b1 * exp(-b1 t) - b2 exp(-b2 t) ]
// params[0] = A, params[1] = b1, params[2] = b2
void funDerivOverDamp( const gsl_vector *v, void *params,
    gsl_vector *df )
{
  double A = gsl_vector_get(v,0) ;
  double b1 = gsl_vector_get(v,1) ;
  double b2 = gsl_vector_get(v,2) ;
  double *dp = (double *)params; // don't really need this, though

  double errorA = 0 ; 
  double errorB1 = 0 ; 
  double errorB2 = 0 ; 
  double valueA = 0 ; 
  double valueB1 = 0 ; 
  double valueB2 = 0 ; 

  for(int i = 0 ; i < 50 ; i++){
//      errorA += pow(  (  exp(- b1 * i) - exp( -b2 *  i ) )  -  targetVector[i],2.0)  ;
//      errorB1 += pow( (-A*b1*exp(- b1 * i))    -  targetVector[i],2.0)  ;
//      errorB2 += pow( (-A*b2*exp(- b2 * i))    -  targetVector[i],2.0)  ;
      valueA =  (  exp(- b1 * i) - exp( -b2 *  i ) )  ;
      valueB1 =  (-A*b1*exp(- b1 * i)) ;
      valueB2 =  (-A*b2*exp(- b2 * i)) ;
      errorA += fabs( valueA - targetVector[i]) ; 
      errorB1 += fabs( valueB1 - targetVector[i]) ; 
      errorB2 += fabs( valueB2 - targetVector[i]) ; 
//      cout << i << " valueA: "<< valueA << " valueB1: " << valueB1 << " valueB2: " << valueB2 << endl ; 
//      cout << i << " errorA: "<< errorA << " errorB1: " << errorB1 << " errorB2: " << errorB2 << endl ; 
  }
  

  gsl_vector_set(df,0,errorA ) ;
  gsl_vector_set(df,1,errorB1 ) ;
  gsl_vector_set(df,2,errorB2 ) ;
}


// calculate both together
void funCombineOverDamp (const gsl_vector *x, void *params, 
        double *f, gsl_vector *df) 
{
  *f = funOverDamp(x, params); 
  funDerivOverDamp(x, params, df);
}




// minimizes A[ exp(-b1 t) - exp(-b2 t)]
void test2(){
 size_t iter = 0;
  int status;

  const gsl_multimin_fdfminimizer_type *T;
  gsl_multimin_fdfminimizer *s;

  /* Position of the minimum (1,2). */
  double par[3] = { 0.1, 0.1, 0.2 };

  gsl_vector *x;
  gsl_multimin_function_fdf my_func;

  my_func.f = &funOverDamp;
  my_func.df = &funDerivOverDamp;
  my_func.fdf = &funCombineOverDamp;
  my_func.n = 3;
  my_func.params = &par;

  /* Starting point, x = (5,7) */
  x = gsl_vector_alloc (3);
  gsl_vector_set (x, 0, 1.8);  // initial parameter, A
  gsl_vector_set (x, 1, 0.06);  // initial parameter, b1
  gsl_vector_set (x, 2, 0.08);  // initial parameter, b2

  T = gsl_multimin_fdfminimizer_conjugate_fr;
  s = gsl_multimin_fdfminimizer_alloc (T, 3);

  gsl_multimin_fdfminimizer_set (s, &my_func, x, 0.01, 1e-6);

  do
    {
      iter++;
      status = gsl_multimin_fdfminimizer_iterate (s);

      if (status)
        break;

      status = gsl_multimin_test_gradient (s->gradient, 1e-3);

      if (status == GSL_SUCCESS)
        printf ("Minimum found at:\n");

//      printf ("%5d %.5f %.5f %10.5f\n", iter, gsl_vector_get( s->x,0),s->f) ; 

      printf ("iter=%5d A=%.5f b1=%.5f b2=%.5f min?=%10.5f\n",
              iter,
              gsl_vector_get (s->x, 0), 
              gsl_vector_get (s->x, 1), 
              gsl_vector_get (s->x, 2), 
              s->f);

    }
  while (status == GSL_CONTINUE && iter < 1000);

  gsl_multimin_fdfminimizer_free (s);
  gsl_vector_free (x);

}

// minimizes A exp(-b t) sin(P t )
//void test3(){
//
//}



/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{


    gsl_vector* test ; 
    gsl_vector_set(test,0,2) ; 
    gsl_vector_set(test,1,0.05) ; 
    gsl_vector_set(test,2,0.1) ; 

    cout << "perfect error: " << funOverDamp(test,NULL) << endl ;

//   test1() ;  // minimizes a sample parabolic function
   test2() ;  // minimizes A[ exp(-b1 t) - exp(-b2 t)]
//   test3() ;  // minimizes A exp(-b t) sin(P t )


    return 0;
} /* }}} */



// -*- C++ -*-

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>

//    cout << "Attempts at minimization function over data, differentiatior is broken (since its data)." << endl ;

