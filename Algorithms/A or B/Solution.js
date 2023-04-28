'use strict';

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
