'use strict';

const fs = require('fs');

process.stdin.resume();
process.stdin.setEncoding('utf-8');

let inputString = '';



process.stdin.on('data', inputStdin =>
{
  inputString += inputStdin;
});


process.stdin.on('end', _ =>
{
  const lines = inputString.trim().split('\n');

  const values = lines[0].split(' ').map(Number);
  values.sort((a, b) => a - b);

  main(values);
});



function getNextPow2(n)
{
  if (n == 0)
  {
    return 1;
  }

  let result = 1;

  while (result <= n)
  {
    result *= 2;
  }

  return result;
}



function getInitialCarryMatrix(lowValue, highValue)
{
  const N = getNextPow2(highValue);

  const initialCarryMatrix = Array(lowValue + 1).fill().map(() => Array(N).fill(0));

  for (let i = 1; i <= lowValue; i++)
  {
    for (let j = i; j <= highValue; j++)
    {
      initialCarryMatrix[i][i ^ j] = 1;
    }
  }

  return initialCarryMatrix;
}



function reduceMatrix(carryMatrix)
{
  const rows = carryMatrix.length;
  const cols = carryMatrix[0].length;

  for (let i = rows - 1; i > 1; i--)
  {
    for (let j = 0; j < cols; j++)
    {
      carryMatrix[i - 1][j] += carryMatrix[i][j];
    }
  }
}



function xorCarryMatrix(B, carryMatrix)
{
  const N = carryMatrix[0].length;

  const xorMatrix = Array(B + 1).fill().map(() => Array(N).fill(0));

  for (let i = 1; i <= B; i++)
  {
    for (let j = 0; j < N; j++)
    {
      xorMatrix[i][i ^ j] = carryMatrix[i][j];
    }
  }

  return xorMatrix;
}



function calculateResult(A, xorMatrix)
{
  let result = 0;

  for (let i = 1; i <= A; i++)
  {
    result += xorMatrix[i].reduce((a, b) => a + b);
    result -= xorMatrix[i][i];
  }

  return result;
}



function beautifulQuadruples(values)
{
  let carryMatrix = getInitialCarryMatrix(values[2], values[3]);
  reduceMatrix(carryMatrix);

  carryMatrix = xorCarryMatrix(values[1], carryMatrix);
  reduceMatrix(carryMatrix);

  return calculateResult(values[0], carryMatrix);
}



function main(values)
{
  const ws = fs.createWriteStream(process.env.OUTPUT_PATH);

  const result = beautifulQuadruples(values);

  ws.write(result + "\n");

  ws.end();
}
