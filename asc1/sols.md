D: Compute the sum algebraically: $\sum_{u\in V} \text{deg}(u)^2$. Complexity: $O(N)$

G: Represent $(x,y)=(B,S)$ in the plane. Sort the people by decreasing $y$, then use dynamic programming
$dp(i)=1+\max_{j>i,x_j>x_i}dp(j)$, with a segment tree to query for the best transition. Complexity: $O(N \log N)$  
Alternative solution: note that the dynamic programming algorithm actually computes LIS.

E: Build the transition matrix for each frontier, then use fast exponentiation to find the total number
of paths. Complexity: $O(M^3\log N)$

C: Dynamic programming on tree: $\text{dp}(\text{i},\text{has})$ with $\text{i}$ the current person and
$\text{has}$ a boolean, true iff. $\text{i}$ receives a grant. Complexity: $O(N)$  
Alternative solution: greedily assign the grants from the leaves.

B: Standard circulation problem with edge demands, can be solved using Dinic's algorithm. Complexity: $O(N^2 M)$

H: To each $b_i$ we can associate a mask $m_i \in \{0,1\}^t$. The answer is the cardinal of the kernel of
the matrix $M$ which columns are $(m_i)_i$. By the rank nullity theorem it is equal to $2^{m-r}$,
where $r$ is the rank of the family $(m_i)$, which can be computed with Gaussian elimination. Complexity: $O(t^2m)$.

A: Notice on small cases that the answer is $(N-1)/2$ if $N$ is odd, $N/2-1$ if $N$ is divisible by $4$, and
$N/2-2$ otherwise (it can be proven using $\text{gcd}$ characterisation). Complexity: $O(\log(N))$  
Other solution: try all generators from $N/2$ by checking if $\text{gcd}(K,N)=1$.

F: Can be reduced to the case of a point by increasing all radiuses by $r$. Build a graph with an edge between circles
that have positive intersection. Check whether the reference point is in any simple cycle whose sum of angles
is greater in absolute value than $2\pi$ with DFS. Complexity: $O(N^2)$
