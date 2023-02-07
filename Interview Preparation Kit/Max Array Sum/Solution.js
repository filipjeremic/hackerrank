'use strict';

const fs = require('fs');

process.stdin.resume();
process.stdin.setEncoding('utf-8');

let inputString = '';
let currentLine = 0;

process.stdin.on('data', inputStdin =>
{
    inputString += inputStdin;
});

process.stdin.on('end', function ()
{
    inputString = inputString.replace(/\s*$/, '')
        .split('\n')
        .map(str => str.replace(/\s*$/, ''));

    main();
});

function readLine()
{
    return inputString[currentLine++];
}

// Note: a recursive solution won't work here (stack overflow)
function maxSubsetSum(arr)
{
    let [appendable, notAppendable] = [0, 0];

    for (const x of arr)
    {
        if (x <= 0)
        {
            appendable = notAppendable = Math.max(appendable, notAppendable);
            continue;
        }

        appendable += x;

        if (notAppendable >= appendable)
        {
            appendable = notAppendable;
            continue;
        }

        [appendable, notAppendable] = [notAppendable, appendable];
    }

    return Math.max(appendable, notAppendable);
}

function main()
{
    const ws = fs.createWriteStream(process.env.OUTPUT_PATH);

    const n = parseInt(readLine(), 10);

    const arr = readLine().split(' ').map(arrTemp => parseInt(arrTemp, 10));

    const res = maxSubsetSum(arr);

    ws.write(res + '\n');

    ws.end();
}
