class Solution
{
  private static int[] readTwoInts()
  {
    return Array.ConvertAll(Console.ReadLine().Split(' '), arrTemp => Convert.ToInt32(arrTemp));
  }

  private static Dictionary<int, HashSet<int>> readInput()
  {
    int edgeCount = readTwoInts()[1];

    var m = new Dictionary<int, HashSet<int>>();

    for (int i = 0; i < edgeCount; i++)
    {
      int[] values = readTwoInts();
      int nodeFrom = values[1];
      int nodeTo = values[0];

      if (m.ContainsKey(nodeFrom))
      {
        m[nodeFrom].Add(nodeTo);
      }
      else
      {
        m.Add(nodeFrom, new HashSet<int> { nodeTo });
      }
    }

    return m;
  }

  private static Tuple<int, int> evenForest(Dictionary<int, HashSet<int>> m, int currentNode)
  {
    if (!m.ContainsKey(currentNode))
    {
      return Tuple.Create(1, 0);
    }

    int result = 0;
    int childrenCount = 0;

    foreach (int childNode in m[currentNode])
    {
      var childValues = evenForest(m, childNode);
      int childChildrenCount = childValues.Item1;
      int childResult = childValues.Item2;

      result += childResult;
      if (childChildrenCount % 2 == 0)
      {
        result++;
      }
      else
      {
        childrenCount += childChildrenCount;
      }
    }

    return Tuple.Create(++childrenCount, result);
  }

  public static void Main(string[] args)
  {
    var m = readInput();
    var result = evenForest(m, 1);
    Console.WriteLine(result.Item2);
  }
}
