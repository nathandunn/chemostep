#include <iostream>
using std::cout ; 
using std::endl ; 


#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_multifit_nlin.h>


struct data {
  size_t n;
  double * y;
  double * sigma;
};


void
print_state (size_t iter, gsl_multifit_fdfsolver * s)
{
  printf ("iter: %3u A=% 15.8f b=% 15.8f P=%15.8f baseline=%15.8f "
          "|f(x)| = %g\n",
          iter,
          gsl_vector_get (s->x, 0), 
          gsl_vector_get (s->x, 1),
          gsl_vector_get (s->x, 2), 
          gsl_vector_get (s->x, 3), 
          gsl_blas_dnrm2 (s->f));
}




int
expb_f (const gsl_vector * x, void *params, 
        gsl_vector * f)
{
  size_t n = ((struct data *)params)->n;
  double *y = ((struct data *)params)->y;
  double *sigma = ((struct data *) params)->sigma;

  double A = gsl_vector_get (x, 0);
  double b = gsl_vector_get (x, 1);
  double P = gsl_vector_get (x, 2);
  double baseline = gsl_vector_get (x, 3);

  size_t i;

  for (i = 0; i < n; i++)
    {
//      Yi = A * ( exp (-b1* t) cos(P t) ) ;
      double t = i;
      double Yi = A * ( exp (-b* t) * cos(P*t) ) + baseline ;
      gsl_vector_set (f, i, (Yi - y[i])/sigma[i]);
    }

  return GSL_SUCCESS;
}

int
expb_df (const gsl_vector * x, void *params, 
         gsl_matrix * J)
{
  size_t n = ((struct data *)params)->n;
  double *sigma = ((struct data *) params)->sigma;

  double A = gsl_vector_get (x, 0);
  double b = gsl_vector_get (x, 1);
  double P = gsl_vector_get (x, 2);
  double baseline = gsl_vector_get (x, 3);

  size_t i;

  for (i = 0; i < n; i++)
    {
      /* Jacobian matrix J(i,j) = dfi / dxj, */
      /* where fi = (Yi - yi)/sigma[i],      */
      /*       Yi = A * exp(-lambda * i) + b  */
      /* and the xj are the parameters (A,lambda,b) */
      double t = i;
      double s = sigma[i];
      double e1 = exp(-b * t);
      double cos1 = cos(P*t) ; 
      double sin1 = -t * sin(P*t) ; 
      gsl_matrix_set (J, i, 0, (e1*cos1)/s);  // dYi/dA
      gsl_matrix_set (J, i, 1, -t * A * e1*cos1/s);  // dYi/db
      gsl_matrix_set (J, i, 2, A * sin1/s);  // dYi/dP
      gsl_matrix_set (J, i, 3, 1.0/s);  // dYi/dbaseline

    }
  return GSL_SUCCESS;
}

int
expb_fdf (const gsl_vector * x, void *params,
          gsl_vector * f, gsl_matrix * J)
{
  expb_f (x, params, f);
  expb_df (x, params, J);

  return GSL_SUCCESS;
}



//The main part of the program sets up a Levenberg-Marquardt solver and some simulated random data. The data uses the known parameters (1.0,5.0,0.1) combined with gaussian noise (standard deviation = 0.1) over a range of 40 timesteps. The initial guess for the parameters is chosen as (0.0, 1.0, 0.0).


int
main (int argc, char** argv)
{

  int N = 1000 ; 

    cout << "Nonlinear regression of function y(t)=A(exp(-b1 t)-exp(-b2 t))+baseline" << endl; 

//    gsl_vector* test ; 
//    gsl_vector_set(test,0,2) ; 
//    gsl_vector_set(test,1,0.05) ; 
//    gsl_vector_set(test,2,0.1) ; 
//  double deltaT[N] ;  
//  for(int i = 0 ; i < N ; i++)  { deltaT[i] = 1.0 ; }
//  struct data paramData = { 50, targetVector, deltaT};
//    cout << "perfect error: " << expb_f(test,&paramData,test) << endl ;

  const gsl_multifit_fdfsolver_type *T;
  gsl_multifit_fdfsolver *s;

  int status;
  size_t i, iter = 0;


  const size_t n = N;
  const size_t p = 4;

  gsl_matrix *covar = gsl_matrix_alloc (p, p);

  double y[N], sigma[N];




  struct data d = { n, y, sigma};
  
  gsl_multifit_function_fdf f;

  double x_init[4] = { 1.0, 0.2, 0.2,0.3 };

  gsl_vector_view x = gsl_vector_view_array (x_init, p);

  const gsl_rng_type * type;
  gsl_rng * r;

  gsl_rng_env_setup();

  type = gsl_rng_default;
  r = gsl_rng_alloc (type);

  f.f = &expb_f;
  f.df = &expb_df;
  f.fdf = &expb_fdf;
  f.n = n;
  f.p = p;
  f.params = &d;

  /* This is the data to be fitted */

  for (i = 0; i < n; i++)
    {
      double t = i;
      y[i] = 0.0 + 2 * ( exp (-0.1 * t) * cos(0.2 * t ) )  ; 
//      y[i] = 0.0 + 2 * ( exp (-0.1 * t) - exp(-0.2 * t ) ) + gsl_ran_gaussian(r,0.1)  ; 
//      sigma[i] = 0.1 ; // delta t
      sigma[i] = 1.0 ; // delta t
//      y[i] = 1.0 + 5 * exp (-0.1 * t) 
//                 + gsl_ran_gaussian (r, 0.1);
//      sigma[i] = 1.0 ; // delta t
//      printf ("data: %d %g %g\n", i, y[i], sigma[i]);
    };

  T = gsl_multifit_fdfsolver_lmsder;
  s = gsl_multifit_fdfsolver_alloc (T, n, p);
  gsl_multifit_fdfsolver_set (s, &f, &x.vector);

  print_state (iter, s);

  do
    {
      iter++;
      status = gsl_multifit_fdfsolver_iterate (s);

      printf ("status = %s\n", gsl_strerror (status));

      print_state (iter, s);

      if (status)
        break;

      status = gsl_multifit_test_delta (s->dx, s->x,
                                        1e-4, 1e-4);
    }
  while (status == GSL_CONTINUE && iter < 500);

  gsl_multifit_covar (s->J, 0.0, covar);

#define FIT(i) gsl_vector_get(s->x, i)
#define ERR(i) sqrt(gsl_matrix_get(covar,i,i))

  printf ("A      = %.5f +/- %.5f\n", FIT(0), ERR(0));
  printf ("b1 = %.5f +/- %.5f\n", FIT(1), ERR(1));
  printf ("b2      = %.5f +/- %.5f\n", FIT(2), ERR(2));
  printf ("baseline      = %.5f +/- %.5f\n", FIT(3), ERR(3));

  { 
    double chi = gsl_blas_dnrm2(s->f);
    printf("chisq/dof = %g\n",  pow(chi, 2.0)/ (n - p));
  }

  printf ("status = %s\n", gsl_strerror (status));

  gsl_multifit_fdfsolver_free (s);
  return 0;
}



