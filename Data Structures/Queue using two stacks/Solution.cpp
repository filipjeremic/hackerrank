#include <iostream>
#include <stack>

// The solution is NOT thread safe, nor generic (it is not required)

class Queue
{
   // one stack for input and one for output
   std::stack<int> m_enqueueStack;
   std::stack<int> m_dequeueStack;

   void transfer()
   {
      while (!m_enqueueStack.empty())
      {
         const int value = m_enqueueStack.top();
         m_enqueueStack.pop();
         m_dequeueStack.push(value);
      }
   }

   void checkAndTransfer()
   {
      // only transfer when the output stack is empty
      if (!m_dequeueStack.empty())
      {
         return;
      }

      transfer();
   }

public:
   void enqueue(const int value)
   {
      m_enqueueStack.push(value);
   }

   int dequeue()
   {
      checkAndTransfer();

      // checking again because the enqueue stack can also be empty (we transferred nothing)
      if (m_dequeueStack.empty())
      {
         throw 1;
      }

      const int value = m_dequeueStack.top();
      m_dequeueStack.pop();
      return value;
   }

   int front()
   {
      checkAndTransfer();

      if (m_dequeueStack.empty())
      {
         throw 1;
      }

      return m_dequeueStack.top();
   }
};

int main()
{
   int n = 0;
   std::cin >> n;

   Queue q;

   for (int i = 0; i < n; i++)
   {
      int type = 0;
      std::cin >> type;

      if (type == 2)
      {
         q.dequeue();
      }
      else if (type == 3)
      {
         std::cout << q.front() << '\n';
      }
      else
      {
         int value = 0;
         std::cin >> value;
         q.enqueue(value);
      }
   }

   return 0;
}
