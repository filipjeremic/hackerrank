using System;
using System.Collections.Generic;

class Solution
{
  static private List<Tuple<int, int>> readData()
  {
    int n = Convert.ToInt32(Console.ReadLine());
    var data = new List<Tuple<int, int>>(n);

    for (int i = 0; i < n; i++)
    {
      int[] pair = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
      data.Add(Tuple.Create(pair[0], pair[1]));
    }

    return data;
  }

  static private Tuple<int, int> getMinMaxListSize(Dictionary<int, LinkedList<int>> m)
  {
    int minSize = int.MaxValue;
    int maxSize = int.MinValue;

    foreach (var e in m)
    {
      int currentSize = e.Value.Count;
      if (currentSize < minSize)
      {
        minSize = currentSize;
      }

      if (currentSize > maxSize)
      {
        maxSize = currentSize;
      }
    }

    return Tuple.Create(minSize, maxSize);
  }

  static private Tuple<int, int> componentsInGraph(List<Tuple<int, int>> data)
  {
    var m = new Dictionary<int, LinkedList<int>>();

    foreach (var pair in data)
    {
      int a = pair.Item1;
      int b = pair.Item2;

      bool hasA = m.ContainsKey(a);
      bool hasB = m.ContainsKey(b);

      if (!hasA && !hasB)
      {
        var newList = new LinkedList<int>(new int[] { a, b });

        m.Add(a, newList);
        m.Add(b, newList);

        continue;
      }

      if (hasA && hasB)
      {
        var listA = m[a];
        var listB = m[b];

        if (listA == listB)
        {
          continue;
        }

        int sizeA = listA.Count;
        int sizeB = listB.Count;

        var listSmall = (sizeA < sizeB ? listA : listB);
        var listLarge = (sizeA >= sizeB ? listA : listB);

        foreach (int i in listSmall)
        {
          m[i] = listLarge;
          listLarge.AddFirst(i);
        }

        continue;
      }

      int valueToInsert = (hasA ? b : a);
      var insertList = m[hasA ? a : b];

      insertList.AddFirst(valueToInsert);
      m[valueToInsert] = insertList;
    }

    return getMinMaxListSize(m);
  }

  static void Main(string[] args)
  {
    var result = componentsInGraph(readData());
    Console.WriteLine($"{result.Item1} {result.Item2}");
  }
}
