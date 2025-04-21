class Queue
{
    // O(1)
    constructor()
    {
        this.enqueueStack = [];
        this.dequeueStack = [];
    }

    // Amortized O(1)
    enqueue(value)
    {
        this.enqueueStack.push(value);
    }

    // Amortized O(1)
    dequeue()
    {
        this.check_and_transfer();
        return this.dequeueStack.pop();
    }

    // Amortized O(1)
    check_and_transfer()
    {
        if (this.dequeueStack.length)
        {
            return;
        }

        this.transfer();
    }

    // Amortized O(n), where n is the number of elements in enqueueStack
    transfer()
    {
        while (this.enqueueStack.length)
        {
            this.dequeueStack.push(this.enqueueStack.pop());
        }
    }

    // Amortized O(1)
    front()
    {
        this.check_and_transfer();
        return this.dequeueStack[this.dequeueStack.length - 1];
    }
}

function processData(input)
{
    const q = new Queue();

    const inputArr = input.trim().split('\n');

    for (let i = 1; i < inputArr.length; i++)
    {
        const t = inputArr[i].trim().split(' ');

        switch (Number(t[0]))
        {
            case 2:
                q.dequeue();
                break;
            case 3:
                console.log(q.front());
                break;
            default:
                q.enqueue(Number(t[1]));
                break;
        }
    }
}

process.stdin.resume();
process.stdin.setEncoding("ascii");
_input = "";
process.stdin.on("data", function (input)
{
    _input += input;
});

process.stdin.on("end", function ()
{
    processData(_input);
});
