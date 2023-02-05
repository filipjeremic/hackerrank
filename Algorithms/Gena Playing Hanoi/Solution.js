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

function isWrongOrder(lhs, rhs)
{
  const rhsLength = rhs.length;
  if (rhsLength === 0)
  {
    return false;
  }

  const lhsLength = lhs.length;
  if (lhsLength === 0)
  {
    return true;
  }

  return lhs[lhsLength - 1] < rhs[rhsLength - 1];
}

class State
{
  constructor(rods, step)
  {
    this.rods = rods;
    this.step = step;
  }

  getCompareString()
  {
    return `${this.rods[1]}|${this.rods[2]}|${this.rods[3]}`;
  }

  isGoalState()
  {
    return (
      this.rods[1].length === 0 &&
      this.rods[2].length === 0 &&
      this.rods[3].length === 0
    );
  }

  copy()
  {
    const r = this.rods;
    return new State([[...r[0]], [...r[1]], [...r[2]], [...r[3]]], this.step);
  }

  sort()
  {
    if (isWrongOrder(this.rods[2], this.rods[3]))
    {
      [this.rods[2], this.rods[3]] = [this.rods[3], this.rods[2]];
    }

    if (isWrongOrder(this.rods[1], this.rods[2]))
    {
      [this.rods[1], this.rods[2]] = [this.rods[2], this.rods[1]];
    }

    if (isWrongOrder(this.rods[2], this.rods[3]))
    {
      [this.rods[2], this.rods[3]] = [this.rods[3], this.rods[2]];
    }
  }
}

class MyDequeue
{
  constructor()
  {
    this.front = undefined;
    this.back = undefined;
  }

  pushBack(value)
  {
    if (!this.front)
    {
      this.front = { value };
      this.back = this.front;
    }
    else
    {
      this.back.next = { value };
      this.back = this.back.next;
    }
  }

  popFront()
  {
    if (!this.front)
    {
      return undefined;
    }

    const value = this.front.value;

    this.front = this.front.next;
    if (!this.front)
    {
      this.back = this.front;
    }

    return value;
  }

  isEmpty()
  {
    return !this.front;
  }
}

function createInitialState(inputIntArray)
{
  const rods = [[], [], [], []];
  for (let i = inputIntArray.length - 1; i >= 0; i--)
  {
    const diskSize = i;
    const rodIndex = inputIntArray[i] - 1;
    rods[rodIndex].push(diskSize);
  }
  const initialState = new State(rods, 0);
  initialState.sort();
  return initialState;
}

function solution(initialState)
{
  if (initialState.isGoalState())
  {
    return 0;
  }

  const stateQueue = new MyDequeue();
  stateQueue.pushBack(initialState);

  const visitedStates = new Set();
  visitedStates.add(initialState.getCompareString());

  while (!stateQueue.isEmpty())
  {
    const currentState = stateQueue.popFront();
    const currentRods = currentState.rods;

    for (let toIndex = 0; toIndex < currentRods.length; toIndex++)
    {
      for (let fromIndex = 0; fromIndex < currentRods.length; fromIndex++)
      {
        const fromRod = currentRods[fromIndex];
        const fromRodLength = fromRod.length;

        if (fromRodLength === 0)
        {
          continue;
        }

        const toRod = currentRods[toIndex];
        const toRodLength = toRod.length;
        const valueToMove = fromRod[fromRodLength - 1];

        if ((toRodLength > 0) && (valueToMove >= toRod[toRodLength - 1]))
        {
          continue;
        }

        const newState = currentState.copy();
        newState.rods[toIndex].push(valueToMove);
        newState.rods[fromIndex].pop();
        newState.sort();
        newState.step += 1;

        if (newState.isGoalState())
        {
          return newState.step;
        }

        const newStateCompareString = newState.getCompareString();

        if (!visitedStates.has(newStateCompareString))
        {
          visitedStates.add(newStateCompareString);
          stateQueue.pushBack(newState);
        }
      }
    }
  }

  return 0;
}

function main()
{
  const ws = fs.createWriteStream(process.env.OUTPUT_PATH);

  readLine();
  const inputIntArray = readLine().replace(/\s+$/g, '').split(' ').map(locTemp => parseInt(locTemp, 10));

  const initialState = createInitialState(inputIntArray);

  ws.write(`${solution(initialState)}\n`);

  ws.end();
}
