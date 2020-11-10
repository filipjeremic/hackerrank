'use strict';

/*

Time complexity: O(n)
Space complexity: O(n)

The logic:
    - you need to keep track of which values are connected (the order is irrelevant)
    - this is done by having a map which says which value is in which list (lists are unique and shared)
    - when a new pair is examined there a X cases
        1) both values are new -> new list and map entries
        2) both values are not new and they are in the same list already -> do nothing
        3) both values are not new and they are not in the same list -> update the map entries for
            the values in one list to point to the other list and add the values from one list to the
            other list (I chose looping and modifying the smaller list because of performance)
        4) one value is new -> add it to the list of the other value and create the map entry for it

*/

const fs = require('fs');

process.stdin.resume();
process.stdin.setEncoding('utf-8');

let inputString = '';
let currentLine = 0;

process.stdin.on('data', inputStdin =>
    {
        inputString += inputStdin;
    }
);

process.stdin.on('end', _ =>
    {
        inputString = inputString.trim().split('\n').map(str => str.trim());
        main();
    }
);

function readLine()
{
    return inputString[currentLine++];
}

function getMinMaxLength(it)
{
    let min = it.next().value.length;
    let max = min;

    for (const i of it)
    {
        const l = i.length;
        [min, max] = [Math.min(l, min), Math.max(l, max)];
    }

    return [min, max];
}

function componentsInGraph(gb)
{
    const m = new Map();
    gb.forEach(p =>
        {
            const [a, b] = p;
            const [hasA, hasB] = [m.has(a), m.has(b)];

            if (!hasA && !hasB)
            {
                const l = [a, b];
                m.set(a, l);
                m.set(b, l);
                return;
            }

            if (hasA && hasB)
            {
                const [la, lb] = [m.get(a), m.get(b)];
                if (la === lb) return;

                const [sizeA, sizeB] = [la.length, lb.length];
                const lSmall = (sizeA < sizeB ? la : lb);
                const lLarge = (sizeA >= sizeB ? la : lb);
                for (const i of lSmall)
                {
                    m.set(i, lLarge);
                    lLarge.push(i);
                }
                return;
            }

            const valueToInsert = (hasA ? b : a);
            const whereToInsert = m.get(hasA ? a : b);
            whereToInsert.push(valueToInsert);
            m.set(valueToInsert, whereToInsert);
        }
    );

    return getMinMaxLength(m.values());
}

function main()
{
    const ws = fs.createWriteStream(process.env.OUTPUT_PATH);

    const n = parseInt(readLine(), 10);

    let gb = Array(n);

    for (let gbRowItr = 0; gbRowItr < n; gbRowItr++)
    {
        gb[gbRowItr] = readLine().split(' ').map(gbTemp => parseInt(gbTemp, 10));
    }

    let result = componentsInGraph(gb);

    ws.write(result.join(" ") + "\n");

    ws.end();
}
