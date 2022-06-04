'use strict';

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


function isPossible(sr, sc, er, ec)
{
  if ((sr + er) % 2 != 0)
  {
    return false;
  }

  if ((sc + ec) % 2 != 0)
  {
    return (er - sr + 2) % 4 == 0;
  }

  return (er - sr) % 4 == 0;
}


function getShortestPath(n, sr, sc, er, ec)
{
  let path = "";
  let moveCount = 0;

  while (sr != er || sc != ec)
  {
    if (sr > er)
    {
      // moving up

      const leftUpFirst = ((ec - sc) * 2) < (sr - er);
      if (sc > 0 && ((sc >= ec) || leftUpFirst))
      {
        path += "UL";
        sc--;
      }
      else
      {
        path += "UR";
        sc++;
      }
      sr -= 2;
    }
    else if (sr < er)
    {
      // moving down or right

      if ((ec - sc) * 2 > (er - sr))
      {
        // moving right
        path += "R";
        sc += 2;
      }
      else
      {
        // moving down

        const rightDownFirst = (sc - ec) * 2 < (er - sr);
        if ((sc < n - 1) && ((sc <= ec) || rightDownFirst))
        {
          path += "LR";
          sc++;
        }
        else
        {
          path += "LL";
          sc--;
        }

        sr += 2;
      }
    }
    else
    {
      if (ec < sc)
      {
        path += "L";
        sc -= 2;
      }
      else
      {
        path += "R";
        sc += 2;
      }
    }

    moveCount++;
    path += " ";
  }

  return [moveCount, path];
}


function printShortestPath(n, sr, sc, er, ec)
{
  const fs = require('fs');
  const ws = fs.createWriteStream(process.env.OUTPUT_PATH);

  if (isPossible(sr, sc, er, ec))
  {
    const [moveCount, path] = getShortestPath(n, sr, sc, er, ec);
    ws.write(moveCount + "\n" + path + "\n");
  }
  else
  {
    ws.write("Impossible\n");
  }

  ws.end();
}


function main()
{
  const n = parseInt(readLine().trim(), 10);

  const firstMultipleInput = readLine().replace(/\s+$/g, '').split(' ');

  const sr = parseInt(firstMultipleInput[0], 10);
  const sc = parseInt(firstMultipleInput[1], 10);
  const er = parseInt(firstMultipleInput[2], 10);
  const ec = parseInt(firstMultipleInput[3], 10);

  printShortestPath(n, sr, sc, er, ec);
}
