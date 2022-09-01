The first (enqueue) stack is used only for inserting values.
The second (dequeue) stack is for reading/removal of values.

Logic of the enqueue stack is simple - values are only pushed to it.

Logic of the dequeue stack is a slightly more complex - if it has values
they are simply read/popped. On the other hand, when the stack is empty
(and only then) are all the values from the enqueue stack transferred to
the dequeue stack.

Method complexities:
  - stack push: O(1) or amortized O(1) depending on the underlying data type
  - stack pop: O(1)
  - stack top: O(1)
  - queue enqueue: O(1) or amortized O(1) depending on the underlying data type, same as stack push
  - queue dequeue: amortized O(1)
  - queue transfer: O(n) where n is the number of elements in the enqueue stack 
