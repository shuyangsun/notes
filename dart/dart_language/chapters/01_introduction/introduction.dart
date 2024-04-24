var flyByObjects = ['jupyter', 'plane'];

// Map<String, Object>
var image = {
  'tags': ['saturn'],
  'url': '//path/to/saturn.jpg'
};

Map<String, String> audio = {'plane': '//path/to/plane.wav'};

int printContains(List<String> arr, String str) {
  int res = 0;
  flyByObjects
      .where((obj) => obj.contains('y'))
      .forEach((obj) => print('+++ ${obj} +++'));
  return res;
}

class Point {
  double x;
  double y;

  Point(this.x, this.y) {}
}

class Rectangle {
  final Point center;
  final double halfWidth;
  final double halfHeight;

  Point get topLeft => Point(center.x - halfWidth, center.y - halfHeight);
  Point get topRight => Point(center.x + halfWidth, center.y - halfHeight);
  Point get bottomLeft => Point(center.x - halfWidth, center.y + halfHeight);
  Point get bottomRight => Point(center.x + halfWidth, center.y + halfHeight);

  double get width => halfWidth * 2;
  double get height => halfHeight * 2;

  double get area => width * height;
  double get circumference => (width + height) * 2;

  Rectangle(this.center, this.halfWidth, this.halfHeight) {}
  Rectangle.tlwh(double x, double y, double w, double h)
      : this(Point(x + w / 2, y + h / 2), x / 2, h / 2);

  void describe() {
    const precision = 3;
    print('Rectangle with width=${width.toStringAsFixed(precision)}, '
        'height=${height.toStringAsFixed(precision)} '
        'staring at top left (${topLeft.x.toStringAsFixed(precision)}, '
        '${topLeft.y.toStringAsFixed(precision)}). '
        'Circumference=${circumference.toStringAsFixed(precision)}, '
        'area=${area.toStringAsFixed(precision)}.');
  }
}

class Square extends Rectangle {
  double get length => super.width;

  Square(Point center, double halfLength)
      : super(center, halfLength, halfLength);
}

void main(List<String> arguments) {
  printContains(flyByObjects, 'y');

  var rect = Rectangle.tlwh(0.2, 0.4, 0.3, 0.6);
  rect.describe();

  var square = Square(Point(0.2, 0.6), 0.5);
  square.describe();

  Square? nullableSquare = square;
  if (arguments.length <= 1) {
    nullableSquare = null;
  }
  print(nullableSquare?.area);
}
