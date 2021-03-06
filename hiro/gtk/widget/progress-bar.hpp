#if defined(Hiro_ProgressBar)

namespace hiro {

struct pProgressBar : pWidget {
  Declare(ProgressBar, Widget)

  auto minimumSize() const -> Size;
  auto setPosition(uint position) -> void;
};

}

#endif
