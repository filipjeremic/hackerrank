The logic:
  - you need to keep track of which numbers are connected (the order is irrelevant)
  - this information is held in a map
  - each number is a key in the map
  - the corresponding value is a list with all the connected numbers (including itself)
  - the lists are unique, i.e. the map entries are references (all the connected numbers point to the same list)
  - there are 4 cases when a new pair is considered:
    1) both numbers are new (not in the map)
      - create a new list with those 2 numbers
      - add the (key, value) pairs to the map, both number keys point to this newly created list
    2) both numbers are old (already in the map) and point to the same list
      - nothing to do in this case
    3) both numbers are old (already in the map) and do not point to the same list
      - this means we are connecting 2 lists
      - all the elements from both lists become connected through this connection
      - we add the elements from one list to the other and update the map references
      - we loop through the smaller list
    4) one number is new
      - add the new number to the connected list of the number already in the map
      - add the new number as a key to the map and the connected list as the value

Time complexity: O(n)
Space complexity: O(n)
