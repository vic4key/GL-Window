struct freeglutStrokeFont
{
  const char* name;
  int num_chars;
  void* ch;
  float top;
  float bottom;
};

struct freeglutBitmapFont
{
  const char* name;
  const int num_chars;
  const int first;
  const void* ch;
};