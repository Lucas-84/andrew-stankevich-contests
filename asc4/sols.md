F: Reexpress the problem with prefix sums. Straightforward sweep line afterwards. Complexity: $O(n)$  
Note: Actually the answer is $\max(0,\sum_i a_i)$.

B: Compute the bridges of a multigraph. Standard problem, solved with DFS. Complexity: $O(n + m)$

H: BFS, find a particular solution by choosing greedily appropriate directions. Complexity: $O(nm)$

E: Dynamic programming $\text{dp}(y, r, i)$ is the maximum number of movies we can see from year 1870
to $y-1$ with $r$ changes of region remaining and starting with region $i$. A transition is a mask from
$2^5$ subsets of regions containing $i$ and an output region. Complexity: $O(nr^2 2^r)$

C: Consider the graph $G=(V,E)$ with $V$ being the set of intersections of all circles (+1 node for
each circle) and ${u,v}\in E$ iff. $u$ and $v$ are two consecutive intersections of a circle. Each
connected component is a planar graph, so apply Euler's formula. Complexity: $O(n^2 \log n)$

A: Check if the residual cut resulting from maxflow is the same from $s$ and from $t$ (ie. if the set
of nodes that can be reached from $s$ and the set of nodes that can reach $t$ in the residual graph
form a partition of $V$). Complexity: $O(n^2 m)$

G: Just a simulation problem (but a few potential bugs).

D: Mainly a parsing problem, not too hard with `scanf`'s regular expressions. 



