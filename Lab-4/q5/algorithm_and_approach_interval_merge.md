# Algorithm & Approach

A naive pairwise comparison would require $\mathcal{O}(n^2)$ time. By sorting intervals beforehand, all potentially overlapping intervals become adjacent, allowing a single linear pass:

---

### **Step 1: Interval Representation**
Define a `struct Interval` containing `start` ($x_i$) and `end` ($y_i$).

---

### **Step 2: Sorting by Start Time**
* Sort the array of intervals in non-decreasing order of their start values using `qsort` ($\mathcal{O}(n \log n)$).
* Sorting guarantees that for any two intervals $I_a$ and $I_b$ with $a < b$, $I_a.\text{start} \le I_b.\text{start}$.

---

### **Step 3: Linear Merge Sweep**
1. Initialize an active interval `current = I[0]`.
2. Iterate through the remaining intervals from $i = 1$ to $n - 1$:
   * **Overlap Case ($I[i].\text{start} \le \text{current.end}$):** The next interval overlaps with or connects to `current`. Expand `current.end` to $\max(\text{current.end}, I[i].\text{end})$.
   * **Disjoint Case ($I[i].\text{start} > \text{current.end}$):** There is a gap between `current` and $I[i]$. Since all subsequent intervals start even later, `current` is finalized. Append `current` to the result and update `current = I[i]`.
3. After the loop finishes, append the last remaining `current` to the result.

---

### **Time Complexity Analysis**
$$\text{Total Time Complexity} = \underbrace{\mathcal{O}(n \log n)}_{\text{Sorting by Start Time}} + \underbrace{\mathcal{O}(n)}_{\text{Linear Merge Sweep}} = \mathcal{O}(n \log n)$$
