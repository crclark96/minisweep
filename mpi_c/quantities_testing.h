/*---------------------------------------------------------------------------*/
/*!
 * \file   quantities_testing.h
 * \author Wayne Joubert
 * \date   Wed Jan 15 16:06:28 EST 2014
 * \brief  Declarations for physical quantities, testing case.
 * \note   Copyright (C) 2014 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
/*---------------------------------------------------------------------------*/

#ifndef _serial_c__quantities_testing_h_
#define _serial_c__quantities_testing_h_

#include "function_attributes.h"
#include "types.h"
#include "dimensions.h"

#include "quantities_testing_kernels.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*===========================================================================*/
/*---Pseudo-constructor for Quantities struct---*/

void Quantities_ctor( Quantities*       quan,
                      const Dimensions  dims,
                      Env*              env );

/*===========================================================================*/
/*---Pseudo-destructor for Quantities struct---*/

void Quantities_dtor( Quantities* quan );

/*===========================================================================*/
/*---Initialize Quantities a_from_m, m_from_a matrices---*/
/*---pseudo-private member function---*/

void Quantities_init_am_matrices__( Quantities*       quan,
                                    const Dimensions  dims,
                                    Env*              env );

/*===========================================================================*/
/*---Initialize Quantities subgrid decomp info---*/
/*---pseudo-private member function---*/

void Quantities_init_decomp__( Quantities*       quan,
                               const Dimensions  dims,
                               Env*              env );

/*===========================================================================*/
/*---Flops cost of solve per element---*/

double Quantities_flops_per_solve( const Dimensions dims );

/*===========================================================================*/
/*---Initial values for state vector---*/

static inline P Quantities_init_state(
  const Quantities*  quan,
  int                ix,
  int                iy,
  int                iz,
  int                ie,
  int                im,
  int                iu,
  const Dimensions   dims )
{
  Assert( ix >= 0 && ix < dims.nx);
  Assert( iy >= 0 && iy < dims.ny );
  Assert( iz >= 0 && iz < dims.nz );
  Assert( ie >= 0 && ie < dims.ne );
  Assert( im >= 0 && im < dims.nm );
  Assert( iu >= 0 && iu < NU );

  if( Quantities_bc_vacuum() )
  {
    return ((P)0);
  }
  else
  {
    return   ( (P) Quantities_affinefunction__( im ) )
           * ( (P) Quantities_scalefactor_space__( quan,
                                                   ix+quan->ix_base,
                                                   iy+quan->iy_base, iz ) )
           * ( (P) Quantities_scalefactor_energy__( ie, dims ) )
           * ( (P) Quantities_scalefactor_unknown__( iu ) );
  }
}

/*===========================================================================*/

#ifdef __cplusplus
} /*---extern "C"---*/
#endif

#endif /*---_serial_c__quantities_testing_h_---*/

/*---------------------------------------------------------------------------*/
