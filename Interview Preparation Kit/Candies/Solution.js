// The logic:
//    - every child must get at least 1 piece of candy
//    - the amout of candy a child gets depends only on its neighbors
//    - if the childs rating is higher than that of its previous neighbor,
//          it gets 1 piece of candy more than the previous neighbor, otherwise it gets 1
//    - same rule applies for its next neighbor
//    - the child gets the greater (max) of the two values pieces of candy

// Time complexity: O(n)
// Space complexity: O(n)

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

// Complete the candies function below.
function candies(n, arr) {
    const candy = Array(n).fill(1);

    for (let i = 1; i < n; i++) {
        if (arr[i] > arr[i - 1]) {
            candy[i] = candy[i - 1] + 1;
        }
    }

    for (let i = n - 2; i >= 0; i--) {
        if (arr[i] > arr[i + 1]) {
            candy[i] = Math.max(candy[i], candy[i + 1] + 1);
        }
    }

    return candy.reduce((a, b) => a + b);
}

function main() {
    const ws = fs.createWriteStream(process.env.OUTPUT_PATH);

    const n = parseInt(readLine(), 10);

    let arr = [];

    for (let i = 0; i < n; i++) {
        const arrItem = parseInt(readLine(), 10);
        arr.push(arrItem);
    }

    const result = candies(n, arr);

    ws.write(result + '\n');

    ws.end();
}
