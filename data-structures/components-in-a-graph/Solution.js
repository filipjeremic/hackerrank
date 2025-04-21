'use strict';

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

function getMinMaxLength(connectedComponents)
{
    let minSize = connectedComponents.next().value.length;
    let maxSize = minSize;

    for (const component of connectedComponents)
    {
        const currentSize = component.length;
        [minSize, maxSize] = [Math.min(currentSize, minSize), Math.max(currentSize, maxSize)];
    }

    return [minSize, maxSize];
}

function componentsInGraph(data)
{
    const m = new Map();

    for (const pair of data)
    {
        const [a, b] = pair;
        const [hasA, hasB] = [m.has(a), m.has(b)];

        if (!hasA && !hasB)
        {
            const newList = [a, b];
            m.set(a, newList);
            m.set(b, newList);
            continue;
        }

        if (hasA && hasB)
        {
            const [listA, listB] = [m.get(a), m.get(b)];

            if (listA === listB)
            {
                continue;
            }

            const [sizeA, sizeB] = [listA.length, listB.length];
            const listSmall = (sizeA < sizeB ? listA : listB);
            const listLarge = (sizeA >= sizeB ? listA : listB);

            for (const i of listSmall)
            {
                m.set(i, listLarge);
                listLarge.push(i);
            }

            continue;
        }

        const valueToInsert = (hasA ? b : a);
        const insertList = m.get(hasA ? a : b);
        insertList.push(valueToInsert);
        m.set(valueToInsert, insertList);
    }

    return getMinMaxLength(m.values());
}

function main()
{
    const ws = fs.createWriteStream(process.env.OUTPUT_PATH);

    const n = parseInt(readLine(), 10);
    const data = new Array(n);
    for (let i = 0; i < n; i++)
    {
        data[i] = readLine().split(' ').map(x => parseInt(x, 10));
    }

    const result = componentsInGraph(data);

    ws.write(`${result[0]} ${result[1]}\n`);

    ws.end();
}
