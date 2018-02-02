static int constexpr forward = 0;
static int constexpr backward = 1;
static int constexpr left = 2;
static int constexpr right = 3;
static int constexpr up = 4;
static int constexpr down = 5;

extern PositionSet const wall[6];

direction nd = (direction)((d + 1) % 6);
