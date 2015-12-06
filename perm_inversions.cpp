/*
Authors: Ekhine Irurozki, Borja Calvo, Jose A. Lozano

Random permutation at a Kendall's-tau distance from the identity 
(or with a given number of inversions). 

The following code can be run by typing:
    g++ perm_onversions.cpp -o perms
    ./perms

It generates one random permutation of 10 items at
distance 0, 1, 2, ..., 22. 

In order to generate a permutation at distance d from 
permutation pi, then generate a random permutation sigma
and compose it with pi (sigma pi)

Based on https://oeis.org/A008302
*/

#include <iostream>
#include <stdio.h>
#include <cstdlib>


long double**count_;
int FIRST_ITEM = 1; //firts item in the permu
int n_;



void dist_decomp_vector2perm(int* vec, int* sigma) {
    int val;
    int*ident = new int[ n_ ];
    for(int i = 0 ; i < n_ ; i ++) ident[i]=i;
    for(int i = 0 ; i < n_ - 1 ; i++){
        val = vec[i];
        int index = 0;
        while( !(ident[ index ] != -1 && val == 0))
            if(ident[ index ++ ] != -1)
                val --;
        sigma[ i ] = index + FIRST_ITEM ;
        ident[ index ] = -1 ;
    }
    int index=0;
    while(ident[ index ] == -1 )index++;
    sigma[ n_ - 1 ] = index + FIRST_ITEM;
    delete [] ident;
}


void random_permu_at_dist_d( int dist, int*sigma  ){
    double* acum = new double[ n_ ];
    int*v = new int[ n_ ];
    v[ n_ - 1 ] = 0 ;
    int i, min, rest_max_dist, pos;
    double bound;
    // generate random distance decomposition vector (inversion vector)
    for(i = 0 ; ( i < n_ && dist > 0 );i ++ ) {
        rest_max_dist = (n_ - i - 1 ) * ( n_ - i - 2 ) / 2;//con los restantes n' puedes tener distMAx de binom(n`)(2)
        if(rest_max_dist  >= dist )acum[ 0 ] = count_[ n_ - i - 1 ][ dist ];
        else acum[ 0 ] = 0 ;
        min = (n_ - i < dist + 1 ) ? (n_ - i ) : dist + 1;/////MIN
        for(int j = 1; j < min; j++ )
            if(rest_max_dist + j >= dist) acum[j] = acum[j-1] + count_[ n_ - i - 1 ] [ dist - j];
            else acum[ j ] = 0;
        //for(int j = 0; j < min; j++ ) std::cout<<acum[j]<<" ";std::cout<<" ACUM \n";
        bound = (double)rand() / (double)(RAND_MAX) * acum[ min - 1 ];
        pos = 0 ;
        while(acum[pos] <= bound) pos++;
        dist -= pos;
        v[i] = pos;
    }
    for (int j = i; j < n_; j++) v[ j ] = 0; //the last n-i positions
    //for (int j = 0; j < n_; j++ ) std::cout<<v[j]<<" ";std::cout<<" V \n";
    dist_decomp_vector2perm(v, sigma);
    
    delete [] v;
    delete [] acum;
}

void ini_count(){
    // initialize the matrix of the count of permutations at each distance
    //https://oeis.org/A008302
    count_= new long double*[n_+1];
    for(int i = 0 ; i < n_ + 1 ; i++) count_[i] = new long double[n_ * ( n_- 1 ) / 2 + 1 ];
    for(int i = 0 ; i < n_ + 1 ; i ++)
        for(int j = 1 ; j < n_ *(n_-1)/2+1 ; j++)
            count_[i][j]=0;
    for(int i = 0 ; i < n_ + 1 ; i++) count_[i][0]=1;
    for(int i = 1 ; i < n_ + 1 ; i++){
        for(int j = 1 ; j < i*(i-1)/2+1 ; j++){
            if( j - i >= 0) count_[i][j] = count_[i][j-1] + count_[i-1][j] - count_[i-1][j-i];
            else count_[i][j] = count_[i][j-1] + count_[i-1][j] ;
        }
    }
}

int main(int argc, const char * argv[]) {
    
    n_ = 10; // Permutation length
    int max_dist = n_ * (n_ - 1) / 2; // maximum distance for two permutations of length n_

    int * sigma = new int[ n_ ];
    ini_count();

    for(int distance=0; distance <= max_dist/2; distance++){
        random_permu_at_dist_d( distance , sigma);
        std::cout <<"Random permutation at distance "<<distance<<" from the idenity " ;
        for ( int j = 0 ; j < n_ ; j++) std::cout <<sigma[ j ]<<" "; std::cout<<"\n";
    }

    for(int i=0;i<n_+1;i++) delete[] count_[i];
    delete[] count_;
    delete[] sigma;
    return 0;
}
