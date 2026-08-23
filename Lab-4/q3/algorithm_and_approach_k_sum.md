# Algorithm & Approach

A brute-force search trying all $\binom{n}{k}$ subsets takes $\mathcal{O}(n^k)$ time. By pre-sorting the set and combining recursive combination enumeration with binary search, we achieve the optimal $\mathcal{O}(n^{k-1} \log n)$ bound:

---

### **Step 1: Initial Sorting**
* Sort the array $S$ in ascending order using `qsort` ($\mathcal{O}(n \log n)$).

---

### **Step 2: Recursive Combination Enumeration (`kElementsExist`)**
1. Use recursion to select $(k - 1)$ elements sequentially.
2. At each recursive level, iterate from index $l$ up to $n - k$ (ensuring at least $k - 1$ elements remain ahead in the array to avoid out-of-bounds selection).
3. **Recurse with:**
   * **Next starting index:** $l = i + 1$ (prevents reusing previously selected elements, ensuring distinctness)
   * **Remaining target:** $T' = T - S[i]$
   * **Remaining count:** $k' = k - 1$

---

### **Step 3: Base Case & Binary Search**
1. When $k == 1$, exactly one element is needed to complete the target sum.
2. Perform a **Binary Search** via `binarySearch` in the remaining sorted range $[l, n - 1]$ for the exact required value $T$.
3. Binary search takes $\mathcal{O}(\log n)$ time.

---

### **Step 4: Output Reconstruction on Call-Stack Unwind**
1. When a valid combination is found, the base case prints the $k$-th element (`S[index]`).
2. As the recursive call stack unwinds, each parent level prints its chosen element (`S[i]`), successfully outputting the exact numbers that sum to $T$.

---

### **Time Complexity Analysis**
$$\text{Total Operations} = \underbrace{\mathcal{O}(n \log n)}_{\text{Sorting}} + \underbrace{\binom{n}{k-1}}_{\mathcal{O}(n^{k-1}) \text{ combinations}} \times \underbrace{\mathcal{O}(\log n)}_{\text{Binary Search}} = \mathcal{O}(n^{k-1} \log n)$$
