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
    let [sumWithCurrent, sumWithPrevious] = [0, 0];

    for (const x of arr)
    {
        if (x <= 0)
        {
            sumWithCurrent = sumWithPrevious = Math.max(sumWithCurrent, sumWithPrevious);
            continue;
        }

        sumWithCurrent += x;

        if (sumWithPrevious >= sumWithCurrent)
        {
            sumWithCurrent = sumWithPrevious;
            continue;
        }

        [sumWithCurrent, sumWithPrevious] = [sumWithPrevious, sumWithCurrent];
    }

    return Math.max(sumWithCurrent, sumWithPrevious);
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
