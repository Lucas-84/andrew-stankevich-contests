C: Standard huffman encoding problem. Can be done using priority queue in $O(n \log n)$.  
Note: $O(n)$ is also possible by keeping two pointers.

E: Straightforward DP with $nm$ states and $s$ transitions. Complexity: $O(nms)$

G: Initially assign $K_i$ to the nearest integer to $MX_i/Y$. Then greedily change $K_i$ by 
minimizing the local change until the $\sum_i K_i = M$. Complexity: $O(n^2)$  
Alternative solution: a DP solution also exists

A: Precompute the transitions of type $0$ with DFS. Then it's an easy DP problem. Complexity: $O(kn|\Sigma|)$

H: Apply Burnside's lemma to the product group of the vertical rotations, the horizontal rotations and
the $\pi$ rotation (plus $\pi/2$ if $n=m$). For each permutation, the number of fixed points can be
computed by counting the number of cycles. Complexity: $O(n^2 m^2)$

F: Let $x_i=d_i-c_i$ for $i<n$ and $y_j=c_j-d_j$ for $i\ge n$. Then the problem asks to maximize
$\sum_i -x_i + \sum_j -y_j$ subject to $-x_i-y_j\le c_i-c_j$, with $i,j$ such that the $i$-th and the $j$-th
edges form a cycle in the graph built from the $n-1$ first edges and the $j-th$ one. $-x_i$ and $-y_j$ are
the potentials computed by hungarian's method. Complexity: $O(max(n, m-n)^3)$

D: Solve formula by hand. The optimal speed as a function of the x-coordinate of the second jump
looks like $x \mapsto ax+b/x$, which is convex. Hence the objective function is a maximum of convex
functions, so we find its minimum with ternary search. Complexity: $O(\log \epsilon)$

B: Frame-Stewart algorithm (check Wikipedia). Find the optimal $k$ with dynamic programming. Complexity:
$O(nm+s)$, with $s$ the size of the solution.
