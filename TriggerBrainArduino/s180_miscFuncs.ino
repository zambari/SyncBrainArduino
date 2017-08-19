

long calculateIntervalMicroSecs(int bpm)
{
  // Take care about overflows!
  return 60L * 1000 * 1000 * 10 / bpm / CLOCKS_PER_BEAT;
}