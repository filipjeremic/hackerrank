import java.util.Scanner;
import java.util.Stack;

public class Solution {

    static class Queue {
        private Stack<Integer> m_enqueueStack = new Stack<Integer>();
        private Stack<Integer> m_dequeueStack = new Stack<Integer>();

        // Amortized O(n), where n is the number of elements in enqueueStack
        private void transfer() {
            while (!m_enqueueStack.empty()) {
                m_dequeueStack.push(m_enqueueStack.pop());
            }
        }

        // Amortized O(1) - only transfer when the output stack is empty
        private void checkAndTransfer() {
            if (!m_dequeueStack.empty()) {
                return;
            }

            transfer();
        }

        // Amortized O(1)
        public void enqueue(final int value) {
            m_enqueueStack.push(value);
        }

        // Amortized O(1)
        public int dequeue() {
            checkAndTransfer();
            return m_dequeueStack.pop();
        }

        // Amortized O(1)
        public int front() {
            checkAndTransfer();
            return m_dequeueStack.peek();
        }
    }

    public static void main(String[] args) {
        Queue q = new Queue();

        final Scanner scan = new Scanner(System.in);

        final int n = scan.nextInt();

        for (int i = 0; i < n; i++) {
            final int type = scan.nextInt();
            switch (type) {
                case 2:
                    q.dequeue();
                    break;
                case 3:
                    System.out.println(q.front());
                    break;
                default:
                    final int value = scan.nextInt();
                    q.enqueue(value);
                    break;
            }
        }

        scan.close();
    }
}
