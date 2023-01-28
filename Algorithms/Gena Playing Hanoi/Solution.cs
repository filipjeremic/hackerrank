namespace HackerRank
{
    class GenaPlayingHanoi
    {
        private static int[]? readInput()
        {
            Console.ReadLine();
            var line = Console.ReadLine();

            if (line == null)
            {
                return null;
            }

            var arr = Array.ConvertAll(line.Trim().Split(' '), Convert.ToInt32);
            return arr;
        }

        private static Stack<int>[] transformInputData(int[] inputData)
        {
            var transformedData = new Stack<int>[4]{
                new Stack<int>(),
                new Stack<int>(),
                new Stack<int>(),
                new Stack<int>(),
            };

            for (int i = inputData.Length - 1; i >= 0; i--)
            {
                int rod = inputData[i] - 1;
                int disk = i;
                transformedData[rod].Push(disk);
            }

            return transformedData;
        }

        private class RodComparer : IComparer<Stack<int>>
        {
            public int Compare(Stack<int>? lhs, Stack<int>? rhs)
            {
                if (lhs.Count == 0)
                {
                    return rhs.Count == 0 ? 0 : 1;
                }

                return rhs.Count == 0 ? -1 : rhs.Peek() - lhs.Peek();
            }
        }

        class StateEqualityComparer : IEqualityComparer<Stack<int>[]>
        {
            public bool Equals(Stack<int>[]? lhs, Stack<int>[]? rhs)
            {
                int lhsLength = lhs.Length;

                if (lhsLength != rhs.Length)
                {
                    return false;
                }

                for (int i = 0; i < lhsLength; i++)
                {
                    if (!lhs[i].SequenceEqual(rhs[i]))
                    {
                        return false;
                    }
                }

                return true;
            }

            public int GetHashCode(Stack<int>[] state)
            {
                int hashCode = 0;

                int iPow = 1;

                foreach (var stack in state)
                {
                    int hashCodePart = 0;

                    int jPow = 1;

                    foreach (var stackItem in stack)
                    {
                        hashCodePart += stackItem * jPow;
                        jPow *= 10;
                    }

                    hashCode += hashCodePart * iPow;
                    iPow *= 10;
                }

                return hashCode;
            }
        }

        private static RodComparer rodComparer = new RodComparer();
        private static StateEqualityComparer stateEqualityComparer = new StateEqualityComparer();

        private static void sortState(Stack<int>[] state)
        {
            Stack<int>[] rodsToSort = new Stack<int>[]{
                state[1],
                state[2],
                state[3],
            };

            Array.Sort(rodsToSort, rodComparer);

            state[1] = rodsToSort[0];
            state[2] = rodsToSort[1];
            state[3] = rodsToSort[2];
        }

        private static int solution(Stack<int>[] initialState)
        {
            var stateDequeue = new LinkedList<Tuple<Stack<int>[], int>>();
            sortState(initialState);
            stateDequeue.AddLast(new Tuple<Stack<int>[], int>(initialState, 0));

            var visitedStates = new HashSet<Stack<int>[]>(stateEqualityComparer) { initialState };

            while (stateDequeue.Count > 0)
            {
                var currentTuple = stateDequeue.First.Value;
                stateDequeue.RemoveFirst();
                var currentState = currentTuple.Item1;
                var currentStep = currentTuple.Item2;

                if (currentState[1].Count == 0 && currentState[2].Count == 0 && currentState[3].Count == 0)
                {
                    return currentStep;
                }

                for (int i = 0; i < currentState.Length; i++)
                {
                    for (int j = 0; j < currentState.Length; j++)
                    {
                        if (i == j)
                        {
                            continue;
                        }

                        var fromStack = currentState[j];
                        if (fromStack.Count < 1)
                        {
                            continue;
                        }

                        var toStack = currentState[i];

                        if ((toStack.Count > 0) && (fromStack.Peek() >= toStack.Peek()))
                        {
                            continue;
                        }

                        var newState = new Stack<int>[4]{
                            new Stack<int>(currentState[0].Reverse()),
                            new Stack<int>(currentState[1].Reverse()),
                            new Stack<int>(currentState[2].Reverse()),
                            new Stack<int>(currentState[3].Reverse()),
                        };

                        newState[i].Push(newState[j].Pop());
                        sortState(newState);

                        if (visitedStates.Add(newState))
                        {
                            stateDequeue.AddLast(new Tuple<Stack<int>[], int>(newState, currentStep + 1));
                        }
                    }
                }
            }

            return 0;
        }

        static void Main(string[] args)
        {
            var inputData = readInput();

            if (inputData == null)
            {
                Console.WriteLine(0);
                return;
            }

            var data = transformInputData(inputData);

            Console.WriteLine(solution(data));
        }
    }
}
