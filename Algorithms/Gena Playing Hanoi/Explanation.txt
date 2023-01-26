The goal is to have all disks on pole 1 (sorted, of course, since a larger disk can never be on a smaller one).
The idea is to optimize going through all the possible states. We save the visited states in a set, so we
don't repeat work. Also, only the first pole's position is significant, therefore all others can be "moved"
around. This is used for further optimization and it works because certain states are identical, e.g.:


                                                       2                   2
    3 2 1               3 1 2                          3 1                 3   1
    _ _ _ _     and     _ _ _ _          or          _ _ _ _     and     _ _ _ _


It doesn't matter where the disks which are not on pole 1 are located since you can make any move as long
as it is valid. This is why we sort poles 2,3 and 4 - to look at those equivalent states as one state.
And, of course, the algorithm ends as soon as we reach the goal state. We take the first occurrence, because
it has the least number of steps since the step counter is incremented by 1 for each state examined
(which produces a set of next valid states with step counter + 1).

Time complexity: tbd
Space complexity: tbd

Not sure about the complexities. I will try to calculate them again when I get smarter :D
