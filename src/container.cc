//
// Created by Jonah on 19/04/21.
//

#include "container.h"
#include "quicksort.h"
#include <vector>
#include <algorithm>
#include <iostream>

namespace sortsimulator {

    using glm::vec2;

    Container::Container() {
        sorted_ = false;
    }

    Container::Container(std::vector<std::tuple<int,int,int>> animation) {
        animations_ = animation;
    }

    void Container::ParseQuickSort() {
        sorted_ = true;
        sortsimulator::QuickSort quicksort = sortsimulator::QuickSort(array_);
        animations_ = quicksort.GetAnimations();
        for (int i : quicksort.GetArray()) {
            std::cout << i << std::endl;
        }
    }

    void Container::Display() const {
        ci::gl::color(ci::Color("white"));
        ci::gl::drawStrokedRect(ci::Rectf(vec2(kMarginLeft, kMarginBottom),
                                          vec2(kMarginLeft+kWidth, kMarginBottom + kHeight)));
        float bar_width = (float)(kWidth - (array_.size() + 1)*kSpacing)/array_.size();
        for (int i = 0; i < array_.size(); i++) {
            ci::gl::color(color_array_[i]);
            ci::gl::drawSolidRect(ci::Rectf(vec2(kMarginLeft + kSpacing + i*(bar_width+kSpacing),
                                                 kMarginBottom + kHeight),
                                            vec2(kMarginLeft + kSpacing + i*(bar_width+kSpacing) + bar_width,
                                                 (kHeight + kMarginBottom) - ((kHeight - kSpacing)
                                                 / array_.size() * array_[i]))));
        }
    }

    void Container::AdvanceOneFrame() {
        if (sorted_) {
            //color change
            if (std::get<0>(animations_[count_]) == 1) {
                color_array_[std::get<1>(animations_[count_])] = ci::Color("red");
                color_array_[std::get<2>(animations_[count_])] = ci::Color("blue");
            }
            //uncolor
            if (std::get<0>(animations_[count_]) == 0) {
                color_array_[std::get<1>(animations_[count_])] = ci::Color("white");
                color_array_[std::get<2>(animations_[count_])] = ci::Color("white");
            }
            //swap
            if (std::get<0>(animations_[count_]) == 2) {
                int tmp = array_[std::get<1>(animations_[count_])];
                array_[std::get<1>(animations_[count_])] = array_[std::get<2>(animations_[count_])];
                array_[std::get<2>(animations_[count_])] = tmp;
            }
            Display();
            count_++;
            //sorting has finished
            if (count_ >= animations_.size()) {
                sorted_ = false;
            }
        }
    }

    void Container::SetArray(std::vector<int>& arr) {
        array_ = arr;
        for (int i = 0; i < arr.size(); i++) {
            color_array_.emplace_back("white");
        }
    }

}  // namespace sortsimulator
