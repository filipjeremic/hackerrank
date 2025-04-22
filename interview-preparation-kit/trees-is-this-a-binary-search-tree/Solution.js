'use strict';

function processData(input)
{
  return input.split('\n')[1].split(' ').map(e => parseInt(e, 10));
}

function formTree(arr, startIndex, endIndex)
{
  if (arguments.length === 1)
  {
    startIndex = 0;
    endIndex = arr.length;
  }

  if (startIndex === endIndex)
  {
    return null;
  }

  const middleIndex = startIndex + Math.trunc((endIndex - startIndex) / 2);

  return {
    value: arr[middleIndex],
    left: formTree(arr, startIndex, middleIndex),
    right: formTree(arr, middleIndex + 1, endIndex),
  };
}

function checkBST(root, min, max)
{
  if (root === null)
  {
    return true;
  }

  if (arguments.length === 1)
  {
    min = -1;
    max = 10001;
  }

  return (
    root.value > min &&
    root.value < max &&
    checkBST(root.left, min, root.value) &&
    checkBST(root.right, root.value, max)
  );
}

process.stdin.resume();
process.stdin.setEncoding("ascii");

var _input = "";

process.stdin.on("data", function (input)
{
  _input += input;
});

process.stdin.on("end", function ()
{
  const arr = processData(_input);
  const root = formTree(arr);
  process.stdout.write(checkBST(root) ? "Yes" : "No");
});
