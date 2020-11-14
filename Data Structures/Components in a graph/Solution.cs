using System;
using System.Collections.Generic;

class Solution
{
    static private List<Tuple<int, int>> readData()
    {
        int n = Convert.ToInt32(Console.ReadLine());
        var gb = new List<Tuple<int, int>>(n);
        for (int i = 0; i < n; i++)
        {
            int[] arr = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
            gb.Add(Tuple.Create(arr[0], arr[1]));
        }
        return gb;
    }

    static private Tuple<int, int> getMinMaxListSize(Dictionary<int, LinkedList<int>> m)
    {
        int min = int.MaxValue;
        int max = int.MinValue;

        foreach (var e in m)
        {
            int size = e.Value.Count;
            if (size < min) min = size;
            if (size > max) max = size;
        }

        return Tuple.Create(min, max);
    }

    static private Tuple<int, int> componentsInGraph(List<Tuple<int, int>> gb)
    {
        var m = new Dictionary<int, LinkedList<int>>();

        gb.ForEach(t =>
        {
            var a = t.Item1;
            var b = t.Item2;

            bool hasA = m.ContainsKey(a);
            bool hasB = m.ContainsKey(b);

            if (!hasA && !hasB)
            {
                var l = new LinkedList<int>(new int[]{ a, b });

                m.Add(a, l);
                m.Add(b, l);

                return;
            }

            if (hasA && hasB)
            {
                var la = m[a];
                var lb = m[b];

                if (la == lb) return;

                int sizeA = la.Count;
                int sizeB = lb.Count;

                var listSmall = (sizeA < sizeB ? la : lb);
                var listLarge = (sizeA >= sizeB ? la : lb);

                foreach (int i in listSmall)
                {
                    m[i] = listLarge;
                    listLarge.AddFirst(i);
                }

                return;
            }

            int valueToInsert = (hasA ? b : a);
            var whereToInsert = m[hasA ? a : b];

            whereToInsert.AddFirst(valueToInsert);
            m[valueToInsert] = whereToInsert;
        });

        return getMinMaxListSize(m);
    }

    static void Main(string[] args)
    {
        var result = componentsInGraph(readData());
        Console.WriteLine("{0} {1}", result.Item1, result.Item2);
    }
}
