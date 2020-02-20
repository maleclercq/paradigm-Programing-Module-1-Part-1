var Stack = function()
{
    this.stack = [];
}

Stack.prototype.add = function(item)
{
    return this.stack.push(item)
}

Stack.prototype.get = function()
{
    return this.stack[this.stack.length - 1];
}

Stack.prototype.remove = function()
{
    return this.stack.pop();
}

var s = new Stack()
s.add(42);
console.log(""+s.get());
s.add("hello")
console.log(""+s.get());
s.remove();
console.log(""+s.get());