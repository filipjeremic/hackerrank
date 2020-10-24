/*

Iterative solution

Time complexity: O(n)
Space complexity: O(1)

Note - a recursive solution won't work here (stack overflow)

The logic:
    - every value that you use, the adjacent one you can't
    - therefore you have to skip everything that is not required
    - when you skip a value you get the maximum sum so far (this restarts the process of considering values)
    - negative values are not considered
    - for positive values you have to check what's larger, max_sum(i - 2) + value or max_sum(i - 1)
    - if max_sum(i - 2) + value is larger you consider the value (here you have to swap the sums because you added a value)
    - if max_sum(i - 1) is larger you don't consider value

*/

'use strict';

const fs = require('fs');

process.stdin.resume();
process.stdin.setEncoding('utf-8');

let inputString = '';
let currentLine = 0;

process.stdin.on('data', inputStdin => {
    inputString += inputStdin;
});

process.stdin.on('end', function () {
    inputString = inputString.replace(/\s*$/, '')
        .split('\n')
        .map(str => str.replace(/\s*$/, ''));

    main();
});

function readLine() {
    return inputString[currentLine++];
}

// Complete the maxSubsetSum function below.
function maxSubsetSum(arr) {
    let [appendable, notAppendable] = [0, 0];

    for (const x of arr) {
        if (x <= 0) {
            appendable = notAppendable = Math.max(appendable, notAppendable);
            continue;
        }

        appendable += x;

        if (notAppendable >= appendable) {
            appendable = notAppendable;
            continue;
        }

        [appendable, notAppendable] = [notAppendable, appendable];
    }

    return Math.max(appendable, notAppendable);
}

function main() {
    const ws = fs.createWriteStream(process.env.OUTPUT_PATH);

    const n = parseInt(readLine(), 10);

    const arr = readLine().split(' ').map(arrTemp => parseInt(arrTemp, 10));

    const res = maxSubsetSum(arr);

    ws.write(res + '\n');

    ws.end();
}
