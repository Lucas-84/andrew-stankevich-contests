I: The volume is the integral of $f(u,v)=\sqrt{\min(R_1^2-u^2,R_2^2-v^2)}$ on $[0,R_1]\times[0,R_2]$. Use numerical integration
to compute it.  
Note: actually there is also a formula with a single integral.

F: Dynamic programming: $\text{dp}(i,j)$ is the answer for the prefix of length $i$ (resp. $j$) of $\lambda$ (resp. $\mu$). Transitions:
(1) put $(\lambda_i, \mu_j)$, (2) put $(\lambda_i,r(\lambda_i))$, (3) $(l({\mu_j}), \mu_j)$ where $l$ and $r$ mimize the cost of each
letter. Complexity: $O(|\lambda||\mu|+(|\lambda|+|\mu|)|\Sigma|)$

E: Put each crystal type at distance $d$ from the source (BFS). Optimality: easy. Complexity: $O(M)$

B: Modify Kuhn's algorithm by finding augmenting paths from nodes sorted in decreasing order of love. Optimality: easy. Complexity: $O(nm)$

A: Find all intersections between lines, then  go through the nodes with DFS and choose neighbour with minimal angle relative to previous one. Sum the
areas of all polygons. Complexity: $O(n^2 \log n)$

H: DFS in the rooted tree from $u$: assign all unassigned sons to province with headquarter in u except $0 \le k < b$ of them. All provinces are
of size between $b$ and $2b$, so we can add the $1+k \le b$ remaining nodes at the end of the DFS to the last province. Complexity: $O(n)$

C: Maintain the following invariant: between each consecutive $2$ there is at least one $0$. Complexity: $O(nm)$

G: Parsing problem. Use Union-Find to keep track of defines.

D: MPM algorithm. Complexity: $O(n^2)$  
Note: Can be solved with push-relabel strategies.
Warning: the conservation property of the output flow is not checked, so there are a few wrong AC solutions. 
