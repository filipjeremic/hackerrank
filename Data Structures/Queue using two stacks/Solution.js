class Queue {
   constructor() {
      this.enqueueStack = [];
      this.dequeueStack = [];
   }

   enqueue(value) {
      this.enqueueStack.push(value);
   }

   dequeue() {
      this.check_and_transfer();
      return this.dequeueStack.pop();
   }

   check_and_transfer() {
      if (this.dequeueStack.length) return;
      this.transfer();
   }

   transfer() {
      while (this.enqueueStack.length) {
         this.dequeueStack.push(this.enqueueStack.pop());
      }
   }

   front() {
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
