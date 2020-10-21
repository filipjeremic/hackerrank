import java.util.Scanner;
import java.util.Stack;

public class Solution {

    static class Queue {
        private Stack<Integer> m_enqueueStack = new Stack<Integer>();
        private Stack<Integer> m_dequeueStack = new Stack<Integer>();

        private void transfer() {
            // Amortized O(n), where n is the number of elements in enqueueStack
            while (!m_enqueueStack.empty()) {
                m_dequeueStack.push(m_enqueueStack.pop());
            }
        }

        private void checkAndTransfer() {
            // Amortized O(1)
            // only transfer when the output stack is empty
            if (!m_dequeueStack.empty()) {
                return;
            }

            transfer();
        }

        public void enqueue(final int value) {
            // Amortized O(1)
            m_enqueueStack.push(value);
        }

        public int dequeue() {
            // Amortized O(1)
            checkAndTransfer();
            return m_dequeueStack.pop();
        }

        public int front() {
            // Amortized O(1)
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
