struct DirectionPOD
{
  int direction;
};

static constexpr DirectionPOD direction_begin{0};
static constexpr DirectionPOD x_positive{0};
static constexpr DirectionPOD x_negative{1};
static constexpr DirectionPOD y_positive{2};
static constexpr DirectionPOD y_negative{3};
static constexpr DirectionPOD z_positive{4};
static constexpr DirectionPOD z_negative{5};
static constexpr DirectionPOD direction_end{6};

class Direction : public DirectionPOD
{
  public:
    Direction(DirectionPOD direction) : DirectionPOD(direction) { }

    static DirectionPOD begin() { return direction_begin; }
    static DirectionPOD end() { return direction_end; }

    bool operator!=(DirectionPOD d) const { return direction != d.direction; }

    void operator++() { ++direction; }
};

extern PositionSet const wall[6];

//direction nd = (direction)((d + 1) % 6);
