# Algorithm & Approach

Instead of testing continuous points across the line, the number of overlapping intervals only changes at interval endpoints. We utilize an **Event-Driven Sweep-Line Algorithm**:

---

### **Step 1: Event Decomposition**
Convert each interval $[l_i, r_i]$ into two discrete events:
* **Start Event:** $(\text{point} = l_i, \text{type} = +1)$
* **End Event:** $(\text{point} = r_i, \text{type} = -1)$

Allocate an array of $2n$ events.

---

### **Step 2: Sorting Events with Inclusive Endpoint Handling**
* Sort the $2n$ events in ascending order of coordinate point ($\mathcal{O}(n \log n)$).
* **Critical Tie-Breaker:** When two events share the same coordinate (e.g., one interval ends at $x$ and another starts at $x$), the **Start event (+1)** must precede the **End event (-1)** because closed intervals include their endpoints.

---

### **Step 3: Sweep-Line Linear Scan**
1. Initialize `count = 0`, `maxCount = 0`, and `p = 0`.
2. Iterate through the sorted events ($\mathcal{O}(n)$):
   * **Update active interval count:** `count += events[i].type`
   * **If `count > maxCount`:**
     * `maxCount = count`
     * `p = events[i].point`

---

### **Time Complexity Analysis**
$$\text{Total Time Complexity} = \underbrace{\mathcal{O}(n \log n)}_{\text{Sorting } 2n \text{ Events}} + \underbrace{\mathcal{O}(n)}_{\text{Linear Sweep Scan}} = \mathcal{O}(n \log n)$$
