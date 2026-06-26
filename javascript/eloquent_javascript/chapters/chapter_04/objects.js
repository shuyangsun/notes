// @bun @bytecode @bun-cjs
(function (exports, require, module, __filename, __dirname) {
  // objects.js
  var obj = {
    a: 1,
    b: 2,
  };
  console.log("Object:");
  console.log(obj);
  obj.a = undefined;
  console.log("Set obj.a to undefined");
  delete obj.b;
  console.log("Deleted obj.b");
  console.log("Object:");
  console.log(obj);
  console.log("obj.a = " + obj.a);
  console.log("obj.b = " + obj.b);
  console.log('"a" in obj: ' + ("a" in obj));
  console.log('"b" in obj: ' + ("b" in obj));
});
