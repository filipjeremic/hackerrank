class Queue {
    constructor() {
        // O(1)
        this.enqueueStack = [];
        this.dequeueStack = [];
    }

    enqueue(value) {
        // Amortized O(1)
        this.enqueueStack.push(value);
    }

    dequeue() {
        // Amortized O(1)
        this.check_and_transfer();
        return this.dequeueStack.pop();
    }

    check_and_transfer() {
        // Amortized O(1)
        if (this.dequeueStack.length) return;
        this.transfer();
    }

    transfer() {
        // Amortized O(n), where n is the number of elements in enqueueStack
        while (this.enqueueStack.length) {
            this.dequeueStack.push(this.enqueueStack.pop());
        }
    }

    front() {
        // Amortized O(1)
        this.check_and_transfer();
        return this.dequeueStack[this.dequeueStack.length - 1];
    }
}

function processData(input) {
    const q = new Queue();

    const inputArr = input.trim().split('\n');

    for (let i = 1; i < inputArr.length; i++) {
        const t = inputArr[i].trim().split(' ');

        switch (Number(t[0])) {
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
process.stdin.on("data", function (input) {
    _input += input;
});

process.stdin.on("end", function () {
    processData(_input);
});
