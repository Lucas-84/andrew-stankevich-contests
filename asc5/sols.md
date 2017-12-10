C: My construction: yellow code of size $n$ is alternating $0+$ grey code of size $n-1$ and $1+$ complement of
grey code of size $n-1$. Easy to prove from the construction of grey code that it satisfies the constraints.
Complexity: $O(n 2^n)$  
Note: There are a lot of alternative constructions.

I: Keep a list of groups. At railroad $i$, separate each group in 2, according to the $i$-th bit of their value.
Complexity: $O(n 2^n)$

H: Check if an edge of type $-1$ is accessible in the graph $(u,c,b)$ where $u$ is the current state, $c$ the
character under the head and $b$ true iff. we the head is strictly on the right of the initial word. Can be done
with DFS. Complexity: $O(us)$

D: Dynamic programming with state $(i,b)$ where $i$ is the index in the binary representation of $r$, and $b$ is
true iff. the $i$-th index is already covered by a previous 2. A transition corresponds to writing a 0, 1, or 2
at position $i$. In Python because of big integers. Complexity: $O(\log R)$

G: Min cost max flow in a bipartite graph (constructed like a matching). Put a cost 1 between a warehouse and a good
that are compatible and that are not yet matched. The constraint to keep all goods is automatic. 

B: The answer is always $0$, obtained at the angle $2\pi-\frac{1}{n-1}\sum_i \alpha_i \mod 2\pi$, where $\alpha_i$ is the angle
of the $i$-th segment.

A: Use the generalization of Euler's theorem from NCPC 2016, problem E. A few small cases must be handled separately.

F: A bit of not so hard geometry to find the formula. Use `decimal` module of Python to get arbitrary precision. Approximate
$\arccos$ with its integer series, but it's a bit too slow for one testcase where the parameter is almost $1$. So I
precomputed everything.

E: First use DP on digits to compute $\text{dp}(i, s, 0)$ the number of integers of length $i$ and sum $s$ and $\text{dp}(i,s,1)$
the number of integers of length $i$, sum $s$ and less than or equal to $n[0:i]$. Now everything can be computed from this, but
it's not very easy to code. Complexity: $O((\log n)^3)$

