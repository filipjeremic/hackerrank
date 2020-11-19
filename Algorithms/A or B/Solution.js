'use strict';

/*

Time complexity: O(n)
Space complexity: O(n)

The logic:

The numbers in this problem are extremely large and are handled as strings.
The solution has two parts: mandatory and optimization.

Mandatory part - here we attempt to transform A and B so that A | B = C with
the minimum number of changes. For this we use a table which has every combination
of A, B and C. So for each value of A and B (both 0..15, that is 0x0..0xF), we store
how many changes are required and what are the resulting A and B to get A | B = C.
The size of this table is 16x16x16 = 4096. We do this once because we don’t want to
recalculate the same combinations. If this part fails, the numbers can’t be transformed
with up to K changes and we print out -1.

Optimization part - we use the remaining K to optimize. This part is simpler because
if a bit in C is 0 there is nothing to optimize (because in this case, after the mandatory part,
bit A and bit B are both 0, which is already optimal). When bit C is 1 there are 3 cases:

| bit A | bit B |
|   0   |   1   |
|   1   |   0   |
|   1   |   1   |

We always want bit A to be 0 since A has priority. Therefore, bit B needs to be 1.
In the first case, we already have those values and there is nothing to be done.
In the second case we need to change both bit A and bit B, so two steps are required.
In the third case all we need to do is set bit A to 0.
Notice that this loop doesn’t end at the first failure because you can have a situation
where K = 1 in case two. In this case you skip the transformation and continue checking
because there might be a case three later on to ultimately use the last K.

Important note - the output must be upper case to be accepted on HackerRank.

In this solution (JavaScript) I utilized BigInt for printing output. Check out the other solutions
for a base case (leading zeroes need to be skipped).

*/

process.stdin.resume();
process.stdin.setEncoding('utf-8');

let inputString = '';
let currentLine = 0;

process.stdin.on('data', inputStdin => {
    inputString += inputStdin;
});

process.stdin.on('end', _ => {
    inputString = inputString.trim().split('\n').map(str => str.trim());

    main();
});

function readLine() {
    return inputString[currentLine++];
}

function getMandatoryChanges(a, b, c)
{
    let [totalChangeCount, aNew, bNew] = [0, 0, 0];

    for (let i = 8; i > 0; i >>>= 1)
    {
        const [aBit, bBit, cBit] = [a, b, c].map(v => (v & i) ? 1 : 0);
        const cBitIs0 = cBit ^ 1;

        const changeCount = (cBitIs0 * (aBit + bBit)) + (cBit * ((aBit | bBit) ^ 1));
        aNew = (aNew << 1) | (cBit * aBit);
        bNew = (bNew << 1) | (cBit * (bBit  + changeCount));
        totalChangeCount += changeCount;
    }

    return [totalChangeCount, aNew, bNew];
}

function getMandatoryChangesTable()
{
    const n = 16;
    const t = new Array(n);

    for (let a = 0; a < n; a++)
    {
        const ta = t[a] = new Array(n);
        for (let b = 0; b < n; b++)
        {
            const tb = ta[b] = new Array(n);
            for (let c = 0; c < n; c++) tb[c] = getMandatoryChanges(a, b, c);
        }
    }

    return t;
}

function hexInt(i)
{
    return parseInt(i, 16);
}

const mandatoryChangesTable = getMandatoryChangesTable();

function mandatoryChanges(k, aString, bString, cString)
{
    const size = aString.length;

    const [aResult, bResult] = [new Array(size), new Array(size)];

    for (let i = 0; i < size; i++)
    {
        const [changeCount, aCharNew, bCharNew] =
            mandatoryChangesTable[hexInt(aString[i])][hexInt(bString[i])][hexInt(cString[i])];
        
        k -= changeCount;
        if (k < 0)
        {
            return [false, 0, null, null];
        }
        
        [aResult[i], bResult[i]] = [aCharNew, bCharNew];
    }

    return [true, k, aResult, bResult];
}

function optimize(k, aChar, bChar, cChar)
{
    let [totalChangeCount, aCharNew, bCharNew] = [0, 0, 0];

    const addA = bit => aCharNew = (aCharNew << 1) | bit;
    const addB = bit => bCharNew = (bCharNew << 1) | bit;

    for (let i = 8; i > 0; i >>>= 1)
    {
        const [aBit, bBit, cBit] = [aChar, bChar, cChar].map(v => (v & i) ? 1 : 0);
        const changeCount = aBit + (bBit ^ 1);

        if ((cBit == 0) || (changeCount > k))
        {
            addA(aBit);
            addB(bBit);
        }
        else
        {
            k -= changeCount;
            totalChangeCount += changeCount;

            addA(0);
            addB(1);
        }
    }

    return [totalChangeCount, aCharNew, bCharNew];
}

function optimizationChanges(k, aArr, bArr, cString)
{
    for (let i = 0; i < aArr.length; i++)
    {
        if (k == 0) break;

        const [changeCount, aCharOptimal, bCharOptimal] = optimize(k, aArr[i], bArr[i], hexInt(cString[i]));

        k -= changeCount;
        [aArr[i], bArr[i]] = [aCharOptimal, bCharOptimal];
    }
}

function aOrB(k, a, b, c)
{
    const [mandatoryPartSuccessful, remainingK, aArr, bArr] = mandatoryChanges(k, a, b, c);

    if (mandatoryPartSuccessful === false)
    {
        console.log(-1);
        return;
    }

    optimizationChanges(remainingK, aArr, bArr, c);

    for (let arr of [aArr, bArr]) console.log(
        BigInt("0x" + arr.map(i => i.toString(16)).join("")).toString(16).toUpperCase()
    );
}

function main() {
    const q = parseInt(readLine(), 10);

    for (let qItr = 0; qItr < q; qItr++) {
        const k = parseInt(readLine(), 10);

        const a = readLine();

        const b = readLine();

        const c = readLine();

        aOrB(k, a, b, c);
    }
}
