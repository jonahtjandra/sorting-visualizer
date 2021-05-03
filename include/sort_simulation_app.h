//
// Created by Jonah on 19/04/21.
//
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "container.h"

namespace sortsimulator {

/**
 * An app for visualizing the behavior sorting algorithm.
 */
    class SortSimulationApp : public ci::app::App {
    public:
        SortSimulationApp();

        void draw() override;
        void update() override;
        void mouseDown(ci::app::MouseEvent event) override;
        void keyDown(ci::app::KeyEvent event) override;

    private:
        const int kWindowSize = 700;
        const int kTitleTopMargin = 50;
        const int kLeftMargin = 50;
        const int kNumberOfBars = 40;
        void GenerateNewArray();
        Container container_;
        //true if array simulation is currently being sorted
        bool sorted_ = false;

    };

}  // namespace sortsimulator
