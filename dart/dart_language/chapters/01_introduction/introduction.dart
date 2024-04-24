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

void main() {
  printContains(flyByObjects, 'y');
}
