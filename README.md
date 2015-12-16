# random_perm_inversion
Generate a random permutation at a Kendall's-tau distance from the identity 
(or with a given number of inversions). Since there are possibly many permutations
at a given distance, this code generates one of them uniformly at random. 

The following code can be run by typing:
    g++ perm_inversions.cpp -o perms
    ./perms

This code generates one random permutation of 10 items at
distance 0, 1, 2, ..., 22 from the identity permutation. 

In order to generate a permutation at distance d from 
permutation pi, then 
  - sigma <- generate a random permutation at distance d and 
  - compose sigma with pi

Based on https://oeis.org/A008302
