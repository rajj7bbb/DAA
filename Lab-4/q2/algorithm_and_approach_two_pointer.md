# Algorithm & Approach

A brute-force search checking all pairs $(a, b) \in S_1 	imes S_2$ would take $\mathcal{O}(n^2)$ time. To achieve $\mathcal{O}(n \log n)$ time complexity, we sort both sets and employ the **two-pointer technique**:

---

### **Step 1: Sorting**
* Sort set $S_1$ in ascending order using `qsort` ($\mathcal{O}(n \log n)$).
* Sort set $S_2$ in ascending order using `qsort` ($\mathcal{O}(n \log n)$).

---

### **Step 2: Two-Pointer Search**
1. Initialize pointer $i = 0$ at the beginning of $S_1$ (smallest element of $S_1$).
2. Initialize pointer $j = n - 1$ at the end of $S_2$ (largest element of $S_2$).
3. While $i < n$ and $j \ge 0$:
   * Compute $	ext{currentSum} = S_1[i] + S_2[j]$.
   * **If $	ext{currentSum} == x$:** A valid pair $(S_1[i], S_2[j])$ is found; return `true`.
   * **If $	ext{currentSum} < x$:** The sum is too small; increment $i$ (`i++`) to consider a larger element from $S_1$.
   * **If $	ext{currentSum} > x$:** The sum is too large; decrement $j$ (`j--`) to consider a smaller element from $S_2$.

---

### **Step 3: Termination**
* If the pointers cross without finding any pair that sums to $x$, return `false`.

---

### **Alternative Approach (Binary Search)**
Alternatively, one could sort only $S_2$ ($\mathcal{O}(n \log n)$) and perform a binary search for $(x - a)$ in $S_2$ for each $a \in S_1$ ($n 	imes \mathcal{O}(\log n) = \mathcal{O}(n \log n)$). The two-pointer approach avoids repeated binary searches and achieves a linear $\mathcal{O}(n)$ search phase after sorting.
