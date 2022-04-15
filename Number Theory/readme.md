### General Advice

+ Try to explore multiplicative properties of a function

#### Sieve of Eratosthenes
+ Finds All primes under **N** in **O(N log log N)** 

#### Totient Function / Phi Function
+ Finds Phi value of a number in **O(sqrt(N))**

#### Totient Function From 1 to N
+ Precomputes all phi values in **O(N log log N)**

#### Chinese Remainder Theorem
+ **ar** stores all the remainders, **mods** stores all the mod base.

#### Miller Rabin

+ **Witness** function return true if founds a divisor of the number. But this algorithm is not deterministic. So we run it several times to decrease the error rate.

#### Pollard Rho
+ **factorize** function provides you with the prime divisiors with frequencies. **n** is the number we want to factorize, **ans** is our output.
