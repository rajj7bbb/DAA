# Algorithm & Approach

Since the items are already sorted by number, achieving the target ordering requires a **stable partition / counting sort** based on the 3 discrete colors:

---

### **Pass 1: Count Frequency**
1. Traverse the input array once to count the total occurrences of **Red ($R$)** and **Blue ($B$)**.
2. Determine the starting indices for each color bucket:
   - `red_index` = $0$
   - `blue_index` = $R$
   - `yellow_index` = $R + B$

---

### **Pass 2: Stable Linear Placement**
1. Allocate an auxiliary array of size $n$.
2. Iterate through the input array from left to right.
   - Because elements are visited in increasing order of their numbers, placing each color sequentially into its respective bucket index maintains stability.
3. Increment the respective bucket index (`red_index`, `blue_index`, or `yellow_index`) after placing each item.

---

### **Pass 3: Copy Back & Cleanup**
1. Copy the elements from the auxiliary array back to the original array.
2. Free the allocated auxiliary memory (if applicable in the language/environment).
