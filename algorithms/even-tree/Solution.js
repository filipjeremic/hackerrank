'use strict';

const fs = require('fs');

process.stdin.resume();
process.stdin.setEncoding('utf-8');

let inputString = '';
let currentLine = 0;

process.stdin.on('data', function (inputStdin)
{
    inputString += inputStdin;
});

process.stdin.on('end', function ()
{
    inputString = inputString.split('\n');

    main();
});

function readLine()
{
    return inputString[currentLine++];
}

function readTwoInts()
{
    return readLine().split(' ').map((s) => parseInt(s, 10));
}

function readInput()
{
    const [_, edgeCount] = readTwoInts();

    const m = new Map();

    for (let i = 0; i < edgeCount; i++)
    {
        const [toNode, fromNode] = readTwoInts();

        if (!m.has(fromNode))
        {
            m.set(fromNode, new Set());
        }

        m.get(fromNode).add(toNode);
    }

    return m;
}

function main()
{
    const m = readInput();
    let result = 0;

    function evenForest(currentNode)
    {
        if (!m.has(currentNode))
        {
            return 1;
        }

        let childrenCount = 0;

        m.get(currentNode).forEach(childNode =>
        {
            const childChildrenCount = evenForest(childNode);
            if (childChildrenCount % 2 == 0)
            {
                result++;
            } else
            {
                childrenCount += childChildrenCount;
            }
        });

        return ++childrenCount;
    }

    evenForest(1);

    const ws = fs.createWriteStream(process.env.OUTPUT_PATH);
    ws.write(result + '\n');
    ws.end();
}
