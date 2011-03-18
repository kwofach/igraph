/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2010  Gabor Csardi <csardi.gabor@gmail.com>
   Rue de l'Industrie 5, 1005 Lausanne, Switzerland
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

#include <igraph.h>
#include <igraph_sparsemat.h>

int main() {
  igraph_matrix_t mat, mat2, mat3;
  igraph_sparsemat_t spmat, spmat2;
  int i;

  igraph_rng_seed(&igraph_rng_default, 42);

#define NROW 10
#define NCOL 7  
#define NZERO 15

  igraph_matrix_init(&mat, NROW, NCOL);
  for (i=0; i<NZERO; i++) {
    int r=igraph_rng_get_integer(&igraph_rng_default, 0, NROW-1);
    int c=igraph_rng_get_integer(&igraph_rng_default, 0, NCOL-1);
    igraph_real_t val=igraph_rng_get_integer(&igraph_rng_default, 1, 10);
    MATRIX(mat, r, c) = val;
  }
  
  igraph_matrix_as_sparsemat(&spmat, &mat, /*tol=*/ 1e-14);
  igraph_sparsemat_as_matrix(&mat2, &spmat);
  if (!igraph_matrix_is_equal(&mat, &mat2)) { return 1; }
  
  igraph_sparsemat_compress(&spmat, &spmat2);
  igraph_sparsemat_as_matrix(&mat3, &spmat2);
  if (!igraph_matrix_is_equal(&mat, &mat3)) { return 2; }
  
  igraph_matrix_destroy(&mat);
  igraph_matrix_destroy(&mat2);
  igraph_matrix_destroy(&mat3);
  igraph_sparsemat_destroy(&spmat);
  igraph_sparsemat_destroy(&spmat2);

  return 0;
}
