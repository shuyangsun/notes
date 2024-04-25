void printDelimiter() {
  print('-' * 80);
}

void main() {
  const record = ('first', a: 2, b: 3, 'last');

  print(record.$1);
  print(record.a);
  print(record.b);
  print(record.$2);

  printDelimiter();

  (int, double, {String name, double ratio}) record_2;
  record_2 = (1, 2.5, name: 'Shuyang', ratio: 0.5);
  print(record_2);

  printDelimiter();

  ({int a, int b}) recordAB = (a: 1, b: 2);
  ({int x, int y}) recordXY = (x: 3, y: 4);
  print('$recordAB, $recordXY');

  // Compile error! These records don't have the same type.
  // recordAB = recordXY;

  printDelimiter();

  // a, b and x, y are purely for annotation purpose.
  (int a, int b) recordAB2 = (1, 2);
  (int x, int y) recordXY2 = (3, 4);
  recordAB2 = recordXY2;
  print('$recordAB2, $recordXY2');

  printDelimiter();

  (int x, int y, int z) point1 = (1, 2, 3);
  (int r, int g, int b) color1 = (1, 2, 3);
  print('point1 == color1: ${point1 == color1}'); // Prints 'true'.

  ({int x, int y, int z}) point2 = (x: 1, y: 2, z: 3);
  ({int r, int g, int b}) color2 = (r: 1, g: 2, b: 3);
  print('point2 == color2: ${point2 == color2}'); // Prints 'true'.

  printDelimiter();

  print('1 == "1": ${1 == '1'}');
}
