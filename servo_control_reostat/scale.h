class Scale {
  public:
  /**    
   *     @brief Конструктор класса. В качестве аргументво принимает граничные значения двух шкал.
   */
   Scale(float a_min, float a_max, float b_min, float b_max): a_min_(a_min), a_max_(a_max), b_min_(b_min), b_max_(b_max), 
        a_scale_ratio_((a_max_ - a_min_) / (b_max_ - b_min_)), 
        b_scale_ratio_((b_max_ - b_min_) / (a_max_ - a_min_)) {}

    int get_on_scale_a(int x_b) {
      return (x_b - b_min_) * a_scale_ratio_ + a_min_;
    }

    int get_on_scale_b(int x_a) {
      return (x_a - a_min_) * b_scale_ratio_ + b_min_;
    }

  private:
    const float a_min_;
    const float a_max_;
    const float b_min_;
    const float b_max_;
    const float a_scale_ratio_;
    const float b_scale_ratio_;
};
