using System;
using System.Linq;
using System.Collections.Generic;

class Solution
{
    class Queue
    {
        private Stack<int> m_enqueueStack = new Stack<int>();
        private Stack<int> m_dequeueStack = new Stack<int>();

        private void transfer()
        {
            // Amortized O(n), where n is the number of elements in enqueueStack
            while (m_enqueueStack.Count > 0)
            {
                m_dequeueStack.Push(m_enqueueStack.Pop());
            }
        }

        private void checkAndTransfer()
        {
            // Amortized O(1)
            // only transfer when the output stack is empty
            if (m_dequeueStack.Count > 0) return;
            transfer();
        }

        public void enqueue(int value)
        {
            // Amortized O(1)
            m_enqueueStack.Push(value);
        }

        public int dequeue()
        {
            // Amortized O(1)
            checkAndTransfer();
            return m_dequeueStack.Pop();
        }

        public int front()
        {
            // Amortized O(1)
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
