turns out we cannot enumerate all possibilities cause that would be such a huge number that isnt even representable even n = 10, 2^10 is a huge number

solution is we must use dp

we observe that in the knapsack problem the recurrence relation is as follows:

dp[k][c] = max(dp[k-1][c], dp[k-1][c-w[k]] + v[k] -> if is valid)

we note that in this solution, to obtain value at item k, we must know solution at item k-1
however to get solution at item k at capacity c, we do not need to know the solution at item k, capacity c-1
this means that we can compute the solutions of the same item with different capacities independently

ex.

let n = 3, maxW = 4
v = [4,5,1]
w = [1,2,3]

then dp table:

wi = 0 | 1 | 2 | 3
vi = 0 | 0 | 0 | 0
vi = 1 | 4 | 4 | 4 
vi = 2 | 4 | 5 | 9
vi = 3 | 4 | 5 | 9

