using System;
using System.Linq;
using System.Collections.Generic;

class Solution
{
  class Queue
  {
    private Stack<int> m_enqueueStack = new Stack<int>();
    private Stack<int> m_dequeueStack = new Stack<int>();

    // Amortized O(n), where n is the number of elements in enqueueStack
    private void transfer()
    {
      while (m_enqueueStack.Count > 0)
      {
        m_dequeueStack.Push(m_enqueueStack.Pop());
      }
    }

    // Amortized O(1) - only transfer when the output stack is empty
    private void checkAndTransfer()
    {
      if (m_dequeueStack.Count > 0)
      {
        return;
      }

      transfer();
    }

    // Amortized O(1)
    public void enqueue(int value)
    {
      m_enqueueStack.Push(value);
    }

    // Amortized O(1)
    public int dequeue()
    {
      checkAndTransfer();
      return m_dequeueStack.Pop();
    }

    // Amortized O(1)
    public int front()
    {
      checkAndTransfer();
      return m_dequeueStack.Peek();
    }
  }

  static void Main(String[] args)
  {
    Queue q = new Queue();

    int n = Convert.ToInt32(Console.ReadLine());

    for (int i = 0; i < n; i++)
    {
      int[] arr = Console.ReadLine().Split(' ').Select(a => Convert.ToInt32(a)).ToArray();

      switch (arr[0])
      {
        case 2:
          q.dequeue();
          break;
        case 3:
          Console.WriteLine(q.front());
          break;
        default:
          q.enqueue(arr[1]);
          break;
      }
    }
  }
}
