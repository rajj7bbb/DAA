# Question 6: The Best Time to Be Alive

## Algorithm

1.  For every scientist, store the birth year and death year.

2.  Create two arrays:

    -   `birth[]` containing all birth years.
    -   `death[]` containing all death years.

3.  Sort both arrays in ascending order.

4.  Use two pointers:

    -   `i` for `birth[]`
    -   `j` for `death[]`

5.  Initialize:

    `alive = 0`\
    `maxAlive = 0`\
    `bestYear = 0`

6.  Compare `birth[i]` and `death[j]`.

7.  If:

    `birth[i] < death[j]`

    then a scientist is born before the next death:

    `alive++`\
    `i++`

8.  Otherwise:

    `birth[i] >= death[j]`

    process the death first:

    `alive--`\
    `j++`

9.  The `>=` condition is important because a scientist who dies in the
    same year another scientist is born is not alive simultaneously with
    that person.

10. Whenever `alive > maxAlive`, update:

    `maxAlive = alive`\
    `bestYear = birth[i]`

11. After all births are processed, `maxAlive` is the maximum number of
    scientists alive at the same time.
