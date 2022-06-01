Time complexity: O(n)
Space complexity: O(n) - because of the result string

The logic:

This problem is not too complex. Basically, one just needs to do the right
calculation to figure out whether or not it is possible to reach the
destination and if it is, align the conditions properly.

It is beneficial to understand that the red knight will never go back
vertically. So if he needs to go up, he will only go up or sideways. Same
thing for going down. Additionally, he can only stand on the green fields
that are marked (recursively). This shows us the positions which he can reach.
If the end position is on one of these fields, it is reachable, otherwise it
is impossible.

The tricky parts are the corner cases and priorities. Obviously, you can't go
over field bounds. But additionally you need to prioritize moves. For example:
the moves from (6, 1) to (0, 2) are UL UR UR, not UR UL UR or UR UR UL,
because UL has priority. So, even though the end position is to the right,
you have to go to the left first. When going down, LR has priority over LL,
but R has priority over LR. All this needs to be taken into consideration.
When the red knight is in the row where the end is, the movement is trivial,
just go left or right.
