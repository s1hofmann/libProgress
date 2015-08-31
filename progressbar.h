#pragma once

#include "terminfo.h"
#include <string>
#include <sstream>
#include <cmath>

template <typename T>
class ProgressBar
{
public:
    ProgressBar(const T totalElements) {
        this->setDimensions();
        this->totalElements = totalElements;
        this->initialize();
        this->drawProgressBar();
    }

    ProgressBar(const T totalElements, const std::string &label) {
        this->setDimensions();
        this->totalElements = totalElements;
        this->label = label;
        this->initialize();
        this->drawLabel();
        this->drawProgressBar();
    }

    void setLabel(const std::string &label) {
        this->label = label;
    }

    std::string getLabel() {
        return this->label;
    }

    int getProgressBarWidth() {
        return this->progressBarWidth;
    }

    int getTerminalWidth() {
        return this->totalWidth;
    }

    void initialize() {
        this->progressBarBuffer.str(std::string());
        this->progressBarBuffer.clear();

        this->progressBarBuffer << "[";
        for(int i = 0; i < this->progressBarWidth; ++i) {
            this->progressBarBuffer << " ";
        }
        this->progressBarBuffer << "]";

        this->progressBar = this->progressBarBuffer.str();

        this->progressBarBuffer.str(std::string());
        this->progressBarBuffer.clear();
        this->progressBarBuffer << " 0%";
        this->progressBarPercent = this->progressBarBuffer.str();
    }

    void update(T current) {
        float percent = current/(float)this->totalElements;
        this->currentProgressPercent = 100*percent;
        int progress = percent * this->progressBarWidth;
        if(progress < this->progressBarWidth) {
            this->progressBar.replace(progress + 1, 1, "#");
        }

        this->progressBarBuffer.str(std::string());
        this->progressBarBuffer.clear();
        this->progressBarBuffer << " " << this->currentProgressPercent << "%";

        this->progressBarBuffer >> this->progressBarPercent;

        if(progress > this->currentProgress) {
            this->currentProgress = progress;
            this->drawProgressBar();
            this->setDimensions();
        }
    }

    void drawLabel() {
        if(!this->label.empty()) {
            std::cout << this->label << std::endl;
            for(int i = 0; i < this->label.size(); ++i) {
                std::cout << "=";
            }
            std::cout << std::endl;
        }
    }

    void drawProgressBar() {
        std::cout << "\r" << this->progressBar << this->progressBarPercent << std::flush;
    }

private:
    void setDimensions() {
        this->totalWidth = this->termInfo.getCols();
        this->progressBarWidth = this->totalWidth - 7;
    }

//
// DATA
//
    TermInfo termInfo;

    T totalElements;

    std::string label;
    std::string progressBar;
    std::string progressBarPercent;
    std::stringstream progressBarBuffer;

    int progressBarWidth;
    int totalWidth;
    int stepSize;
    int elementStepSize;

    int currentProgressPercent = 0.0;
    int currentProgress = 0;
};
