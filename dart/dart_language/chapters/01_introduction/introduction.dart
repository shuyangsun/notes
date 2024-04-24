var flyByObjects = ['jupyter', 'plane'];

void main() {
  flyByObjects
      .where((obj) => obj.contains('y'))
      .forEach((obj) => print('+++ ${obj} +++'));
}
