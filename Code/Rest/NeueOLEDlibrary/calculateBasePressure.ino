/* Basisdruck (P0) berechnen*/

double calculateBasePressure() {
  for (int i = 0; i < measurements; i++)
  {
    Array[i] = getPressure();
  }
  for (int i = 0; i < measurements; i++)
  {
    P0 = P0 + Array[i];
  }
  P0 = P0 / measurements;

}
