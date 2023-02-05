The logic:
  - every child must get at least 1 piece of candy
  - the amout of candy a child gets depends only on its neighbors
  - if the childs rating is higher than that of its previous neighbor
    it gets 1 piece of candy more than the previous neighbor, otherwise it gets 1
  - same rule applies for its next neighbor
  - the child gets the greater (max) of the two values pieces of candy

Time complexity: O(n)
Space complexity: O(n)
